import {
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild
} from '@angular/core';
import { List } from '../../../data-access/list';
import { ListContainer } from '../../../data-access/listContainer';

@Component({
  selector: 'listContainer',
  templateUrl: './listContainer.component.html',
  styleUrls: ['./listContainer.component.scss']
})

export class ListContainerComponent{
  @Input() lcObject: ListContainer;
  @Input() selectedOnCreate: boolean;
  @Input() color: string = '#000000';
  @Output() clickDeleteEvent = new EventEmitter<number>();

  @ViewChild('myInput') myInput: ElementRef;

    selectedObject: List;
    elementRef: ElementRef;

    ngOnInit(): void {
      this.lcObject = new ListContainer();
    }

    createNewList(input: any): void {
      this.selectedObject = this.lcObject.addList();
    }

    deleteList(id: number): void {
      this.lcObject.removeList(id);
    }
}
