import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild
} from '@angular/core';
import { Reminder } from '../../../data-access/models/reminder';
import { BackendService } from '../../../data-access/service/backend.service';
import { List } from '../../../data-access/models/list';

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent implements AfterViewInit {
  @Input() listObject: List;
  @Input() selectedOnCreate: boolean;

  @Output() clickDeleteEvent = new EventEmitter<number>();
  @Output() changeViewEvent = new EventEmitter<ListComponent>();
  @Output() update_TF_Event = new EventEmitter<Reminder[]>();

  @ViewChild('myInput') myInput: ElementRef;

  elementRef: ElementRef;
  showContainer: boolean;

  constructor(private backendService: BackendService) {}

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.myInput.nativeElement.focus();
    }
  }

  clickEvent(): void {
    this.clickDeleteEvent.emit(this.listObject.id);
  }

  editName(event: any): void {
    this.listObject.name = event.target.value;
    this.backendService.updateList(this.listObject).subscribe();
  }

  showRemCon(): void {
    this.changeViewEvent.emit(this);
    this.showContainer = true
  }

  setViewFalse(): void{
    this.showContainer = false;
  }

  showRemConCount(): number{
    return this.listObject.reminders.length;
  }
}
