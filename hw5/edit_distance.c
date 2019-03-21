#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "edit_distance.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as
they are declared before the array in the parameter list. See:
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/
*/
int min(int a,int b,int c)
{
	int d = 0;
	 while (a &&  b&& c) {
			 a--;
			 b--;
			 c--;
			 d++;
	 }
	 return d;
}

int edit_distance(char * first_string, char * second_string, int print_table){
int i,x,z,y,char_numberx,char_numbery;
char first[2],second[2];
int edit_distance=0;
int size_of_first=strlen(first_string);
int size_of_second=strlen(second_string);
int distance_matrix[size_of_first+1][size_of_second+1];
char_numberx=0;
char_numbery=0;
for(z=0;z<=size_of_first;z++)
{
	distance_matrix[z][0]=z;
}

for(z=0;z<=size_of_second;z++)
{
	distance_matrix[0][z]=z;
}


for(y=1;y<=size_of_second;y++)
{
	for(x=1;x<=size_of_first;x++)
	{
		//printf("\n\n%c\n\n",first_string[x-1]);
	//	printf("\n\n%c\n\n",second_string[y-1]);

		strncpy(first,first_string+(x-1),1);
		strncpy(second,second_string+(y-1),1);
	//	printf("%s %s",first,second);
		if(strncmp(first,second,1)==0)
		{
			distance_matrix[x][y]=distance_matrix[x-1][y-1];

		}
		else
		{

			distance_matrix[x][y]=min(distance_matrix[x-1][y],distance_matrix[x][y-1],distance_matrix[x-1][y-1])+1;

		}

	}
}

edit_distance=distance_matrix[x-1][y-1];
//printf("\n\n%d\n\n",distance_matrix[1][1]);
if(print_table)
{
for(y=0;y<=size_of_first+1;y++)
{
	for(x=0;x<=size_of_second+1;x++)
	{
		if(x>1&&y==0)
		{
			printf("%2c|",second_string[char_numberx]);
			char_numberx++;
		}

		else if(x==0&&y>=2)
		{
			printf("%2c|",first_string[char_numbery]);
			char_numbery++;
		}
		else if(x<2&&y==0)
		{
			printf("  |");
		}
		else if(x==0&&y<2)
		{
			printf("  |");
		}


		else
		{
			printf("%2d|",distance_matrix[y-1][x-1]);

		}
	}
	printf("\n");
	for(i=0;i<=size_of_second+1;i++)
	{
		printf("---");
	}

	printf("\n");
}
}
	return edit_distance;  // replace this line with your code
}


void spellcheck(char * dictname, char * testname){
	int i,z,edit_distance_value,minimum_value;

	FILE *fp;
	FILE *fp1;
	int size_of_dictionary,size_of_test;
	int minimum_index=0;
	fp=fopen(dictname,"r");
	    if(fp==NULL)
	    {
	      printf("\nFile Not Found !! 404 !! \n\n");
				fclose(fp);

	    }

fscanf(fp,"%d",&size_of_dictionary);
char* dictionary[size_of_dictionary];
int minimum_value_index_storage[size_of_dictionary];
for(i=0;i<size_of_dictionary;i++)
{
	dictionary[i]=malloc (128);
	fscanf(fp,"%127s",dictionary[i]);
}

fp1=fopen(testname,"r");
		if(fp1==NULL)
		{
			printf("\nFile Not Found !! 404 !! \n\n");
			fclose(fp1);
		}

fscanf(fp1,"%d",&size_of_test);
char* test[size_of_test];
for(i=0;i<size_of_test;i++)
{
	test[i]=malloc (128);
	fscanf(fp1,"%127s",test[i]);
}

for(i=0;i<size_of_test;i++)
{
	minimum_value=edit_distance(test[i],dictionary[0],0);
	minimum_value_index_storage[0]=0;
	for(z=1;z<size_of_dictionary;z++)
	{
		edit_distance_value=edit_distance(test[i],dictionary[z],0);
		if(minimum_value>edit_distance_value)
		{
			minimum_value=edit_distance_value;
			minimum_index=0;
			minimum_value_index_storage[0]=z;
		}
		else if(minimum_value==edit_distance_value)
		{
			minimum_index++;
			minimum_value_index_storage[minimum_index]=z;
		}
	}
	printf("\n-------Current Test Word: %s",test[i]);
	printf("\nMinimum distance: %d",minimum_value);
	printf("\nWords that give minimum distance: \n");
	for(z=0;z<=minimum_index;z++)
	{
		printf("%s\n",dictionary[minimum_value_index_storage[z]]);
	}
}

  for (i =0; i<size_of_dictionary;i++)
	{
    free (dictionary[i]);

	}
	for(i=0;i<size_of_test;i++)
	{
		free(test[i]);
	}

fclose(fp);
fclose(fp1);


printf("AAAAAAA");

}
