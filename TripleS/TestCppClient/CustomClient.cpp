#include "CustomClient.h"
#include <stdlib.h>
#include <stdio.h>
#include "packet.pb.h"
#include "..\TripleS\PacketHeader.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

CustomClient::CustomClient(void)
{
}

CustomClient::~CustomClient(void)
{
}

void CustomClient::_Working( SOCKET client_sock )
{
    int return_value;
    char buf[1024 +1];
    while (true)
    {
        /*printf("input : ");
        fgets(buf, 1024+1, stdin);

        int len = strlen(buf);
        buf[len-1] = '\0';*/

        EchoPacket packet;
        packet.set_id(1);
        packet.set_name("a");

        int buf_size = 8 + packet.ByteSize();

        google::protobuf::io::ArrayOutputStream output_array_stream(buf, buf_size);
        google::protobuf::io::CodedOutputStream output_coded_stream(&output_array_stream);

        TripleS::PacketHeader packet_header;
        packet_header.size = packet.ByteSize();
        packet_header.type = eEchoPacket;
        output_coded_stream.WriteRaw(&packet_header, sizeof(packet_header));
        packet.SerializeToCodedStream(&output_coded_stream);

        printf("send attemp\n");
        return_value = send(client_sock, buf, buf_size, 0);
        if (return_value == SOCKET_ERROR || return_value == INVALID_SOCKET)
        {
            printf("send error\n");
            break;
        }

        printf("recv attemp\n");
        return_value = recv(client_sock, buf, 1024, 0);
        if (return_value == SOCKET_ERROR || return_value == INVALID_SOCKET)
        {
            printf("recv error\n");
            break;
        }

        buf[return_value] = '\0';

        printf("%s\n",buf);
    }
}
