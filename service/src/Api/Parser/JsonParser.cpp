#define RAPIDJSON_ASSERT(x)

#include "JsonParser.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace ReminderApp::Api::Parser;
using namespace ReminderApp::Core::Model;
using namespace rapidjson;
using namespace std;

string JsonParser::convertToApiString(ListContainer &listcontainer) {
    Document document;
    Document::AllocatorType &allocator = document.GetAllocator();

    Value jsonBoard = getJsonValueFromModel(listcontainer, allocator);
    return jsonValueToString(jsonBoard);
}

string JsonParser::convertToApiString(List &list) {
    Document document(kObjectType);

    Value jsonList = getJsonValueFromModel(list, document.GetAllocator());
    return jsonValueToString(jsonList);
}

string JsonParser::convertToApiString(std::vector<List> &lists) {
    Document document(kArrayType);
    Document::AllocatorType &allocator = document.GetAllocator();

    for (List &list : lists) {
        Value jsonList = getJsonValueFromModel(list, allocator);
        document.PushBack(jsonList, allocator);
    }

    return jsonValueToString(document);
}

string JsonParser::convertToApiString(Reminder &reminder) {

    string result = EMPTY_JSON;
    Document document(kObjectType);

    Value jsonReminder = getJsonValueFromModel(reminder, document.GetAllocator());
    result = jsonValueToString(jsonReminder);
    return result;
}

string JsonParser::convertToApiString(std::vector<Reminder> &reminders) {
    Document document(kArrayType);
    Document::AllocatorType &allocator = document.GetAllocator();

    for (Reminder &reminder : reminders) {
        Value jsonReminder = getJsonValueFromModel(reminder, allocator);
        document.PushBack(jsonReminder, allocator);
    }

    return jsonValueToString(document);
}

std::optional<List> JsonParser::convertListToModel(int listId, std::string &request) {

    std::optional<List> resultList;
    Document document;
    document.Parse(request.c_str());

    if (true == isValidList(document)) {
        std::string name = document["name"].GetString();
        int position = document["position"].GetInt();
        resultList = List(listId, name, position);
    }
    return resultList;
}

std::optional<Reminder> JsonParser::convertReminderToModel(int reminderId, std::string &request) {
    std::optional<Reminder> resultReminder;

    Document document;
    document.Parse(request.c_str());

    if (true == isValidReminder(document)) {
        std::string title = document["title"].GetString();
        int position = document["position"].GetInt();
        long date = document["date"].GetInt64();
        resultReminder = Reminder(reminderId, title, position, date);
    }
    return resultReminder;
}

string JsonParser::jsonValueToString(rapidjson::Value const &json) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    json.Accept(writer);

    return buffer.GetString();
}

rapidjson::Value JsonParser::getJsonValueFromModel(Reminder const &reminder, rapidjson::Document::AllocatorType &allocator) {
    Value jsonReminder(kObjectType);

    jsonReminder.AddMember("id", reminder.getId(), allocator);
    jsonReminder.AddMember("title", Value(reminder.getTitle().c_str(), allocator), allocator);
    jsonReminder.AddMember("position", reminder.getPos(), allocator);
    // jsonReminder.AddMember("timestamp", Value(reminder.getTimestamp().c_str(), allocator), allocator);

    return jsonReminder;
}

rapidjson::Value JsonParser::getJsonValueFromModel(List const &list, rapidjson::Document::AllocatorType &allocator) {
    Value jsonList(kObjectType);

    jsonList.AddMember("id", list.getId(), allocator);
    jsonList.AddMember("name", Value(list.getName().c_str(), allocator), allocator);
    jsonList.AddMember("position", list.getPos(), allocator);

    Value jsonReminders(kArrayType);

    for (Reminder const &reminder : list.getReminders()) {
        Value jsonReminder = getJsonValueFromModel(reminder, allocator);
        jsonReminders.PushBack(jsonReminder, allocator);
    }

    jsonList.AddMember("reminders", jsonReminders, allocator);

    return jsonList;
}

rapidjson::Value JsonParser::getJsonValueFromModel(ListContainer &listcontainer, rapidjson::Document::AllocatorType &allocator) {
    Value jsonListContainer(kObjectType);
    Value jsonLists(kArrayType);

    for (List &list : listcontainer.getLists()) {
        Value jsonList = getJsonValueFromModel(list, allocator);
        jsonLists.PushBack(jsonList, allocator);
    }

    // jsonListContainer.AddMember("title", Value(listcontainer.getTitle().c_str(), allocator), allocator);
    jsonListContainer.AddMember("lists", jsonLists, allocator);

    return jsonListContainer;
}

bool JsonParser::isValidList(rapidjson::Document const &document) {

    bool isValid = true;

    if (document.HasParseError()) {
        isValid = false;
    }
    if (false == document["name"].IsString()) {
        isValid = false;
    }
    if (false == document["position"].IsInt()) {
        isValid = false;
    }

    return isValid;
}

bool JsonParser::isValidReminder(rapidjson::Document const &document) {

    bool isValid = true;

    if (document.HasParseError()) {
        isValid = false;
    }
    if (false == document["title"].IsString()) {
        isValid = false;
    }
    if (false == document["position"].IsInt()) {
        isValid = false;
    }

    return isValid;
}
