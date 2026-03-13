#include "PacketService.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

PacketService::PacketService() : nextId(1)
{
}

std::string PacketService::generateTimestamp() const
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::tm utcTime{};
#if defined(_WIN32)
    gmtime_s(&utcTime, &currentTime);
#else
    gmtime_r(&currentTime, &utcTime);
#endif

    std::ostringstream output;
    output << std::put_time(&utcTime, "%Y-%m-%dT%H:%M:%SZ");
    return output.str();
}

Packet PacketService::addPacket(const Packet& packet)
{
    Packet newPacket = packet;
    newPacket.id = nextId++;
    newPacket.timestamp = generateTimestamp();

    packets.push_back(newPacket);
    return newPacket;
}

std::vector<Packet> PacketService::getAllPackets() const
{
    return packets;
}

std::optional<Packet> PacketService::getPacketById(int id) const
{
    for (const auto& packet : packets)
    {
        if (packet.id == id)
        {
            return packet;
        }
    }

    return std::nullopt;
}