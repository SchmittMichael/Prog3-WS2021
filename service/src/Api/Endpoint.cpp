#include "Endpoint.hpp"

#include <iostream>

using namespace Reminder::Api;
using namespace Reminder::Core;
using namespace crow;

Endpoint::Endpoint(SimpleApp &givenApp, Manager &givenManager) : app(givenApp),
                                                                 manager(givenManager) {
    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {

    CROW_ROUTE(app, "/api/board")
    ([this](const request &req, response &res) {
        std::string jsonBoards = Manager.getListContainer();
        res.write(jsonBoards);
        res.end();
    });

    CROW_ROUTE(app, "/api/board/columns")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res) {
            std::string jsonColumns;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumns = Manager.getLists();
                break;
            }
            case HTTPMethod::Post: {
                jsonColumns = Manager.postList(req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonColumns);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/columns/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listID) {
            std::string jsonColumn = "{}";

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumn = Manager.getList(listID);
                break;
            }
            case HTTPMethod::Put: {
                jsonColumn = Manager.putList(listID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                Manager.deleteList(listID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonColumn);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/columns/<int>/items")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res, int listID) {
            std::string jsonItem;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = Manager.getReminders(listID);
                break;
            }
            case HTTPMethod::Post: {
                jsonItem = Manager.postReminder(listID, req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });

    CROW_ROUTE(app, "api/lc/lists/<int>/lists/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listID, int reminderID) {
            std::string jsonItem;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = Manager.getReminder(listID, reminderID);
                break;
            }
            case HTTPMethod::Put: {
                jsonItem = Manager.putReminder(listID, reminderID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                Manager.deleteReminder(listID, reminderID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });
}
