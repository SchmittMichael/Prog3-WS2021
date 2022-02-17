#include "Endpoint.hpp"

#include <iostream>

using namespace ReminderApp::Api;
using namespace ReminderApp::Core;
using namespace crow;

Endpoint::Endpoint(SimpleApp &givenApp, Manager &givenManager) : app(givenApp),
                                                                 manager(givenManager) {
    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {

    CROW_ROUTE(app, "/api/lc")
    ([this](const request &req, response &res) {
        std::string jsonListContainers = manager.getListContainer();
        res.write(jsonListContainers);
        res.end();
    });

    CROW_ROUTE(app, "/api/lc/lists")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res) {
            std::string jsonLists;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonLists = manager.getLists();
                break;
            }
            case HTTPMethod::Post: {
                jsonLists = manager.postList(req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonLists);
            res.end();
        });

    CROW_ROUTE(app, "/api/lc/lists/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listID) {
            std::string jsonList = "{}";

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonList = manager.getList(listID);
                break;
            }
            case HTTPMethod::Put: {
                jsonList = manager.putList(listID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteList(listID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonList);
            res.end();
        });

    CROW_ROUTE(app, "/api/lc/lists/<int>/reminders")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res, int listID) {
            std::string jsonReminder;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonReminder = manager.getReminders(listID);
                break;
            }
            case HTTPMethod::Post: {
                jsonReminder = manager.postReminder(listID, req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonReminder);
            res.end();
        });


    CROW_ROUTE(app, "/api/lc/flagged/reminders")
      .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res) {

            std::string jsonFlagged;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonFlagged = manager.getFlaggedReminders();
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonFlagged);
            res.end();
        });


    CROW_ROUTE(app, "/api/lc/today/reminders")
      .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res) {

            std::string jsonToday;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonToday = manager.getTodayReminders();
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonToday);
            res.end();
        });



    CROW_ROUTE(app, "/api/lc/lists/<int>/reminders/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listID, int reminderID) {
            std::string jsonReminder;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonReminder = manager.getReminder(listID, reminderID);
                break;
            }
            case HTTPMethod::Put: {
                jsonReminder = manager.putReminder(listID, reminderID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteReminder(listID, reminderID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonReminder);
            res.end();
        });
}
