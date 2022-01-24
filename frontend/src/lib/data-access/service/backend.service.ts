import{ HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
//Vorerst weiterhin mit Klassen gelöst
import { List,  } from '../models/list';
import { Reminder } from '../models/reminder';
import { ListContainer } from '../models/listContainer';


@Injectable({
  providedIn: 'root',
})
    // Endpunkte müssen noch inplementiert werden!!!!
export class Backendservice {
  readonly url = 'http://localhost:4200';

  constructor(private httpClient: HttpClient){}

  loadListContainer(): Observable<ListContainer> {
    return this.httpClient.get<ListContainer>(this.url + '/api/lc');
  }

  createList(list: List): Observable<List> {
      let listPayload = {
        ...list,
      };

      return this.httpClient.post<List>(
        this.url + 'api/lc/lists', listPayload
      );
  }

  deleteList(listId: number): Observable<void> {
    return this.httpClient.delete<void>(
      this.url + 'api/lc/lists/' + listId
    );
  }

  updateList(list: Partial<List>): Observable<List> {
    let listPayload = {
      ...list,
    };

    return this.httpClient.put<List>(
      this.url +  'api/lc/lists/' + list.id, listPayload
    );
  }

  createReminder(reminder: Reminder): Observable<Reminder> {
    let reminderPayload = {
      ...reminder
    };

    return this.httpClient.post<Reminder>(
      this.url + '/api/lc/lists/', reminderPayload
    );
  }

  deleteReminder(reminderId: number): Observable<void>{
    return this.httpClient.delete<void>(
      this.url + 'api/lc/lists/'+ reminderId
    );
  }

  updateReminder(reminder: Reminder): Observable<Reminder> {
    let reminderPayload = {
      ... reminder
    };

    return this.httpClient.put<Reminder>(
      this.url + 'api/lists/', reminderPayload
    );
  }

}
