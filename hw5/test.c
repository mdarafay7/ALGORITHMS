#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  int i;
  char * lines[4];
  FILE *file_handle = fopen ("data1.txt", "r");

  for (i =0; i < 4; ++i) {
    lines[i] = malloc (128); /* allocate a memory slot of 128 chars */
    fscanf (file_handle, "%127s", lines[i]);
  }

  for (i =0; i < 4; ++i)
    printf ("%d: %s\n", i, lines[i]);

  for (i =0; i < 4; ++i)
    free (lines[i]); /* remember to deallocated the memory allocated */

  return 0;
}
