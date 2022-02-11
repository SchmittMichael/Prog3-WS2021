#include "List.hpp"

using namespace ReminderApp::Core::Model;

List::List(int id, std::string name, int pos)
    : id(id), name(name), position(pos) {}

int List::getId() const {
    return id;
}

std::string List::getName() const {
    return name;
}

int List::getPos() const {
    return position;
}

std::vector<Reminder> List::getReminders() const {
    return reminders;
}

void List::setID(int givenId) {
    id = givenId;
}

void List::setName(std::string newName) {
    name = newName;
}

void List::setPos(int newPos) {
    position = newPos;
}

void List::addReminder(Reminder &newReminder) {
    reminders.push_back(newReminder);
}
