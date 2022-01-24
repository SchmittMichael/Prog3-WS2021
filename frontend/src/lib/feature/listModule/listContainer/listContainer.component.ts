import { Component, OnInit } from '@angular/core';
import { List } from '../../../data-access/models/list';
import { ListContainer } from '../../../data-access/models/listContainer';

@Component({
  selector: 'listContainer',
  templateUrl: './listContainer.component.html',
  styleUrls: ['./listContainer.component.scss'],
})
export class ListContainerComponent implements OnInit {
  lcObject: ListContainer;
  selected: List;

  ngOnInit(): void {
    this.lcObject = new ListContainer();
  }

  createNewList(): void {
    this.selected = this.lcObject.addList();
  }

  deleteList(id: number): void {
    this.lcObject.removeList(id);
  }
}
