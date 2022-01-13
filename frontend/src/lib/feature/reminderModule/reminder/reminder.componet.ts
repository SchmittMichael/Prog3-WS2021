import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild
} from '@angular/core';
import { Reminder } from '../../../data-access/reminder';

@Component({
  selector: 'reminder',
  templateUrl: './reminder.componet.html',
  styleUrls: ['./reminder.componet.scss']
})

export class ReminderComponent implements AfterViewInit{
  @Input() reminderObject: Reminder;
  @Input() selectedOnCreate: boolean;
  @Output() clickDeleteEvent = new EventEmitter<number>();

  @ViewChild('myInput') myInput: ElementRef;

  showCalender: boolean = false;
  elementRef: ElementRef;

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.myInput.nativeElement.focus();
    }
  }

  hoverEvent(): void{
    this.showCalender = true;
  }

  mouseOutEvent(): void {
    this.showCalender = false;
  }

  clickEvent(): void {
    this.clickDeleteEvent.emit(this.reminderObject.getID());
  }

  editName(event: any): void {
    this.reminderObject.setTitle(event.target.value);
  }

  editDate(event: any): void {

  }

  editFlag(event: any): void{
    this.reminderObject.flag = (this.reminderObject.flag)? false : true;
    console.log(this.reminderObject.flag)
  }
}
