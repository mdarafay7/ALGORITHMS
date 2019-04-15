#include <stdio.h>
#include <stdlib.h>

// Do not modify main
int main(int argc, char** argv) {
	int N, res1,res2;
	printf("Enter N: ");
	scanf("%d",&N);

	while (N!= -1){
		printf("Calling foo_iterative(N)\n");
		res1 = foo_iterative(N);
		printf("Result of iterative function for N=%d is: %d\n", N, res1);

		printf("Calling foo_wrapper(N)\n");
		res2 = foo_wrapper(N);
		printf("Result of memoized function for N=%d is: %d\n", N, res2);

		printf("\n--------------------------------\nEnter N: ");
		scanf("%d",&N);
	}
	return (EXIT_SUCCESS);
}

// Use this method to print the data for foo_memoized at different depth.
void print_at_depth(int depth, int N){
	int i;
	printf("\n");
	for(i=0;i<depth; i++){
		printf("   ");
	}
	printf("N = %d, depth = %d\n", N, depth);
}


int foo_iterative(int N){
	int res1,res2;
  res1=5;
  res2=5;
  for(int i=N;i>1;i=i/2)
  {
    res1=res1*3;
  }
  if(res1>=res2)
  {
    return res1;
  }
  else
  {
    return res2;
  }
	return -1;  // TO DO: write your code in here
}

// This method should call foo_memoized
int foo_wrapper(int N){
 	int sol[N+1];
	int level;
	for(int i=0;i<N+1;i++)
	{
		sol[i]=0;
	}
	int result=foo_memoized(N,sol,0,0);
	return result; // TO DO: write your code in here.
}

int foo_memoized(int N,int *w,int level)
{
 print_at_depth(level,N);

 if(w[N])
 {
	 return w[N];
 }
 if (N <= 1)
 {
	 return 5;}

 int res1 = 3*foo_memoized(N/2,w,level+1);
 int res2 = foo_memoized(N-1,w,level+1);
 if (res1 >= res2)
 {
	 	w[N]=res1;
	  return res1;
	}
 else
 {
	 w[N]=res2;
   return res2;
	}
}
