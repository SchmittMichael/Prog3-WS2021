import { reminderContainer } from './reminderContainer';
export class List {
   id: number;
  private title: string;
  private remCon: reminderContainer;

  constructor(id: number, title: string) {
    this.id = id;
    this.title = title;
    this.remCon = new reminderContainer(id, title);
  }

  setTitle(newTitle: string): void {
    console.log("Tile updated.");
    this.title = newTitle;
    this.remCon.setName(newTitle);
  }


  getRemCon(): reminderContainer{
    return this.remCon;
  }

  getTitle(): string {
    return this.title;
  }

  getID(): number {
    console.log("listID abgerufen")
    return this.id;
  }

  getRemConCount(): number {
    return this.remCon.getCount();
  }


}
