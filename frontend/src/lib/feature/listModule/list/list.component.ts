import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild,
} from '@angular/core';
import { List } from '../../../data-access/list';

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent implements AfterViewInit {
  @Input() listObject: List;
  @Input() selectedOnCreate: boolean;
  @Input() color: string = '#000000';
  @Output() clickDeleteEvent = new EventEmitter<number>();

  @ViewChild('myInput') myInput: ElementRef;

  elementRef: ElementRef;

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      console.log("In fokus")
      this.myInput.nativeElement.focus();
    }
  }

  clickEvent(): void {
    this.clickDeleteEvent.emit(this.listObject.getID());
  }

  editTitle(event: any): void {
    this.listObject.setTitle(event.target.value);
  }
}
