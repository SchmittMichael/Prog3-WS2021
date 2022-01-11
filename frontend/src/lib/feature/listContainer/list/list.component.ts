import {
  Component, Input
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





}
