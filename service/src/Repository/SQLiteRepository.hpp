#pragma once

#include "Repository/RepositoryIf.hpp"
#include "sqlite3.h"
#include <string>
#include "ctime"


namespace ReminderApp {
namespace Repository {

class SQLiteRepository : public RepositoryIf {
  private:
    sqlite3 *database;

    void initialize();
    void createDummyData();
    void handleSQLError(int statementResult, char *errorMessage);

    static bool isValid(int id) {
        return id != INVALID_ID;
    }

    static ReminderApp::Core::Model::Reminder getReminderFromCallback(char **fieldValues, int startIndex);
    static ReminderApp::Core::Model::List getListFromCallback(char **fieldValues, int startIndex);

    static int queryListsCallback(void *data, int numberOfLists, char **fieldValues, char **listsNames);
    static int queryRemindersCallback(void *data, int numberOfReminder, char **fieldValues, char **reminderNames);


  public:
    SQLiteRepository();
    virtual ~SQLiteRepository();

    virtual ReminderApp::Core::Model::ListContainer getListContainer();
    virtual std::vector<ReminderApp::Core::Model::List> getLists();
    virtual std::optional<ReminderApp::Core::Model::List> getList(int id);
    virtual std::optional<ReminderApp::Core::Model::List> postList(std::string name, int position);
    virtual std::optional<ReminderApp::Core::Model::List> putList(int id, std::string name, int position);
    virtual void deleteList(int id);
    virtual std::optional<ReminderApp::Core::Model::List> getFlagged();
    virtual std::optional<ReminderApp::Core::Model::List> getToday();
    virtual std::vector<ReminderApp::Core::Model::Reminder> getReminders(int listId);
    virtual std::optional<ReminderApp::Core::Model::Reminder> getReminder(int listId, int reminderId);
    virtual std::optional<ReminderApp::Core::Model::Reminder> postReminder(int listId, std::string title, int position, std::string date, bool falg);
    virtual std::optional<ReminderApp::Core::Model::Reminder> putReminder(int listId, int reminderId, std::string title, int position, std::string date, bool flag);
    virtual void deleteReminder(int columnId, int itemId);

    static inline std::string const listContainerName = "DefaultListContainer";
    static inline int const INVALID_ID = -1;


    static std::string const databaseFile;
};
// test
} // namespace Repository
} // namespace ReminderApp
