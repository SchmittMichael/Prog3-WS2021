import { AfterViewInit, Component, OnInit } from '@angular/core';
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

  flagged: List;
  today: List;

  newListIndex?: number;

  constructor(private backendService: BackendService) {}

  ngOnInit(): void {
    this.lcObject = {name:"OfflineLc", lists:[]};   //Fix dafür dass er nicht jedes mal die Konsole volspamt mit "ERROR TypeError: Cannot read properties of undefined (reading 'lists')"
    this.backendService.loadListContainer().subscribe( (lc:ListContainer) => (this.lcObject = lc));

    this.flagged = {name:"OfflineFlagged", reminders:[]}
    this.backendService.loadFlaggedReminders().subscribe( (flagged:List) => this.flagged = flagged);

    this.today = {name:"OfflineToday", reminders:[]}
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
    if(this.view != null){
      this.view.setViewFalse();
      this.view = currentList;
    }
    else this.view = currentList;
  }

}
