#pragma once

#include "List.hpp"
#include <string>
#include <vector>

namespace ReminderApp {
namespace Core {
namespace Model {

class ListContainer {
  public:
    ListContainer(int id);
    ~ListContainer() {}

    int getID() const;

    std::vector<List> &getLists();
    void setLists(std::vector<List> const &Lists);

  private:
    int id;
    std::vector<List> lists;
};

} // namespace Model
} // namespace Core
} // namespace ReminderApp
