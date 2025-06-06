import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { List } from '../models/list';
import { ListContainer } from '../models/listContainer';
import { Reminder } from '../models/reminder';


@Injectable({
  providedIn: 'root',
})
    // Endpunkte müssen noch inplementiert werden!!!!
export class BackendService {
  readonly url = 'http://localhost:4200';

  constructor(private httpClient: HttpClient) {}

  loadListContainer(): Observable<ListContainer> {
    return this.httpClient.get<ListContainer>(this.url + '/api/lc');
  }

  loadFlaggedReminders(): Observable<List> {
    return this.httpClient.get<List>(this.url + '/api/lc/flagged/reminders');
  }

  loadTodayReminders(): Observable<List> {
    return this.httpClient.get<List>(this.url + '/api/lc/today/reminders')
  }

  createList(list: List): Observable<List> {
      let listPayload = {
        ...list,
      };

      return this.httpClient.post<List>(
        this.url + '/api/lc/lists', listPayload
      );
  }

  deleteList(listId: number): Observable<void> {
    return this.httpClient.delete<void>(
      this.url + '/api/lc/lists/' + listId
    );
  }

  updateList(list: Partial<List>): Observable<List> {
    let listPayload = {
      ...list,
    };

    return this.httpClient.put<List>(
      this.url +  '/api/lc/lists/' + list.id, listPayload
    );
  }

  createReminder(listId: number, reminder: Reminder): Observable<Reminder> {
    let reminderPayload = {
      ...reminder,
    };

    return this.httpClient.post<Reminder>(
      this.url + '/api/lc/lists/'+listId+'/reminders', reminderPayload
    );
  }

  deleteReminder(listId:number, reminderId: number): Observable<void>{
    return this.httpClient.delete<void>(
      this.url + '/api/lc/lists/'+listId +'/reminders/'+ reminderId
    );
  }

  updateReminder(listId: number, reminder: Partial<Reminder>): Observable<Reminder> {
    let reminderPayload = {
      ... reminder,
    };

    return this.httpClient.put<Reminder>(
      this.url + '/api/lc/lists/'+listId +'/reminders/'+ reminder.id, reminderPayload
    );
  }



}
