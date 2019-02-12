/* This program uses the name 'link' from code from "Algorithms in C, Third Edition,"
*               by Robert Sedgewick, Addison-Wesley, 1998.
*
* - Alexandra Stefan
*/

#include <stdio.h>
#include <stdlib.h>

#include "list_hw.h"

// ------------- Node functions

/* Creates a new link, that contains the value specified in the argument,
* and that points to next_in.
*/
link new_node(int value_in,  link next_in) {
  link result = (link) malloc(sizeof (struct node));
  result->data = value_in;
  result->next = next_in;
  return result;
}

/*    --------  LIST functions    */
// List implementation uses a DUMMY NODE

/* Creates and returns an empty list. */
link new_list() {
  link dummy = new_node(0,NULL);
  return dummy;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroy_list(link Ld) {
  link current = Ld;
  while (current != NULL) {
    link next = current->next;
    free(current);
    current = next;
  }
}

// Inserts new_link after the link called "previous".
void insert_node(link previous, link new_node_link) {
  if (previous == NULL) {
    printf("\n Cannot insert after a NULL node. No action taken.");
  } else {
    new_node_link->next = previous->next;
    previous->next = new_node_link;
  }
}

// Returns 0 for empty lists (have just one dummy node) and NULL lists
int compute_length(link Ld) {
  if (Ld == NULL) {
    return 0;
  }

  int counter = 0;
  link curr;
  for (curr = Ld->next; curr != NULL; curr = curr->next) {
    counter++;
  }
  return counter;
}


void print_list(link my_list) {
  if (my_list == NULL) {
    printf("\n<print_list> : list is NULL\n");
    return;
  }
  int i = 0;
  link curr;
  printf("\n List items:\n");
  for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
    printf("item %d: %d\n", i, curr->data);
    i++;
  }
  printf(" Length of above list = %d\n", i);
}

void print_list_horiz(link my_list) {
  if (my_list == NULL) {
    printf("\n<print_list_horiz> : List is NULL\n");
    return;
  }
  int i = 0;
  link curr;

  printf("\n List items: ");
  for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
    printf("%5d    ", curr->data);
    i++;
  }
  printf("\n Length of above list = %d\n", i);
}

void print_list_horiz_pointer(link my_list) {
  if (my_list == NULL) {
    printf("\n<print_list_horiz_pointer> : List is NULL\n");
    return;
  }

  int i = 0;
  link curr;
  printf("\n List items:    ");
  for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
    printf("%-11d ", curr->data);
    i++;
  }
  printf("\n List pointers: ");
  for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
    printf("%p ", curr);
    i++;
  }
  printf("\n Length of above list = %d\n", i);
}

// Sorts List A IN PLACE, using insertion sort by MOVING node,NOT copying node content
// O(N^2) time,
// O(1) data moves. Here pointer copying is counted as a constant operation, NOT a data move.
// The data in the nodes is not copied, only the links are updated.
void insertion_sort(link Ad) {
  link c,p;      // Current and Previous in outer loop
  link cl,pl;    // Current and Previous in Left loop
  p = Ad->next;
  c = p->next;
  while (c != NULL){
    pl = Ad;
    cl = pl->next;
    while ((cl->data <= c->data) && (cl != c)){
      pl = pl->next;
      cl = cl->next;
    }
    if (cl!=c){
      // move c between pl and cl
      p->next = c->next;
      pl->next = c;
      c->next = cl;

      // update temp variable c.
      // do NOT update p.
      c = p->next;
    }
    else { // c was not moved. Must update both p and c
      p=c;
      c=c->next;
    }
  }
  return;
}


/*----------------------------------------------------------------
New functions.
Finish their implementation below.
If you need to use helper functions you can define them and use them in this file.
***You should not change the behavior of any of the functions defined above.***
*** You should only write code in this file. DO not modify the client file in any way. You will NOT submit the client file.

NOTE: that the functions:
link array_2_list(int arr[], int sz)
link build_list_of_ints()
are implemented and used in the instructor_client.c file,
BUT YOU CAN ALSO CALL THEM AND USE THEM IN YOUR run_student_tests function,
or any other helper function that you write here, in list_hw.c
*/

link sublist(link A, link pos_list) {
  link sub_list=new_list();
  link temp_sub_list=sub_list;
  link position_parser=pos_list->next;;
  link temp;
  while(position_parser!=NULL)
  {
    temp=A;
    int position=position_parser->data;
    position_parser=position_parser->next;
    int i;
    for(i=0;i<=position;i++)
    {
      temp=temp->next;
    }
    link new_insertion=new_node(temp->data,NULL);
    insert_node(temp_sub_list,new_insertion);
    temp_sub_list=temp_sub_list->next;
  }

  return sub_list;
}

void swap_first_third(link A) {
  if(compute_length(A)==1)
  {
    return;
  }
  else if(compute_length(A)==2)
  {
    link store_first=A->next;
    link store_second=A->next->next;
    A->next=store_second;
    A->next->next=store_first;
    A->next->next->next=NULL;
  }
  else
  {
    int i;
    link store_first=A->next;
    link store_second=A->next->next;
    link store_third=A->next->next->next;
    link store_fourth=A->next->next->next->next;
    store_third->next=store_second;
    A->next=store_third;
    A->next->next->next=store_first;
    A->next->next->next->next=store_fourth;
    return;
  }
}

void delete_occurrences(link A, int V) {
  link prev_value_marker=A;
  link list_parser=A->next;
  int i;
  for(i=0;i<compute_length(A);i++)
  {
    link temp=list_parser;
    if(list_parser->data==V)
    {
      prev_value_marker->next=list_parser->next;
      list_parser=list_parser->next;
      free(temp);

    }
    else{
      list_parser=list_parser->next;
      prev_value_marker=prev_value_marker->next;
    }
  }

  return;
}

// Set-up and call your testing functions from this function.
int run_student_tests() {
  printf("\n Running function run_student_test.\n ");
  printf("\n\n--------------------------------------\n");

}
