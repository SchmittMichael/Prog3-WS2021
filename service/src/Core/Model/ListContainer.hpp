#pragma once

#include "List.hpp"
#include <string>
#include <vector>

namespace ReminderApp {
namespace Core {
namespace Model {

class ListContainer {
  public:
    ListContainer(std::string name);
    ~ListContainer() {}

    std::string getName() const;

    std::vector<List> &getLists();
    void setLists(std::vector<List> const &Lists);

  private:
    std::string name;
    std::vector<List> lists;
};

} // namespace Model
} // namespace Core
} // namespace ReminderApp
