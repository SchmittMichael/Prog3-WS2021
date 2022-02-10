#include "ListContainer.hpp"

using namespace Core::Model;

ListContainer::ListContainer(int id) : id(id){};

int ListContainer::getID() const {
    return id;
}

std::vector<List> &ListContainer::getLists() {
    return lists;
}

void ListContainer::setLists(std::vector<List> const &lists) {
    this->lists = lists;
}
