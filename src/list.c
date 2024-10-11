// list.c

#include "list.h"
#include <stddef.h>

// adds new_element to beginning of linked list
void list_add(struct list_element **list_head, struct list_element *new_element){
  new_element->next = *list_head;
  *list_head = new_element;
}

// removes element from linked list
// if element is head, point list_head to next element
void list_remove(struct list_element **list_head, struct list_element *element){
  if(*list_head == element) {
    *list_head = element->next;
  } else {
    struct list_element *tmp = *list_head;
    while (tmp && tmp->next != element){
      tmp = tmp->next;
    }
    if (tmp) {
      tmp->next = element->next;
    }
  }
}


int main(){
  struct list_element d;
  struct list_element c;
  struct list_element b = {&c,   0};
  struct list_element a = {&b,   0};
  struct list_element *head = &a;

  struct list_element *new_item = &d;

  list_add(&head, new_item);

  list_remove(&head, new_item);

  return 0;
}
