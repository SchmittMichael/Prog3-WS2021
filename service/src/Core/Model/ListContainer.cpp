#include "ListContainer.hpp"

using namespace ReminderApp::Core::Model;

ListContainer::ListContainer(std::string name) : name(name){};

std::string ListContainer::getName() const {
    return name;
}

std::vector<List> &ListContainer::getLists() {
    return lists;
}

void ListContainer::setLists(std::vector<List> const &lists) {
    this->lists = lists;
}
