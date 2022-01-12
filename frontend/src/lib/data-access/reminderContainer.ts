import { Reminder } from "./reminder";

export class reminderContainer {

  private id: number;
  public reminders: Reminder[] = [];
  private name: string;
  private reminderCounter: number;



  constructor(id: number, name: string){
    this.id = id;
    this.name = name;
    this.reminderCounter = 0;
    console.log("RerminderContainer erstellt: "+name);

  }

  addReminder(): Reminder{
    let reminder: Reminder = new Reminder (this.reminderCounter, '');
    this.reminders.push(reminder);
    return reminder;
  }

  removeReminder(id: number): void {
    let i: number = this.getReminderPos(id);
    if (id != -1) this.reminders.splice(i, 1);
  }

  getReminderPos(id:number): number {
    for (var i = 0; i < this.reminders.length; i++) {
      if (this.reminders[i].getID() == id) {
        return i;
      }
    }
    return -1;
  }

  getID(): number {
    return this.id;
  }

  getName(): string {
    return this.name;
  }

  getCount(): number {
    return this.reminderCounter;
  }

  getReminders(): Reminder[]{
    return this.reminders;
  }

}
