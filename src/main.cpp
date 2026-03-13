#include "crow_all.h"
#include "services/PacketService.hpp"
#include "routes/PacketRoutes.hpp"
#include "routes/HealthRoutes.hpp"

int main()
{
    crow::SimpleApp app;
    PacketService packetService;

    registerHealthRoutes(app);
    registerPacketRoutes(app, packetService);

    app.port(23500).multithreaded().run();

    return 0;
}