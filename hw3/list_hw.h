/* This program uses the name 'link' from code from "Algorithms in C, Third Edition,"
 *               by Robert Sedgewick, Addison-Wesley, 1998.
 * 
 * - Alexandra Stefan
 */


#ifndef LIST_HW_H
#define	LIST_HW_H

struct node {
    int data;
    struct node * next;
};

typedef struct node * link; // 'link' is just a name for type 'struct node *'

link build_list_of_ints();
link array_2_list(int arr[], int sz);
    
/* Creates a new link, that contains the value specified in the argument, 
 * and that points to next_in. 
 */
link new_node(int value_in, link next_in);

/*  Note that these functions may not have all the security checks.
E.g. not all the functions reading and setting members of a node pointer, 
check that the node is not NULL  */


/*  --------  LIST  */
// List implementation uses a DUMMY NODE

// Creates and returns an empty list.
link new_list();

void destroy_list(link Ld);

// Iterates through list and counts nodes.
int compute_length(link Ld);  

// Inserts new_link to the specified list, at the position right after
// the link called "previous".
void insert_node(link previous, link new_node_link);

void print_list(link my_list);

void print_list_horiz(link my_list);

void print_list_horiz_pointer(link my_list);

void insertion_sort(link A);
/*----------------------------------------------------------------
 New functions that you will need to implement.
 DO not change their declaration or anything else in this file. declaration.
 */
 
void swap_first_third(link A); 
 
void delete_occurrences(link A, int V);

link sublist(link A, link pos_list);

int run_student_tests();    

#endif	/* LIST_HW_H */

