import {
  Component, EventEmitter,
  Input,
  Output
} from '@angular/core';
import { List } from '../../../data-access/list';

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss']
})

export class ListComponent{

  @Input() listObject: List;
  @Input() selectedOnCreate: boolean;
  @Input() color: string = '#000000';
  @Output() editName = new EventEmitter<number>();


  clickEvent(): void {
    this.editName.emit(this.listObject.getID());
  }

  editValue(event: any): void {
    this.listObject.setListTitle(event.target.value);
  }

}
