#include <stdlib.h>
#include <math.h>
#include <stdio.h>


int fill(FILE* file)
{
  char filename[15];
  char *filename_ptr=filename;
  int start_val,end_val,fill_amt,search_amt;
  printf("\nEnter: N S start_val end_val filename(with extension):");
  scanf("%d %d %d %d %s",&fill_amt,&search_amt,&start_val,&end_val,filename_ptr);
  file=fopen(filename,"w+");
  fprintf(file,"%d %d %d %d\n",fill_amt,search_amt,start_val,end_val);
  int i;
  for (i = 0; i < fill_amt; i++) {
        int num = (rand() % (end_val - start_val + 1)) + start_val;
        fprintf(file,"%d ",num);
    }
    fprintf(file,"\n");
  for (i = 0; i < search_amt; i++) {
        int num = (rand() % (end_val - start_val + 1)) + start_val;
        fprintf(file,"%d ",num);
      }
  fclose(file);
}

int interpolated_search(int *array,int size,int x,int *reps)
{
  int start=0;
  int end=size-1;
  int  mid;
  while(start<=end && x>= array[start] && x<=array[end])
  {
    *reps=*reps+1;
    mid= (float)(start + (x - array[start])*(end - start) / (array[end] - array[start]));
    if(array[mid]==x)
    {
      return mid;
    }
    else if(x<array[mid])
    {
      end=mid-1;
    }
    else
    {
      start=mid+1;
    }
  }
  return -1;

}

int binary_search(int *array,int size,int x,int *reps)
{
  int start=0;
  int end=size-1;
  int mid;
  while(start<=end)
  {
    *reps=*reps+1;
    mid=(start+end)/2;
    if(array[mid]==x)
    {
      return mid;
    }
    else if(x<array[mid])
    {
      end=mid-1;
    }
    else
    {
      start=mid+1;
    }
  }
  return -1;

}

void insertion_sort(int *array,int size)
{
 int i;
  for(i=1;i<size;i++)
  {
    int key;
    key=array[i];
    int j=i-1;
    while(j>=0&&array[j]>key)
    {
      array[j+1]=array[j];
      j--;
    }
    array[j+1]=key;

  }
}

int main()
{
  char filename[25];
  char empty[100];
  char *filename_ptr=filename;
  int choice,i,start_val,end_val,fill_amt,search_amt,binary_reps,interpolation_reps,print_opt,binary_t_reps,interpolation_t_reps;
  float binary_avg,interpolation_avg;
  do{
  printf("0-exit\n1-create and save random data for search.\n2)Load data from file,sort array and run searches.\nEnter Your choice: ");
  scanf("%d",&choice);
  interpolation_t_reps=0;
  binary_t_reps=0;
  FILE *fp;
  if(choice==1)
  {
    fill(fp);
  }
  if(choice==2)
  {
    printf("\nEnter: filename, mode(1-verbose, 2-not verbose): ");
    scanf("%s %d",filename_ptr,&print_opt);
    fp=fopen(filename_ptr,"r");
    if(fp==NULL)
    {
      printf("\nFile Not Found !! 404 !! \n\n");
      continue;
    }
    fscanf(fp,"%d",&fill_amt);
    fscanf(fp,"%d",&search_amt);
    int values[fill_amt];
    int *valuearray_ptr=values;
    int values_search[search_amt];
    int binary_info[search_amt][2];
    int interpolation_info[search_amt][2];
    fgets(empty,100,fp);
    for(i=0;i<fill_amt;i++){
    fscanf(fp,"%d",&values[i]);
    }

    for(i=0;i<search_amt;i++){
    fscanf(fp,"%d",&values_search[i]);
    }

    insertion_sort(values,fill_amt);
    for(i=0;i<search_amt;i++)
    {
      binary_reps=0;
      int pos=binary_search(values,fill_amt,values_search[i],&binary_reps);
      binary_info[i][0]=pos;
      binary_info[i][1]=binary_reps;
      binary_t_reps=binary_t_reps+binary_reps;
    }
      binary_avg=(float)binary_t_reps/search_amt;
    for(i=0;i<search_amt;i++)
    {
      interpolation_reps=0;
      int pos=interpolated_search(values,fill_amt,values_search[i],&interpolation_reps);
      interpolation_info[i][0]=pos;
      interpolation_info[i][1]=interpolation_reps;
      interpolation_t_reps=interpolation_t_reps+interpolation_reps;
    }
      interpolation_avg=(float)interpolation_t_reps/search_amt;

    if(print_opt==1)
    {
    printf("\n|      |      | found at index  |    repititions  |\n");
    printf("|     i| value| interp| binary  | interp|  binary |\n");
    for(i=0;i<search_amt;i++)
    {
       printf("| %5d|%6d|%7d|%9d|%7d|%9d|\n",i,values_search[i],interpolation_info[i][0],binary_info[i][0],interpolation_info[i][1],binary_info[i][1]);

    }

       printf("|   avg|      |       |         |%7.2f|%9.2f|",interpolation_avg,binary_avg);
       printf("\n");
    }
    else if(print_opt==2)
    {
      printf("\n|      |      | found at index  |    repititions  |\n");
      printf("|     i| value| interp| binary  | interp|  binary |\n");
      printf("|   avg|      |       |         |%7.2f|%9.2f|",interpolation_avg,binary_avg);
      printf("\n");
    }
  if(choice==0)
  {
    exit(0);
  }
}

}while(choice!=0);
}
