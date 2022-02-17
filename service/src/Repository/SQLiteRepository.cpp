#include "SQLiteRepository.hpp"
#include <filesystem>
#include <iostream>

using namespace std;
using namespace ReminderApp::Core::Model;
using namespace ReminderApp::Repository;

#ifdef RELEASE_SERVICE
string const SQLiteRepository::databaseFile = "./data/reminder-app.db";
#else
string const SQLiteRepository::databaseFile = "../data/reminder-app.db";
#endif

SQLiteRepository::SQLiteRepository() : database(nullptr) {

    string databaseDirectory = filesystem::path(databaseFile).parent_path().string();

    if (filesystem::is_directory(databaseDirectory) == false) {
        filesystem::create_directory(databaseDirectory);
    }

    int result = sqlite3_open(databaseFile.c_str(), &database);

    if (SQLITE_OK != result) {
        cout << "Cannot open database: " << sqlite3_errmsg(database) << endl;
    }

    initialize();
}

SQLiteRepository::~SQLiteRepository() {
    sqlite3_close(database);
}

void SQLiteRepository::initialize() {
    int result = 0;
    char *errorMessage = nullptr;

    string sqlCreateTableList =
        "create table if not exists list("
        "id integer not null primary key autoincrement,"
        "name text not null,"
        "position integer not null UNIQUE);";

    string sqlCreateTableReminder =
        "create table if not exists reminder("
        "id integer not null primary key autoincrement,"
        "title text not null,"
        "date date not null,"
        "flag integer not null,"
        "position integer not null,"
        "list_id integer not null,"
        "unique (position, list_id),"
        "foreign key (list_id) references list (id));";

    result = sqlite3_exec(database, sqlCreateTableList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
    result = sqlite3_exec(database, sqlCreateTableReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

ListContainer SQLiteRepository::getListContainer() {

    ListContainer lc = ListContainer(listContainerName);

    vector<List> lists = getLists();
    lc.setLists(lists);

    return lc;
}

std::vector<List> SQLiteRepository::getLists() {

    std::vector<List> lists;

    string sqlQueryLists =
        "SELECT list.id, list.name, list.position, reminder.id, reminder.title, reminder.position, reminder.date, reminder.flag from list "
        "left join reminder on list.id = reminder.list_id "
        "order by list.position, reminder.position";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryLists.c_str(), queryListsCallback, &lists, &errorMessage);
    handleSQLError(result, errorMessage);

    return lists;
}

std::optional<List> SQLiteRepository::getList(int id) {

    std::vector<List> lists;

    string sqlQueryLists =
        "SELECT list.id, list.name, list.position, reminder.id, reminder.title, reminder.position, reminder.date, reminder.flag"
        " from list"
        " left join reminder on list.id = reminder.list_id where list.id = " +to_string(id) +
        " order by list.position, reminder.position";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryLists.c_str(), queryListsCallback, &lists, &errorMessage);
    handleSQLError(result, errorMessage);

    if (lists.size() == 1) {
        return lists.front();
    } else {
        return std::nullopt;
    }
}

std::optional<List> SQLiteRepository::postList(std::string name, int position) {

    string sqlPostReminder =
        "INSERT INTO list('name', 'position') "
        "VALUES('" +
        name + "', '" + to_string(position) + "')";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result) {
        int listId = sqlite3_last_insert_rowid(database);
        return List(listId, name, position);
    }

    return std::nullopt;
}

std::optional<ReminderApp::Core::Model::List> SQLiteRepository::putList(int id, std::string name, int position) {

    string sqlUpdateList =
        "UPDATE list "
        "SET name = '" +
        name + "', position = '" + to_string(position) +
        "' WHERE id = " + to_string(id);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlUpdateList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    return getList(id);
}

void SQLiteRepository::deleteList(int id) {

    string sqlDeleteListReminders =
        "DELETE FROM reminder "
        "WHERE reminder.list_id = " +
        to_string(id);

    string sqlDeleteList =
        "DELETE FROM list "
        "WHERE list.id = " +
        to_string(id);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlDeleteListReminders.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    result = sqlite3_exec(database, sqlDeleteList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

std::vector<Reminder> SQLiteRepository::getReminders(int listId) {

    std::vector<Reminder> reminders;

    string sqlQueryReminders =
        "SELECT reminder.id, reminder.title, reminder.position, reminder.date, reminder.flag from reminder "
        "where reminder.list_id = " +std::to_string(listId) +
        " order by reminder.position";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryReminders.c_str(), queryRemindersCallback, &reminders, &errorMessage);
    handleSQLError(result, errorMessage);

    return reminders;
}

std::optional<List> SQLiteRepository::getFlagged() {

    std::vector<Reminder> reminders;

    string sqlQueryReminders =
        "SELECT reminder.id, reminder.title, reminder.position, reminder.date, reminder.flag from reminder "
        "where reminder.flag = 1 "
        "order by reminder.date";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryReminders.c_str(), queryRemindersCallback, &reminders, &errorMessage);
    handleSQLError(result, errorMessage);

    List flagged(-2, "Flagged", -2);
    flagged.setReminders(reminders);

    return flagged;
}

