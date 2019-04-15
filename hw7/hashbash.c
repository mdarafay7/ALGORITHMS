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
  return value*sum;
}

 int insert(char *word,char *meaning, ht_item* item,ht_hash_table* collection)
{
  int position;
  position=(hash_bash(word))%29881;
  int prob=1;
  while(collection->items[position].key)
  {
    position=(hash_bash(word)+hash_bash2(word,prob))%29881;
    prob++;

  }
  prob=0;
  collection->items[position].key=word;
  collection->items[position].meaning=meaning;
  //printf("\n%d) %s || %s",prob,collection->items[position].key,collection->items[position].meaning);
}

int search(char *word,ht_item* item,ht_hash_table* collection)
{
  int position;
  position=(hash_bash(word))%29881;
  int prob=1;
  while(strcmp(collection->items[position].key,word)&&(prob<29881&&position<29881))
  {
    position=(hash_bash(word)+hash_bash2(word,prob))%29881;
    if(!strcmp(collection->items[position].key,word))
    {
      prob++;
      break;
    }
    prob++;

  }
  return prob;
}

int delete()





int main(int argc, char** argv) {
  {
  int x=0,prob=0,count=0;
  int result;
  unsigned int position,position2;
  ht_item item;
  ht_hash_table collection;
  char word[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char word_insert[BUFFERSIZE];
  char meaning[BUFFERSIZE];
  char term[BUFFERSIZE];
  word[0]='1';
scanf("%s",filename);
//printf("%s %s",word,meaning);
FILE *fp=fopen(filename,"r");
printf("%s",filename);


int c;
if(!fp)
{
  printf("AAAAAAAAAAAAAAA");
}
fflush(stdout);
fflush(NULL);
fflush(stdin);


    while(strcmp(word,"Fatiha"))
    {
      fscanf(fp,"%s",word);
      fgets(meaning, BUFFERSIZE, fp);
      position=(hash_bash(word))%29881;
      prob=1;
      while(collection.items[position].key)
      {
        position=(hash_bash(word)+hash_bash2(word,prob))%29881;
        prob++;

      }
      prob=0;
      collection.items[position].key=word;
      collection.items[position].meaning=meaning;
      count++;
    //  printf("\n%d) %s || %s",count,collection.items[position].key,collection.items[position].meaning);
      }

scanf("%s",term);

while(strcmp(term,"q"))
{
  if(!strcmp(term,"s"))
  {
    fgets(word,BUFFERSIZE,stdin);
    result=search(word,&item,&collection);
  }
  if(!strcmp(term,"i"))
  {
    scanf("%s",word);
    fgets(meaning,BUFFERSIZE,stdin);
    result=insert(word,meaning,&item,&collection);
  }
  if(!strcmp(term,"d"))
  {
    fgets(word,BUFFERSIZE,stdin);

  }


}





fclose(fp);



	return (EXIT_SUCCESS);
}
}
