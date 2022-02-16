#pragma ocnce

#include <string>

namespace ReminderApp {
namespace Core {
namespace Model {
class Reminder {
  public:
    Reminder(int id, std::string title, int position, std::string date, bool flag);
    ~Reminder(){};

    int getId() const;
    std::string getTitle() const;
    int getPos() const;
    std::string  getDate() const;
    bool getFlag() const;

    void setID(int newID);
    void setTitle(std::string newTitle);
    void setPos(int newPos);
    void setDate(std::string date);
    void setFlag(bool newFlagStatus);

  private:
    int id;
    std::string title;
    int position;
    bool flag;
    std::string date;
};

} // namespace Model
} // namespace Core
} // namespace ReminderApp
