#pragma once

#include "Repository/RepositoryIf.hpp"
#include "sqlite3.h"
#include <string>

namespace ReminderApp {
namespace Repository {

class SQLiteRepository : public RepositoryIf {
  private:
    sqlite3 *database;

  public:
    SQLiteRepository();
    virtual ~SQLiteRepository();

    static std::string const databaseFile;
};
// test
} // namespace Repository
} // namespace ReminderApp
