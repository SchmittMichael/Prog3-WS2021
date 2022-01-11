import { Reminder } from "./reminder";

export class reminderContainer {

  private id: number;
  public reminders: Reminder[] = [];
  private name: String;
  private reminderCounter: number;

  

  constructor(id: number, name: String){
    this.id = id;
    this.name = name;
    this.reminderCounter = 0;

  }

  addReminder(date: Date, name: String): Reminder{
    let reminder: Reminder = new Reminder (this.reminderCounter, date, name);
    this.reminders.push(reminder);
    return reminder;
  }

}
