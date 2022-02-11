import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild
} from '@angular/core';
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

  @ViewChild('myInput') myInput: ElementRef;

  elementRef: ElementRef;
  showContainer: boolean;

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.myInput.nativeElement.focus();
    }
  }

  clickEvent(): void {
    console.log("Delete Click erkannt")
    this.clickDeleteEvent.emit(this.listObject.getID());
  }

  editTitle(event: any): void {
    this.listObject.setTitle(event.target.value);
  }

  showRemCon(): void {
    this.changeViewEvent.emit(this);
    this.showContainer = true
  }

  setViewFalse(): void{
    this.showContainer = false;
  }

  showRemConCount(): number{
    return this.listObject.getRemConCount();
  }
}
