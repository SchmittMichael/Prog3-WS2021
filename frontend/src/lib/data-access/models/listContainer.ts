import { List } from "./list";

export class ListContainer {
  lists: List[] = [];
  static listCounter: number = 0;

  constructor() {}

  addList(): List {
    let l: List = new List(ListContainer.listCounter++, ListContainer.listCounter+". Liste");
    this.lists.push(l);
    return l;
  }

  removeList(id: number): void {
    let i: number = this.getListPos(id);
    if (id != -1) this.lists.splice(i, 1);
  }

  getListPos(itemID: number): number {
    for (var i = 0; i < this.lists.length; i++) {
      if (this.lists[i].getID() == itemID) {
        return i;
      }
    }
    return -1;
  }

  getLists(): List[] {
    return this.lists;
  }

}
