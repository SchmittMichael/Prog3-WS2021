import { Component, EventEmitter, Input, Output } from '@angular/core';

@Component({
  selector: 'addButton',
  templateUrl: './addButton.component.html',
  styleUrls: ['./addButton.component.scss'],
})
export class addButtonComponent {
  @Input() backgroundColor: string = '#d6d6d6';
  @Input() borderRadius: string = '15px';
  @Output() newClickEvent = new EventEmitter<any>();

  clickEvent(): void {
    this.newClickEvent.emit();

  }
}
