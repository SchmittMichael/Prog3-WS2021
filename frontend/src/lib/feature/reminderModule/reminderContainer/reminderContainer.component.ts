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
import { reminderContainer } from '../../../data-access/reminderContainer';

@Component({
  selector: 'reminderContainer',
  templateUrl: './reminderContainer.component.html',
  styleUrls: ['./reminderContainer.component.scss']
})

export class reminderContainerComponent{
    @Input() rcObject: reminderContainer;
    @Input() selectedOnCreate: boolean;
    @Input() color: string = '#000000';
    @Input()
    @Output() clickDeleteEvent = new EventEmitter<number>();

    @ViewChild('myInput') myInput: ElementRef;

    selectedObject: Reminder;
    elementRef: ElementRef;

    ngAfterViewInit(): void {
      if (this.selectedOnCreate) {
        this.myInput.nativeElement.focus();
      }
    }

    clickEvent(): void {
      this.clickDeleteEvent.emit(this.rcObject.getID());
    }

    createNewReminder(input: any): void {
      this.selectedObject = this.rcObject.addReminder();
    }

    deleteReminder(id: number): void {
      this.rcObject.removeReminder(id);
    }

    showName():string {
      return this.rcObject.getName();
    }

    showCount():number {
      return this.rcObject.getCount();
    }
  }
