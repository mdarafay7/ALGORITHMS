#include<stdio.h>
#include<stdlib.h>

#include "list_hw.h"

// Builds and returns a list with integers read from standard input.
 link build_list_of_ints() {
   link Ld = new_list();
   link last_node = Ld; // the last (and only) node in the list is the dummy node.
   while(1)
   {
      int number;
      printf("please enter an integer: ");
      int items_read = scanf("%d", &number);
      if (items_read != 1)  // There are no more integers in the read buffer => STOP
      {
         break;
      }

      // allocate memory for the next link
      link new_node_ptr = new_node(number, NULL);
      insert_node(last_node, new_node_ptr);
      last_node = new_node_ptr;
   }
   return Ld;
}


link array_2_list(int arr[], int sz)  {
	int i;
	link last_node, new_node_ptr;
	link A = new_list();

	last_node = A;  // the last (and only) node of A is the dummy node.
	for (i = 0; i < sz; i++) 	{
		new_node_ptr = new_node(arr[i], NULL);
		insert_node(last_node, new_node_ptr);
		last_node = new_node_ptr;
	}
	return A;
}


int test_swap_first_third(link A) {
    printf("\n\n--------------------------------------\n");
    printf("Test swap_first_third (for lists of ints).\n\n");
    printf("LIST A:");
    print_list_horiz_pointer(A);

    swap_first_third(A);

    printf("After calling swap_first_third(A) (currently not implemented).\n");
    printf("After you implement this function, list A (printed below).\n");
    print_list_horiz_pointer(A);

    printf("\n----------  end test function -------------------\n");
    return 0;
}

int test_insertion_sort(link A) {
    printf("\n\n--------------------------------------\n");
    printf("Testing insertion sort (for lists of ints).\n\n");
    printf("original list A:");
    print_list_horiz_pointer(A);

	insertion_sort(A);

    printf("SORTED A:");
    print_list_horiz_pointer(A);
    return 0;
}


int test_sublist(link A) {
    printf("\n\n--------------------------------------\n");
    printf("Testing sublist (for lists of ints).\n\n");
    printf("original list A:");
    print_list_horiz_pointer(A);

    int arr_pos[] = {3, 0, 6, 4};
    link pos_list = array_2_list(arr_pos, 4);
    printf("List with positions pos_list:");
    print_list_horiz(pos_list);

    link res = sublist(A, pos_list);
    destroy_list(pos_list);

    printf("SUBLIST:");
    print_list_horiz_pointer(res);
    destroy_list(res);

    printf("original list A:");
    print_list_horiz_pointer(A);
    return 0;
}

int test_delete_occurrences(link A) {
    printf("\n\n--------------------------------------\n");
    printf("Test delete_occurrences (for lists of ints).\n\n");
    printf("LIST A:");
    //print_list_horiz(A);
    print_list_horiz_pointer(A);

    delete_occurrences(A, 7);

    printf("After calling delete_occurrences(A,7) (currently not implemented).\n");
    printf("After you implement this function, list A (printed below) should not have any values of 7.\n");
    //print_list_horiz(A);
    print_list_horiz_pointer(A);

    printf("\n----------  end test function -------------------\n");
    return 0;
}

int main() {
    link A = NULL;
    int arr[] = {15, 100, 7, 5, 100, 7, 30};
    A = array_2_list(arr, 7);
    //A = buildListOfInts() ;  // use this line and redirect input to run test cases from data files. See posted example data file.
    printf("LIST A:");
    print_list_horiz_pointer(A);

    test_sublist(A);
    test_delete_occurrences(A);
	test_swap_first_third(A);

    destroy_list(A);

	printf("\n===========================================\n");
	printf("\n       END of INSTRUCTOR TESTS             \n");
	printf("\n===========================================\n");

	printf("\n\n\n     RUN STUDENT TESTS             \n");
	run_student_tests();

    return 0;
}
