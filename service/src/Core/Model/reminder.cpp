#include "Reminder.hpp"

using namespace ReminderApp::Core::Model;

Reminder::Reminder(int id, std::string title, int pos, time_t date)
            : id(id), title(title), position(pos), date(date) {}

int Reminder::getId() const {
    return id;
}

int Reminder::getPos() const {
    return position;
}

time_t Reminder::getDate() const {
    return date;
}

void Reminder::setID(int newID) {
    id = newID;
}

void Reminder::setTitle(std::string newTitle) {
    title = newTitle;
}

void Reminder::setPos(int newPos) {
    position = newPos;
}

void Reminder::setDate(time_t newDate) {
    date = newDate;
}

