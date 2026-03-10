#include "../include/crow_all.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/health")
    ([]() {
        crow::json::wvalue response;
        response["status"] = "ok";
        return response;
    });

    app.port(23500).multithreaded().run();

    return 0;
}