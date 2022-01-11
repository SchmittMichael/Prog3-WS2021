import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';

import { ListComponent } from '../lib/feature/listModule/list/list.component';
import { ListContainerComponent } from '../lib/feature/listModule/listContainer/listContainer.component';
import { ReminderComponent } from '../lib/feature/reminderModule/reminder/reminder.componet';
import { reminderContainerComponent } from '../lib/feature/reminderModule/reminderContainer/reminderContainer.component';
import { listButtonComponent } from '../lib/feature/listModule/listButton/listButton.component';

@NgModule({
  declarations: [AppComponent, ListComponent, listButtonComponent, ListContainerComponent, ReminderComponent, reminderContainerComponent],
  imports: [BrowserModule, AppRoutingModule],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
