#pragma once

#include <string>

struct Packet
{
    int id;
    std::string timestamp;
    std::string sourceIp;
    std::string destinationIp;
    std::string protocol;
    int port;
    int payloadSize;
    std::string status;
};