import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild
} from '@angular/core';
import { BackendService } from 'src/lib/data-access/service/backend.service';
import { Reminder } from '../../../data-access/models/reminder';

@Component({
  selector: 'reminder',
  templateUrl: './reminder.componet.html',
  styleUrls: ['./reminder.componet.scss'],
})
export class ReminderComponent implements AfterViewInit {
  @Input() reminderObject: Reminder;
  @Input() selectedOnCreate: boolean;
  @Input() listId: number;
  @Output() clickDeleteEvent = new EventEmitter<number>();

  @ViewChild('myInput') myInput: ElementRef;

  showCalender: boolean = false;
  elementRef: ElementRef;
  deleteTrigger: boolean = false;

  constructor(private backendService: BackendService) {}

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
        this.clickDeleteEvent.emit(this.reminderObject.id);
        console.log('delete succesfull');
      }
      else console.log('delete failed')
    }
  }

  mouseOutEvent(): void {
    this.showCalender = false;
  }

  clickEvent(): void {
    this.clickDeleteEvent.emit(this.reminderObject.id);
  }

  editTitle(event: any): void {
    this.reminderObject.title = event.target.value;
    if(this.reminderObject.title == "easteregg"){this.reminderObject.easteregg = true;}
    this.backendService.updateReminder(this.listId, this.reminderObject).subscribe();
  }

  editDate(event: any): void {
    this.reminderObject.date= event.target.value;
    this.backendService.updateReminder(this.listId, this.reminderObject).subscribe();
  }

  editFlag(): void {
    this.reminderObject.flag = this.reminderObject.flag ? false : true;
    this.backendService.updateReminder(this.listId, this.reminderObject).subscribe();
  }
}
