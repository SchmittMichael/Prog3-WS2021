import {
  OnInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild,
} from '@angular/core';
import { List } from '../../../data-access/list';
import { ListContainer } from '../../../data-access/listContainer';

@Component({
  selector: 'listContainer',
  templateUrl: './listContainer.component.html',
  styleUrls: ['./listContainer.component.scss']
})

export class ListContainerComponent implements OnInit{
  @Input() selectedOnCreate: boolean;
  @Input() color: string = '#29b9e6';
  @Output() clickDeleteEvent = new EventEmitter<number>();

  @ViewChild('myInput') myInput: ElementRef;

  lcObject: ListContainer;
  selected: List;

    ngOnInit(): void {
      this.lcObject = new ListContainer();
    }

    createNewList(input: any): void {
      this.selected = this.lcObject.addList();
    }

    deleteList(id: number): void {
      this.lcObject.removeList(id);
    }
}
