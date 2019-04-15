#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <ctype.h>
#include <signal.h>
#include <limits.h>
#include <math.h>
#define BUFFERSIZE 1000


typedef struct {
  char* key;
  char* meaning;
} ht_item;

typedef struct {
  int size;
  int count;
  ht_item items[29908];
} ht_hash_table;

 unsigned int hash_bash(char* string)
{

     int i, sum=0;
     for (i=0; i < strlen(string); i++)
    {sum=(int)(sum+string[i]*pow(128,(strlen(string)-(i+1))))%29881;}
    return sum;
}

unsigned int hash_bash2(char *string,int value)
{
  int i,sum=0;
  for(i=0;i<strlen(string);i++)
  {
    sum=(int)(sum+string[i]*pow(128,(strlen(string)-(i+1))))%29879;
  }
  return 1+sum;
}

 int insert(char *string,char *meaning, ht_item* item,ht_hash_table* collection)
{
  int x=0,position=0;
  position=(hash_bash(string)+hash_bash2(string,2))%29881;
  collection->items[position].key=string;
  collection->items[position].meaning=meaning;

}






int main(int argc, char** argv) {
  {
  int x=0,prob=0;
  unsigned int position;
  ht_item item;
  ht_hash_table collection;
  char word[BUFFERSIZE];
  char meaning[BUFFERSIZE];
  word[0]='1';
  //  printf("%s %s",word,meaning);

    while(strcmp(word,"Fatima\n"))
    {
      scanf("%s",word);
      if(!strcmp(word,"s"))
      {

      }
      if(!strcmp(word,"i"))
      {
        //fgets(meaning, BUFFERSIZE, stdin);
        //insert(word,meaning,&item,&collection);
      }
      else{
      fgets(meaning, BUFFERSIZE, stdin);
      position=(hash_bash(word)+hash_bash2(word,prob))%29881;
      collection.items[position].key=word;
      collection.items[position].meaning=meaning;
      printf("\n%d) %s || %s",prob,collection.items[position].key,collection.items[position].meaning);
      }
      prob++;

    }



	return (EXIT_SUCCESS);
}
}
