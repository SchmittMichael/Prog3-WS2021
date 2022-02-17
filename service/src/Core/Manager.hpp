#pragma once

#include "Api/Parser/ParserIf.hpp"
#include "Repository/RepositoryIf.hpp"

namespace ReminderApp {
namespace Core {
class Manager {
  private:
    ReminderApp::Repository::RepositoryIf &repository;
    ReminderApp::Api::Parser::ParserIf &parser;

  public:
    Manager(ReminderApp::Api::Parser::ParserIf &givenParser, ReminderApp::Repository::RepositoryIf &givenRepository);
    ~Manager();

    std::string getListContainer();
    std::string getLists();
    std::string getList(int listId);
    std::string postList(std::string request);
    std::string putList(int listId, std::string request);
    void deleteList(int listId);

    std::string getReminders(int listId);
    std::string getReminder(int listId, int reminderId);
    std::string getFlaggedReminders();
    std::string getTodayReminders();
    std::string postReminder(int listId, std::string request);
    std::string putReminder(int listId, int reminderId, std::string request);
    void deleteReminder(int listId, int reminderId);
};

} // namespace Core
} // namespace ReminderApp
