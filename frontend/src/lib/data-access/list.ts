import { reminderContainer } from './reminderContainer';
export class List {
  private id: number;
  public title: String;
  public remindcount: number;
  static listcounter: number = 1;
  public rC: reminderContainer;

  constructor(id: number, name: String) {
    this.id = id;
    this.title = name;
    this.remindcount = 0; // set number of Reminders default 0
    List.listcounter++; // set  number for default name
    this.rC = new reminderContainer(0, name);

    console.log("Neue liste erstellt!");
  }

  getID(): number {
    return List.listcounter;
  }

  getListTitle(): String {
    return this.title;
  }

  setListTitle(title: String): void {
    this.title = title;
  }
}
