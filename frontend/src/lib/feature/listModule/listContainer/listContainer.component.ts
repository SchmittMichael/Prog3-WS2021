import { Component, OnInit } from '@angular/core';
import { List } from '../../../data-access/models/list';
import { ListContainer } from '../../../data-access/models/listContainer';
import { ListComponent } from '../list/list.component';
import { BackendService } from '../../../data-access/service/backend.service'

@Component({
  selector: 'listContainer',
  templateUrl: './listContainer.component.html',
  styleUrls: ['./listContainer.component.scss'],
})
export class ListContainerComponent implements OnInit {
  lcObject?: ListContainer;
  view: ListComponent;

  flagedcount: number;
  newListIndex?: number;

  constructor(private backendService: BackendService) {}

  ngOnInit(): void {
    this.lcObject = {name:"INITIALISING", lists:[]};   //Fix dafür dass er nicht jedes mal die Konsole volspamt mit "ERROR TypeError: Cannot read properties of undefined (reading 'lists')"
    this.backendService.loadListContainer().subscribe( (lc:ListContainer) => (this.lcObject = lc));
  }

  createNewList(): void {
    let newList: List = { name: "", position: 0, reminders:[]};
    this.newListIndex = this.lcObject.lists.push(newList) - 1;

    newList.position = (this.newListIndex === 0)? 1 : this.lcObject.lists[this.newListIndex -1].position+1;

    this.backendService.createList(newList).subscribe((list) => {
      newList.id = list.id;
      newList.position = list.position;
    });


  }

  deleteList(listId: number): void {
    const index = this.lcObject.lists.findIndex(
      (list) => list.id === listId
    );
    this.lcObject.lists.splice(index, 1);

    this.backendService.deleteList(listId).subscribe();
  }

  currentView(currentList: ListComponent): void{
    if(this.view != null){
      this.view.setViewFalse();
      this.view = currentList;
    }
    else this.view = currentList;
  }
  showFlaggedCount(): number {
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
