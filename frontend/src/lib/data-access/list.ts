import { reminderContainer } from './reminderContainer';
export class List {
  private id: number;
  private title: string;
  private remCon: reminderContainer;

  constructor(id: number, title: string) {
    this.id = id;
    this.title = title;
    this.remCon = new reminderContainer(id, title);
  }

  setTitle(newValue: string): void {
    console.log("Tile updated.");
    this.title = newValue;
  }

  getRemcom(): reminderContainer{
    return this.remCon;
  }

  getTitle(): string {
    return this.title;
  }

  getID(): number {
    return this.id;
  }
}
