import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from '@angular/common/http';


import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';

import { ListComponent } from '../lib/feature/listModule/list/list.component';
import { ListContainerComponent } from '../lib/feature/listModule/listContainer/listContainer.component';
import { ReminderComponent } from '../lib/feature/reminderModule/reminder/reminder.componet';
import { reminderContainerComponent } from '../lib/feature/reminderModule/reminderContainer/reminderContainer.component';
import { BackendService } from 'src/lib/data-access/service/backend.service';
@NgModule({
  declarations: [AppComponent, ListComponent, ListContainerComponent, ReminderComponent, reminderContainerComponent],
  imports: [BrowserModule, AppRoutingModule, HttpClientModule],
  bootstrap: [AppComponent],
})
export class AppModule {}
  