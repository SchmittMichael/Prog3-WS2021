export class Reminder {
  //private id: number;
  private date: string;
  private title: string;
  private flag: boolean;
  private id: number;

  constructor(id: number, title: string) {
    this.id = id;
    this.date = new Date().toDateString();
    this.title = title;
    this.flag = false;
    //console.log("Reminder erstellt: "+title)
  }

  getID(): number {
    return this.id;
  }

  getTitle(): string {
    return this.title;
  }

  getDate(): string {
    return this.date;
  }

  setTitle(newName: string): void {
    this.title = newName;
  }

  setDate(newDate: string): void {
    this.date = newDate;
  }
}
