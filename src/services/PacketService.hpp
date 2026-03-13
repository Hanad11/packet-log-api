#pragma once

#include <optional>
#include <vector>
#include "../models/Packet.hpp"

class PacketService
{
private:
    std::vector<Packet> packets;
    int nextId;

    std::string generateTimestamp() const;

public:
    PacketService();

    Packet addPacket(const Packet& packet);
    std::vector<Packet> getAllPackets() const;
    std::optional<Packet> getPacketById(int id) const;
};