#pragma ocnce

#include <ctime>
#include <string>

namespace ReminderApp {
namespace Core {
namespace Model {
class Reminder {
  public:
    Reminder(int id, std::string title, int position, time_t date, bool flag);
    ~Reminder(){};

    int getId() const;
    std::string getTitle() const;
    int getPos() const;
    time_t getDate() const;
    bool getFlag() const;

    void setID(int newID);
    void setTitle(std::string newTitle);
    void setPos(int newPos);
    void setDate(time_t newDate);
    void setFlag(bool newFlagStatus);

  private:
    int id;
    std::string title;
    int position;
    bool flag;
    time_t date;
};

} // namespace Model
} // namespace Core
} // namespace ReminderApp
