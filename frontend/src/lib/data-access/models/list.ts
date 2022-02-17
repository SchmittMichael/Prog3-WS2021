import { Reminder } from './reminder';
export interface List {
   id?: number;
   name : string;
   position?: number;
   reminders: Reminder[];
}
