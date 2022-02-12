import { ThrowStmt } from '@angular/compiler';
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

@Component({
  selector: 'reminder',
  templateUrl: './reminder.componet.html',
  styleUrls: ['./reminder.componet.scss'],
})
export class ReminderComponent implements AfterViewInit {
  @Input() reminderObject: Reminder;
  @Input() selectedOnCreate: boolean;
  @Output() clickDeleteEvent = new EventEmitter<number>();

  @ViewChild('myInput') myInput: ElementRef;

  showCalender: boolean = false;
  elementRef: ElementRef;
  deleteTrigger: boolean = false;

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.myInput.nativeElement.focus();
    }
  }

  hoverEvent(): void {
    this.showCalender = true;
  }

  async deleteReminder() {
    this.deleteTrigger = !this.deleteTrigger;
    if(this.deleteTrigger== true){
      await new Promise((resolve) => setTimeout(resolve, 3000));
      if(this.deleteTrigger== true){
        this.clickDeleteEvent.emit(this.reminderObject.getID());
        console.log('delete succesfull');
      }
      else console.log('delete failed')
    }
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

  editDate(event: any): void {}

  editFlag(event: any): void {
    this.reminderObject.flag = this.reminderObject.flag ? false : true;
  }
}
