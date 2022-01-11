export class Reminder {
  //private id: number;
  private date: Date;
  private title: String;
  private flag: boolean;
  private id : number;

  constructor(id: number, date: Date, title: String){
    this.id = id;
    this.date = date;
    this.title = title;
    this.flag = false;
  }

  getID(): number{
    return this.id;
  }

  getTitle(): String{
    return this.title;
  }

  setTiile(newName: String): void{
    this.title = newName;
  }

  setDate(newDate: Date):void{
    this.date=newDate;
  }
  //git commit geht nicht
}
