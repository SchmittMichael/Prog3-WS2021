export interface Reminder {
  id?: number;
  title: string;
  listId: number;
  position: number;
  date?: Date;
  flag?: boolean;

}
