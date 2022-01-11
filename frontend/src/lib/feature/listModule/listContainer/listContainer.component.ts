import {
  Component, Input
} from '@angular/core';
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
}
