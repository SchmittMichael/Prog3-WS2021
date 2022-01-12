import { Component, EventEmitter, Input, Output } from '@angular/core';

@Component({
  selector: 'listButton',
  templateUrl: './listButton.component.html',
  styleUrls: ['./listButton.component.scss'],
})
export class listButtonComponent {
  @Input() backgroundColor: string = '#d6d6d6';
  @Input() borderRadius: string = '15px';
  @Output() newClickEvent = new EventEmitter<any>();

  clickEvent(): void {
    this.newClickEvent.emit();

  }
}
