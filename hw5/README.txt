Compilation Instructions
1)Compilation
gcc -g edit_distance_client.c edit_distance.c

2)Execution with MEMCHECK.
valgrind --leak-check=full ./a.out <data1.txt
