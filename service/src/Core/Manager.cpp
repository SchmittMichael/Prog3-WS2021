#include "Manager.hpp"
#include <iostream>

using namespace ReminderApp::Core;
using namespace ReminderApp::Core::Model;
using namespace ReminderApp::Api::Parser;
using namespace ReminderApp::Repository;
using namespace std;

Manager::Manager(ParserIf &givenParser, RepositoryIf &givenRepository)
    : parser(givenParser), repository(givenRepository) {
}

Manager::~Manager() {
}

std::string Manager::getListContainer() {

      ListContainer container = repository.getListContainer();

      return parser.convertToApiString(container);

}

std::string Manager::getLists() {

      std::vector<List> lists = repository.getLists();

      return parser.convertToApiString(lists);

}

std::string Manager::getList(int listId) {


        std::optional<List> list = repository.getList(listId);
        if (list) {
            return parser.convertToApiString(list.value());
        } else {
            return parser.getEmptyResponseString();
        }

}

std::string Manager::postList(std::string request) {

      int const dummyId = -1;
      std::optional<List> parsedListOptional = parser.convertListToModel(dummyId, request);
      if (false == parsedListOptional.has_value()) {
          return parser.getEmptyResponseString();
      }

      List parsedList = parsedListOptional.value();

      std::optional<List> postedList = repository.postList(parsedList.getName(), parsedList.getPos());

      if (postedList) {
          return parser.convertToApiString(postedList.value());
      } else {
          return parser.getEmptyResponseString();
      }

}

std::string Manager::putList(int listId, std::string request) {

        std::optional<List> parsedListOptional = parser.convertListToModel(listId, request);

        if (false == parsedListOptional.has_value()) {
            return parser.getEmptyResponseString();
        }
        List list = parsedListOptional.value();
        std::optional<List> putList = repository.putList(listId, list.getName(), list.getPos());

        if (putList) {
            return parser.convertToApiString(putList.value());
        } else {
            return parser.getEmptyResponseString();
        }

}

void Manager::deleteList(int listId) {
    repository.deleteList(listId);
}

std::string Manager::getReminders(int listId) {
    std::vector<Reminder> reminders = repository.getReminders(listId);
     return parser.convertToApiString(reminders);
}

std::string Manager::getReminder(int listId, int reminderId) {

        std::optional<Reminder> reminder = repository.getReminder(listId, reminderId);

        if (reminder) {
            return parser.convertToApiString(reminder.value());
        } else {
            return parser.getEmptyResponseString();
        }

}

std::string Manager::postReminder(int listId, std::string request) {

      int const dummyId = -1;
      std::optional parsedReminderOptional = parser.convertReminderToModel(dummyId, request);
      if (false == parsedReminderOptional.has_value()) {
          return parser.getEmptyResponseString();
      }

      Reminder reminder = parsedReminderOptional.value();
      std::optional<Reminder> postedReminder = repository.postReminder(listId, reminder.getTitle(), reminder.getPos(), reminder.getDate());
      if (postedReminder) {
          return parser.convertToApiString(postedReminder.value());
      } else {
          return parser.getEmptyResponseString();
      }

}

std::string Manager::putReminder(int listId, int reminderId, std::string request) {

        std::optional parsedReminderOptional = parser.convertReminderToModel(reminderId, request);
        if (false == parsedReminderOptional.has_value()) {
            return parser.getEmptyResponseString();
        }

        Reminder reminder = parsedReminderOptional.value();
        std::optional<Reminder> putReminder = repository.putReminder(listId, reminderId, reminder.getTitle(), reminder.getPos(), reminder.getDate());

        if (putReminder) {
            return parser.convertToApiString(putReminder.value());
        } else {
            return parser.getEmptyResponseString();
        }

}

void Manager::deleteReminder(int listId, int reminderId) {
    repository.deleteReminder(listId, reminderId);
}
