import { Component, OnInit } from '@angular/core';
import { List } from '../../../data-access/models/list';
import { ListContainer } from '../../../data-access/models/listContainer';
import { ListComponent } from '../list/list.component';

@Component({
  selector: 'listContainer',
  templateUrl: './listContainer.component.html',
  styleUrls: ['./listContainer.component.scss'],
})
export class ListContainerComponent implements OnInit {
  lcObject: ListContainer;
  selected: List;
  view: ListComponent;
  flagedcount: number;

  ngOnInit(): void {
    this.lcObject = new ListContainer();
  }

  createNewList(): void {
    this.selected = this.lcObject.addList();
  }

  deleteList(id: number): void {
    this.lcObject.removeList(id);
  }

  currentView(currentList: ListComponent): void{
    if(this.view != null){
      this.view.setViewFalse();
      this.view = currentList;
    }
    else this.view = currentList;
  }
  showFlaggedCount(): number {

    //<div id="remindCount"> {{showFlaggedCount()}}</div>
/*
    this.lcObject.lists.forEach(List  => {
      List.getRemCon.getReminders.forEach(Reminder => {
      if(Reminder.getFlag == true){this.flagedcount ++;}
    });

    });
    */
     this.flagedcount = 9; // idk wie die mehtode geht -__O
    return this.flagedcount ;
  }
}
