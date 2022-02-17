import { Component, Input, Output } from '@angular/core';
import { BackendService } from 'src/lib/data-access/service/backend.service';
import { Reminder } from '../../../data-access/models/reminder';

@Component({
  selector: 'reminderContainer',
  templateUrl: './reminderContainer.component.html',
  styleUrls: ['./reminderContainer.component.scss'],
})
export class reminderContainerComponent {
  @Input() reminders: Reminder[];
  @Input() name: string;
  @Input() id: number;


  selectedObject: Reminder;
  newReminderIndex: number;

  constructor(private backendService: BackendService) {}

  createNewReminder(): void {
    let newReminder: Reminder = { title: '', position: 0, date:""};
    this.newReminderIndex = this.reminders.push(newReminder) -1;
    newReminder.position = (this.newReminderIndex === 0)? 1 : this.reminders[this.newReminderIndex -1].position + 1;

    this.backendService
      .createReminder(this.id, newReminder).subscribe((reminder) => {
        newReminder.id = reminder.id;
        newReminder.position = reminder.position;
      });
  }

  deleteReminder(reminderId: number): void {
    const index = this.reminders.findIndex((reminder) => reminder.id === reminderId);
    this.reminders.splice(index, 1);

    console.log(reminderId)

    this.backendService.deleteReminder(this.id, reminderId).subscribe();
  }

}
