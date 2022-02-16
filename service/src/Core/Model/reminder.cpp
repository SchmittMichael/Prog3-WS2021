#include "Reminder.hpp"

using namespace ReminderApp::Core::Model;

Reminder::Reminder(int id, std::string title, int pos, std::string date, bool flag)
    : id(id), title(title), position(pos), date(date), flag(flag) {}

int Reminder::getId() const {
    return id;
}

int Reminder::getPos() const {
    return position;
}

std::string Reminder::getDate() const {
    return date;
}

std::string Reminder::getTitle() const {
    return title;
}

bool Reminder::getFlag() const{
    return flag;
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

void Reminder::setDate(std::string newDate) {
    date = newDate;
}

void Reminder::setFlag(bool newFlagStatus){
    flag = newFlagStatus;
}
