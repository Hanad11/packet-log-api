#pragma once

#include "crow_all.h"
#include "../services/PacketService.hpp"

void registerPacketRoutes(crow::SimpleApp& app, PacketService& packetService);