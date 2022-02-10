#pragma ocnce

#include <ctime>
#include <string>

namespace ReminderApp {
namespace Core {
namespace Model {
class Reminder {
  public:
    Reminder(int id, std::string title, int position, time_t date);
    ~Reminder(){};

    int getId() const;
    std::string getTitle() const;
    int getPos() const;
    time_t getDate() const;

    void setID(int newID);
    void setTitle(std::string newTitle);
    void setPos(int newPos);
    void setDate(time_t newDate);

  private:
    int id;
    std::string title;
    int position;
    time_t date;
};

} // namespace Model
} // namespace Core
} // namespace ReminderApp
