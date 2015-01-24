using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net;
using System.Net.Sockets;
using TripleS;

namespace TestCSharpClient
{
    class Program
    {
        public static void HandleEchoPacket(byte[] packet_buf)
        {
            EchoPacket packet = EchoPacket.CreateBuilder().MergeFrom(packet_buf).Build();
            Console.WriteLine(packet.ToString());
            Console.WriteLine(Util.ByteStringToString(packet.Name, Encoding.Default));
        }
        public static void HandleStringPacket(byte[] packet_buf)
        {
            StringPacket packet = StringPacket.CreateBuilder().MergeFrom(packet_buf).Build();
            Console.WriteLine(packet.ToString());
        }
        public static void HandleAddResultPacket(byte[] packet_buf)
        {
            AddResultPacket packet = AddResultPacket.CreateBuilder().MergeFrom(packet_buf).Build();
            Console.WriteLine(packet.ToString());
        }
        public static Int32 InputInteger()
        {
            string input_str = Console.ReadLine();
            int converted_int = 0;
            try
            {
                converted_int = Convert.ToInt32(input_str);
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            return converted_int;
        }
        static void Main(string[] args)
        {
            TClient tcp_client = new TClient();
            tcp_client.AddHandle(PACKET_TYPE.eEchoPacket, new TClient.Handler(HandleEchoPacket));
            tcp_client.AddHandle(PACKET_TYPE.eStringPacket, new TClient.Handler(HandleStringPacket));
            tcp_client.AddHandle(PACKET_TYPE.eAddResultpacket, new TClient.Handler(HandleAddResultPacket));
            tcp_client.Connect("127.0.0.1", 9000);
            while(true)
            {
/*
                string message = Console.ReadLine();
                if (message.IndexOf("END") > -1) break;

                EchoPacket.Builder newTestPacketBuilder = EchoPacket.CreateBuilder();
                newTestPacketBuilder.SetId(10);
                newTestPacketBuilder.SetName(Util.StringToByteString(message, Encoding.Default)); // 문자열은 이와같은 변형을 반드시 필요로한다
                EchoPacket packet = newTestPacketBuilder.Build();
                newTestPacketBuilder = null;
                tcp_client.SendProtobuf(packet, PACKET_TYPE.eEchoPacket);
*/

                AddPacket.Builder packet_builder = AddPacket.CreateBuilder();
                Console.Write("first : ");
                packet_builder.SetFirst(InputInteger());
                Console.Write("second : ");
                packet_builder.SetSecond(InputInteger());
                AddPacket packet = packet_builder.Build();
                packet_builder = null;
                tcp_client.SendProtobuf(packet, PACKET_TYPE.eAddPacket);
            }
            tcp_client.Disconnect();
        }
    }
}