import { Component, Input } from '@angular/core';
import { Reminder } from '../../../data-access/models/reminder';
import { reminderContainer } from '../../../data-access/models/reminderContainer';

@Component({
  selector: 'reminderContainer',
  templateUrl: './reminderContainer.component.html',
  styleUrls: ['./reminderContainer.component.scss'],
})
export class reminderContainerComponent {
  @Input() rcObject: reminderContainer;

  selectedObject: Reminder;

  createNewReminder(): void {
    console.log('neuer Reminder erstellt');
    this.selectedObject = this.rcObject.addReminder();
  }

  deleteReminder(id: number): void {
    this.rcObject.removeReminder(id);
  }

  showName(): string {
    return this.rcObject.getName();
  }

  showCount(): number {
    return this.rcObject.getCount();
  }
}
