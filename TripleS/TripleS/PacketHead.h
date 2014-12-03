#pragma once

namespace TripleS
{
    typedef UInt32  PACKET_TYPE;
    typedef void*   PACKET_PTR;
    class PacketHead
    {
    public:

        PacketHead(PACKET_TYPE packetType)
            : m_packetType(packetType)
        {
        }

        PACKET_TYPE GetPacketType() const
        {
            return m_packetType;
        }

        void SetType(PACKET_TYPE type)
        {
            m_packetType = type;
        }


    private:
        PACKET_TYPE m_packetType;
    };
};