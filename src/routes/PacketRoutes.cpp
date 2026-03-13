#include "PacketRoutes.hpp"

namespace
{
    crow::json::wvalue packetToJson(const Packet& packet)
    {
        crow::json::wvalue response;
        response["id"] = packet.id;
        response["timestamp"] = packet.timestamp;
        response["sourceIp"] = packet.sourceIp;
        response["destinationIp"] = packet.destinationIp;
        response["protocol"] = packet.protocol;
        response["port"] = packet.port;
        response["payloadSize"] = packet.payloadSize;
        response["status"] = packet.status;
        return response;
    }

    bool hasRequiredFields(const crow::json::rvalue& body)
    {
        return body.has("sourceIp")
            && body.has("destinationIp")
            && body.has("protocol")
            && body.has("port")
            && body.has("payloadSize")
            && body.has("status");
    }
}

void registerPacketRoutes(crow::SimpleApp& app, PacketService& packetService)
{
    CROW_ROUTE(app, "/packets").methods(crow::HTTPMethod::Post)
    ([&packetService](const crow::request& req) {
        auto body = crow::json::load(req.body);

        if (!body)
        {
            crow::json::wvalue errorResponse;
            errorResponse["error"] = "Invalid JSON";
            return crow::response(400, errorResponse);
        }

        if (!hasRequiredFields(body))
        {
            crow::json::wvalue errorResponse;
            errorResponse["error"] = "Missing required fields";
            return crow::response(400, errorResponse);
        }

        Packet packet;
        packet.id = 0;
        packet.timestamp = "";
        packet.sourceIp = std::string(body["sourceIp"].s());
        packet.destinationIp = std::string(body["destinationIp"].s());
        packet.protocol = std::string(body["protocol"].s());
        packet.port = body["port"].i();
        packet.payloadSize = body["payloadSize"].i();
        packet.status = std::string(body["status"].s());

        Packet savedPacket = packetService.addPacket(packet);

        return crow::response(201, packetToJson(savedPacket));
    });

    CROW_ROUTE(app, "/packets").methods(crow::HTTPMethod::Get)
    ([&packetService]() {
        std::vector<Packet> packets = packetService.getAllPackets();

        crow::json::wvalue response;
        for (size_t i = 0; i < packets.size(); i++)
        {
            response["packets"][i] = packetToJson(packets[i]);
        }

        return response;
    });

    CROW_ROUTE(app, "/packets/<int>").methods(crow::HTTPMethod::Get)
    ([&packetService](int id) {
        auto packet = packetService.getPacketById(id);

        if (!packet.has_value())
        {
            crow::json::wvalue errorResponse;
            errorResponse["error"] = "Packet not found";
            return crow::response(404, errorResponse);
        }

        return crow::response(200, packetToJson(packet.value()));
    });
}