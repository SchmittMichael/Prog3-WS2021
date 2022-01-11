export class List {
public name: String;
public remindcount: number;
static listcounter: number = 1;


constructor(name: String){
this.name = name;
this.remindcount = 0;   // set number of Reminders default 0
List.listcounter ++ ;  // set  number for default name
}

getID(): number{
  return List.listcounter;
}

getListTitle(): String{
  return this.name;
}




}
