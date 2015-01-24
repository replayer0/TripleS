using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace TripleS
{
    class TClient
    {
        public TClient()
        {
            m_handlers = new Dictionary<PACKET_TYPE, Handler>();
        }
        public delegate void Handler(byte[] packet_buf);

        private Dictionary<PACKET_TYPE, Handler> m_handlers;

        private Socket m_socket = null;

        public void AddHandle(PACKET_TYPE packet_type, Handler packet_handler)
        {
            m_handlers.Add(packet_type, packet_handler);
        }

        public void DelHandle(PACKET_TYPE packet_type)
        {
            m_handlers.Remove(packet_type);
        }

        public Google.ProtocolBuffers.IMessage HandleBuf(PACKET_TYPE packet_type, byte[] packet_buf)
        {
            Google.ProtocolBuffers.IMessage message = null;
            if (m_handlers.ContainsKey(packet_type) == true)
            {
                m_handlers[packet_type](packet_buf);
            }
            else
            {
                // Console.WriteLine("Invalid packet_type({0})", packet_type);
            }
            return message;
        }

        public void SendProtobuf(Google.ProtocolBuffers.IMessage message, PACKET_TYPE packet_type)
        {
            if (m_socket == null || m_socket.Connected == false)
            {
                Disconnect();
                return;
            }
            byte[] type_bytes = BitConverter.GetBytes((int)packet_type);

            byte[] packet_buffer = message.ToByteArray();
            int size = packet_buffer.Length;
            byte[] size_bytes = BitConverter.GetBytes(size);

            int buf_size = packet_buffer.Length + size_bytes.Length + type_bytes.Length;
            byte[] send_buf = new byte[buf_size];
            System.Buffer.BlockCopy(size_bytes, 0, send_buf, 0, size_bytes.Length);
            System.Buffer.BlockCopy(type_bytes, 0, send_buf, size_bytes.Length, type_bytes.Length);
            System.Buffer.BlockCopy(packet_buffer, 0, send_buf, size_bytes.Length + type_bytes.Length, packet_buffer.Length);
            m_socket.Send(send_buf);
            // Console.WriteLine("Send len({0}) = header({1} + {2}) + body({3})", buf_size, size_bytes.Length, type_bytes.Length, packet_buffer.Length);
        }

        // todo - circular buffer
        byte[] m_stored_buf = new byte[8192];
        byte[] m_recv_buf = new byte[8192];
        int header_size = 8;
        int last_index = 0;
        // 외부에서 버퍼만 넘겨주도록
        private void ProcessReceive(object sender, SocketAsyncEventArgs e)
        {
            if (m_socket == null || m_socket.Connected == false)
            {
                Disconnect();
                return;
            }
            if(e.BytesTransferred == 0) // e.socketerror
            {
                Disconnect();
                // Connect(m_ip, m_port);
                return;
            }
            Console.WriteLine("received {0}", e.BytesTransferred);
            System.Buffer.BlockCopy(e.Buffer, 0, m_stored_buf, last_index, e.BytesTransferred);
            last_index += e.BytesTransferred;
            if (last_index >= header_size)
            {
                int process_size = ProcessPacket(m_stored_buf);
                System.Buffer.BlockCopy(m_stored_buf, process_size, m_stored_buf, 0, last_index - process_size);
                last_index -= process_size;
            }
            m_socket.ReceiveAsync(e);
        }

        public int ProcessPacket(byte[] recv_buf)
        {
            int process_size = 0;
            int remain_size = last_index;
            while(true)
            {
                if (remain_size < header_size)
                {
                    break;
                }
                int packet_size = BitConverter.ToInt32(recv_buf, 0);
                int packet_type = BitConverter.ToInt32(recv_buf, sizeof(int));

                if (remain_size - header_size < packet_size)
                {
                    break;
                }

                byte[] recv_buf_for_body = new byte[packet_size];
                System.Buffer.BlockCopy(recv_buf, 8, recv_buf_for_body, 0, packet_size);

                try
                {
                    HandleBuf((PACKET_TYPE)packet_type, recv_buf_for_body);
                }
                catch (Exception ex)
                {
                    // Console.WriteLine(ex.ToString());
                }
                process_size += header_size + packet_size;
                remain_size -= header_size + packet_size;
                Console.WriteLine("process packet {0}", packet_type);
            }
            return process_size;
        }

        public void Disconnect()
        {
            if (m_socket == null)
            {
                return;
            }
            try
            {
                if (m_socket.Connected)
                {
                    m_socket.Disconnect(false);
                }
                m_socket.Dispose();
                m_socket.Shutdown(SocketShutdown.Both);
                m_socket.Close();
                m_socket = null;
            }
            catch (Exception ex)
            {
                // Console.WriteLine(ex);
            }
        }
        private void ConnectCompleted(object sender, SocketAsyncEventArgs e)
        {
            m_socket = (Socket)sender;

            if (m_socket.Connected)
            {
                SocketAsyncEventArgs args = new SocketAsyncEventArgs();
                args.UserToken = m_socket;
                args.SetBuffer(m_recv_buf, 0, 1024);
                args.Completed += new EventHandler<SocketAsyncEventArgs>(ProcessReceive);
                m_socket.ReceiveAsync(args);
                // Console.WriteLine("Socket Connected {0}", m_socket.RemoteEndPoint.ToString());
            }
            else
            {
                Disconnect();
                // Console.WriteLine("Socket Connect failed");
            }
        }

        public void Connect(string ip, int port)
        {
            m_ip = ip;
            m_port = port;
            try
            {
                IPEndPoint ip_end_point = new IPEndPoint(IPAddress.Parse(ip), port);

                Socket client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                SocketAsyncEventArgs args = new SocketAsyncEventArgs();
                args.RemoteEndPoint = ip_end_point;
                args.Completed += new EventHandler<SocketAsyncEventArgs>(ConnectCompleted);

                client.ConnectAsync(args);
            }
            catch (Exception ex)
            {
                // Console.WriteLine(ex);
            }
        }
        private string m_ip;
        private int m_port;
    }

    class Util
    {
        public static byte[] StringToBytes(string str)
        {
            byte[] bytes = new byte[str.Length * sizeof(char)];
            System.Buffer.BlockCopy(str.ToCharArray(), 0, bytes, 0, bytes.Length);
            return bytes;
        }
        public static string BytesToString(byte[] bytes)
        {
            char[] chars = new char[bytes.Length / sizeof(char)];
            System.Buffer.BlockCopy(bytes, 0, chars, 0, bytes.Length);
            return new string(chars);
        }
        public static byte[] ByteStringToBytes(Google.ProtocolBuffers.ByteString byte_string)
        {
            byte[] bytes = new byte[byte_string.Length];
            byte_string.CopyTo(bytes, 0);
            return bytes;
        }
        public static string ByteStringToString(Google.ProtocolBuffers.ByteString byte_string, Encoding encode)
        {
            return encode.GetString(ByteStringToBytes(byte_string), 0, byte_string.Length);
        }
        public static Google.ProtocolBuffers.ByteString StringToByteString(string str, Encoding encode)
        {
            Google.ProtocolBuffers.ByteString byte_string = Google.ProtocolBuffers.ByteString.CopyFrom(encode.GetBytes(str.ToCharArray()));
            return byte_string;
        }
    }
}
