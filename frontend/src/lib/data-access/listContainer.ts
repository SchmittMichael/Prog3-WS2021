import { List } from "./list";

export class ListContainer{
  public lists: List[] = [];

  private listCounter: number;

  constructor(){
    this.listCounter =0;
  }


  addList(): List {
    let l: List = new List(this.listCounter,'')
    this.lists.push(l);
    return l;
  }

  removeList(id: number): void {
    let i: number = this.getListPos(id);
    if (id != -1) this.lists.splice(i, 1);
  }

  getListPos(id: number): number {
    for(var i = 0;i<this.lists.length;i++){
      if(this.lists[i].getID() == id)
      return i;
    }
    return -1;
  }


  getLists(): List[] {
    return this.lists;
  }
}
