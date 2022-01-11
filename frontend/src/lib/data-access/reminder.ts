export class Reminder {
  //private id: number;
  private date: String;
  private title: String;
  private flag: boolean;
  private id : number;

  constructor(id: number, title: String){
    this.id = id;
    this.date = new Date().toDateString();
    this.title = title;
    this.flag = false;
  }

  getID(): number{
    return this.id;
  }

  getTitle(): String{
    return this.title;
  }

  getDate(): String{
    return this.date;
  }

  setTitle(newName: String): void{
    this.title = newName;
  }

  setDate(newDate: String):void{
    this.date=newDate;
  }
  //git commit geht nicht
}
