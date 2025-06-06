import { Component, OnInit } from '@angular/core';
import { List } from '../../../data-access/models/list';
import { ListContainer } from '../../../data-access/models/listContainer';
import { ListComponent } from '../list/list.component';
import { BackendService } from '../../../data-access/service/backend.service'
import { Reminder } from '../../../data-access/models/reminder';

@Component({
  selector: 'listContainer',
  templateUrl: './listContainer.component.html',
  styleUrls: ['./listContainer.component.scss'],
})
export class ListContainerComponent implements OnInit {
  lcObject?: ListContainer;
  view: ListComponent;

  flagged: List;
  today: List;

  newListIndex?: number;

  constructor(private backendService: BackendService) {}

  ngOnInit(): void {
    this.lcObject = {name:"Offline Reminder", lists:[]};
    this.backendService.loadListContainer().subscribe( (lc:ListContainer) => (this.lcObject = lc));

    this.flagged = {name:"Offline Flagged", reminders:[]}
    this.backendService.loadFlaggedReminders().subscribe( (flagged:List) => this.flagged = flagged);

    this.today = {name:"Offline Today", reminders:[]}
    this.backendService.loadTodayReminders().subscribe( (today:List) => this.today = today);
  }

  createNewList(): void {
    let newList: List = { name: "", reminders:[]};
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

  updateTF(input: Reminder[]):void{
    if(input[0]!=undefined){
      this.today.reminders.push(input[0]);
    }
    else if(input[1]!=undefined){
      const index = this.today.reminders.findIndex(rem => rem === input[1]);
      this.today.reminders.splice(index, 1);
    }
    else if(input[2]!=undefined){
      this.flagged.reminders.push(input[2]);
    }
    else if(input[3]!=undefined){
      const index = this.flagged.reminders.findIndex(rem => rem === input[3]);
      this.flagged.reminders.splice(index, 1);
    }
  }

  changeViewToFlagged(){
    if(this.view != undefined) this.view.setViewFalse();
    this.today.position = 0;
    this.flagged.position = 1;
  }

  changeViewToToday(){
    if(this.view != undefined) this.view.setViewFalse();
    this.flagged.position = 0;
    this.today.position = 1;
  }

  currentView(currentList: ListComponent): void{
    this.flagged.position = 0;
    this.today.position = 0;
    if(this.view != null){
      this.view.setViewFalse();
      this.view = currentList;
    }
    else this.view = currentList;
  }

}