std::optional<Reminder> SQLiteRepository::getReminder(int listId, int reminderId) {

    std::vector<Reminder> reminders;

    string sqlQueryReminders =
        "SELECT reminder.id, reminder.title, reminder.position, reminder.date, reminder.flag from reminder "
        "where reminder.list_id = " +
        std::to_string(listId) + " and reminder.id = " + std::to_string(reminderId) +
        " order by reminder.position";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryReminders.c_str(), queryRemindersCallback, &reminders, &errorMessage);
    handleSQLError(result, errorMessage);

    if (reminders.size() == 1) {
        return reminders.front();
    } else {
        return std::nullopt;
    }
}

std::optional<Reminder> SQLiteRepository::postReminder(int listId, std::string title, int position, std::string date, bool flag) {

    short flagInBin = flag ? 1 : 0;

    string sqlPostReminder =
        "INSERT INTO reminder ('title', 'date', 'position', 'list_id', 'flag') "
        "VALUES ('" +
        title + "', '" + date + "', '" + to_string(position) + "', '" + to_string(listId) + "', '" + to_string(flagInBin) + "')";
    // VALUES ('title', 'date', 'position', 'listId', 'flagInBin' )

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    int reminderId = INVALID_ID;
    if (SQLITE_OK == result) {
        reminderId = sqlite3_last_insert_rowid(database);
    }

    return getReminder(listId, reminderId);
}

std::optional<ReminderApp::Core::Model::Reminder> SQLiteRepository::putReminder(int listId, int reminderId, std::string title, int position, std::string date, bool flag) {

    short flagInBin = flag ? 1 : 0;

    string sqlUpdateReminder =
        "UPDATE reminder SET title = '" + title + "', position = '" + to_string(position) + "', date = '" + date + "', flag = '" + to_string(flagInBin) + "' "
        "WHERE reminder.list_id = " + to_string(listId) +
        " AND reminder.id = " + to_string(reminderId);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlUpdateReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    return getReminder(listId, reminderId);
}

void SQLiteRepository::deleteReminder(int listId, int reminderId) {
    string sqlQueryReminder =
        "DELETE FROM reminder "
        "WHERE reminder.list_id = " +
        to_string(listId) +
        " AND reminder.id = " + to_string(reminderId);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

Reminder SQLiteRepository::getReminderFromCallback(char **fieldValues, int startIndex) {
    int index = startIndex;

    int reminderId = fieldValues[index] ? atoi(fieldValues[index]) : INVALID_ID;
    index++;

    string title = fieldValues[index] ? fieldValues[index] : "";
    index++;

    int position = fieldValues[index] ? atoi(fieldValues[index]) : 0;
    index++;

    string date = fieldValues[index] ? fieldValues[index] : "";
    index++;

    int temp = fieldValues[index] ? atoi(fieldValues[index]) : 0;
    bool flag = temp == 1;

    Reminder rem(reminderId, title, position, date, flag);
    return rem;
}

List SQLiteRepository::getListFromCallback(char **fieldValues, int startIndex) {
    int index = startIndex;

    int listId = fieldValues[index] ? atoi(fieldValues[index]) : INVALID_ID;
    index++;

    string name = fieldValues[index] ? fieldValues[index] : "";
    index++;

    int position = fieldValues[index] ? atoi(fieldValues[index]) : 0;
    index++;

    List l(listId, name, position);
    return l;
}

int SQLiteRepository::queryListsCallback(void *data, int numberOfLists, char **fieldValues, char **listNames) {

    std::vector<List> *pLists = static_cast<std::vector<List> *>(data);
    std::vector<List> &lists = *pLists;

    Reminder reminder = getReminderFromCallback(fieldValues, 3);

    int listId = fieldValues[0] ? atoi(fieldValues[0]) : INVALID_ID;
    bool listAlreadyAdded = false;

    for (List &l : lists) {
        if (l.getId() == listId) {
            listAlreadyAdded = true;
            if (isValid(reminder.getId())) {
                l.addReminder(reminder);
            }
            break;
        }
    }

    if (false == listAlreadyAdded) {
        List l = getListFromCallback(fieldValues, 0);

        if (isValid(reminder.getId())) {
            l.addReminder(reminder);
        }

        if (isValid(l.getId())) {
            lists.push_back(l);
        }
    }

    return 0;
}

int SQLiteRepository::queryRemindersCallback(void *data, int numberOfLists, char **fieldValues, char **listNames) {

    std::vector<Reminder> *result = static_cast<std::vector<Reminder> *>(data);

    Reminder r = getReminderFromCallback(fieldValues, 0);
    if (isValid(r.getId())) {
        result->push_back(r);
    }
    return 0;
}

void SQLiteRepository::handleSQLError(int statementResult, char *errorMessage) {

    if (statementResult != SQLITE_OK) {
        cout << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

void SQLiteRepository::createDummyData() {}
