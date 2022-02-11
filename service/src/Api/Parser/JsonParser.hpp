#pragma once

#include "ParserIf.hpp"
#include "rapidjson/document.h"

namespace ReminderApp {
namespace Api {
namespace Parser {

class JsonParser : public ParserIf {
  private:
    static inline std::string const EMPTY_JSON = "{}";

    bool isValidList(rapidjson::Document const &document);
    bool isValidReminder(rapidjson::Document const &document);

    std::string jsonValueToString(rapidjson::Value const &json);

    rapidjson::Value getJsonValueFromModel(ReminderApp::Core::Model::Reminder const &reminder, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModel(ReminderApp::Core::Model::List const &list, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModel(ReminderApp::Core::Model::ListContainer &listcontainer, rapidjson::Document::AllocatorType &allocator);

  public:
    JsonParser(){};
    virtual ~JsonParser(){};

    virtual std::string getEmptyResponseString() {
        return JsonParser::EMPTY_JSON;
    }

    virtual std::string convertToApiString(ReminderApp::Core::Model::ListContainer &Listcontainer);
    virtual std::string convertToApiString(ReminderApp::Core::Model::List &list);
    virtual std::string convertToApiString(std::vector<ReminderApp::Core::Model::List> &lists);

    virtual std::string convertToApiString(ReminderApp::Core::Model::Reminder &reminder);
    virtual std::string convertToApiString(std::vector<ReminderApp::Core::Model::Reminder> &reminders);

    virtual std::optional<ReminderApp::Core::Model::List> convertListToModel(int listId, std::string &request);
    virtual std::optional<ReminderApp::Core::Model::Reminder> convertReminderToModel(int reminderId, std::string &request);

    virtual std::string getEmptyResponseString() {
        return JsonParser::EMPTY_JSON;
    }
};

} // namespace Parser
} // namespace Api
} // namespace ReminderApp
