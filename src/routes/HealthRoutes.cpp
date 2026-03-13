#include "HealthRoutes.hpp"

void registerHealthRoutes(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/health")
    ([]() {
        crow::json::wvalue response;
        response["status"] = "ok";
        return response;
    });

    CROW_ROUTE(app, "/version")
    ([]() {
        crow::json::wvalue response;
        response["service"] = "packet-log-api";
        response["version"] = "1.0.0";
        return response;
    });
}