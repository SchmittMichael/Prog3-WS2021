#pragma once

#include "Core/Model/ListContainer.hpp"
#include "optional"
#include "ctime"

namespace ReminderApp {
namespace Repository {
class RepositoryIf {
  public:
    virtual ~RepositoryIf() {}

    virtual ReminderApp::Core::Model::ListContainer getListContainer() = 0;
    virtual std::vector<ReminderApp::Core::Model::List> getLists() = 0;
    virtual std::optional<ReminderApp::Core::Model::List> getList(int id) = 0;
    virtual std::optional<ReminderApp::Core::Model::List> postList(std::string name, int position) = 0;
    virtual std::optional<ReminderApp::Core::Model::List> putList(int id, std::string name, int position) = 0;
    virtual void deleteList(int id) = 0;
    virtual std::vector<ReminderApp::Core::Model::Reminder> getReminders(int listId) = 0;
    virtual std::optional<ReminderApp::Core::Model::Reminder> getReminder(int listId, int reminderId) = 0;
    virtual std::optional<ReminderApp::Core::Model::Reminder> postReminder(int listId, std::string title, int position, time_t date, bool flag) = 0;
    virtual std::optional<ReminderApp::Core::Model::Reminder> putReminder(int listId, int itemId, std::string title, int position, time_t date, bool flag) = 0;
    virtual void deleteReminder(int listId, int reminderId) = 0;
};

} // namespace Repository
} // namespace ReminderApp
