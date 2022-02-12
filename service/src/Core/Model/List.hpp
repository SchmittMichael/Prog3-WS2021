#pragma once

#include "Reminder.hpp"
#include <string>
#include <vector>

namespace ReminderApp {
namespace Core {

namespace Model {

class List {

  public:
    List(int id, std::string name, int pos);
    ~List(){};

    int getId() const;
    std::string getName() const;
    int getPos() const;
    std::vector<Reminder> getReminders() const;

    void setID(int newID);
    void setName(std::string newName);
    void setPos(int newPos);
    void addReminder(Reminder &newReminder);

  private:
    int id;
    std::string name;
    int position;
    std::vector<Reminder> reminders;
};

} // namespace Model
} // namespace Core
} // namespace ReminderApp
