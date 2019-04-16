//Abdul Rafay Mohammed UTA ID:- 1001331625

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


void add_colon(char *dest, int size) {
  int len = strlen(dest);
  // for the check i still assume dest tto contain a valid '\0' terminated string, so len will be smaller than size

  memset( dest+len, ';',1);
  dest[len + 1] = '\0';
}

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
    sum=(int)(sum+string[i]);
  }
  return 29881-(value*sum);
}


void strip(char *s) {
  char *p2 = s;
  while(*s != '\0') {
    if(*s != '\t' && *s != '\n') {
      *p2++ = *s++;
    } else {
      ++s;
    }
  }
  *p2 = '\0';
}

int search(char *word,char *keys[],char *values[])
{
  int position=0;
  position=(hash_bash(word))%29881;
  int prob=1;
  int result=0;
  if(position>=29881||!*keys[position])
  {
    printf("\n\t%d probes",prob);
    printf("\n\tItem not found\n");
    fflush(NULL);
    return 1;
  }
  else if(!strcmp(keys[position],word))
  {
    printf("\n\t%d probes",prob);
    printf("\n\tTranslation: %s \n",values[position]);
    return 1;
  }
  else
  {
    while(*keys[position]&&strcmp(keys[position],word))
    {
      position=(hash_bash(word)+hash_bash2(word,prob))%29881;
      if(!strcmp(keys[position],word))
      {
        prob++;
        printf("\n\t%d probes",prob);
        printf("\n\tTranslation: %s \n",values[position]);
        result=1;
        return prob;
      }
      else{
      prob++;
          }
    }
  }
  if(!result)
  {
    printf("\n\t%d probes",prob);
    printf("\n\tItem not found\n");
    return prob;
  }

}



int delete(char *word,char *keys[],char *values[])
{
  int position=0;
  position=(hash_bash(word))%29881;
  int prob=1;
  int result=0;
  if(position>=29881||!*keys[position])
  {
    printf("\n\t%d probes",prob);
    printf("\n\tItem not found => no deletion\n");
    fflush(NULL);
    return prob;
  }
  else if(!strcmp(keys[position],word))
  {
    free(keys[position]);
    free(values[position]);
    keys[position]=(char*)malloc(sizeof(int));
    values[position]=(char*)malloc(sizeof(int));
    *keys[position]=0;
    *values[position]=0;
    printf("\n\t%d probes",prob);
    printf("\n\tItem was deleted\n");
    return prob;
  }
  else
  {
    while(*keys[position]&&strcmp(keys[position],word))
    {
      position=(hash_bash(word)+hash_bash2(word,prob))%29881;
      if(!strcmp(keys[position],word))
      {
        free(keys[position]);
        free(values[position]);
        keys[position]=(char*)malloc(sizeof(int));
        values[position]=(char*)malloc(sizeof(int));
        *keys[position]=0;
        *values[position]=0;
        prob++;
        printf("\n\t%d probes",prob);
        printf("\n\tItem was deleted\n");
        return prob;
      }
      else{
      prob++;
      }
    }
  }
  printf("\n%d probes ",prob);
  if(!result)
  {
    printf("\n\t%d probes",prob);
    printf("\n\tItem not found => no deletion\n");
    return prob;
  }


}

int insert(char *word,char *meaning,char *keys[],char *values[])
{
  int position=0;
  position=(hash_bash(word))%29881;
  int prob=1;
  int result=0;
  if(position>=29881||!*keys[position])
  {
    if(!*keys[position])
    {
      keys[position]=(char*)realloc(keys[position],100*sizeof(char));
      values[position]=(char*)realloc(values[position],1000*sizeof(char));
      strcpy(keys[position],word);
      strcpy(values[position],meaning);
      printf("\n\t%d probes",prob);
      printf("\n\tWill insert pair [%s,%s]\n",word,meaning);
      return prob;

    }
    fflush(NULL);
    return 0;
  }
  else if(!strcmp(keys[position],word))
  {
    strcat(values[position],";");
    strcat(values[position],meaning);
    printf("\n\t%d probes",prob);
    printf("\n\tWill insert pair [%s,%s]\n",word,meaning);
    return prob;

    return 0;
  }
  else
  {
    while(*keys[position]&&strcmp(keys[position],word))
    {
      position=(hash_bash(word)+hash_bash2(word,prob))%29881;
      if(!*keys[position])
      {
        keys[position]=(char*)realloc(keys[position],100*sizeof(char));
        values[position]=(char*)realloc(values[position],1000*sizeof(char));
        strcpy(keys[position],word);
        strcpy(values[position],meaning);
        prob++;
        printf("\n\t%d probes",prob);
        printf("\n\tWill insert pair [%s,%s]\n",word,meaning);
        return prob;

      }
      else if(!strcmp(keys[position],word))
      {
        strcat(values[position],";");
        strcat(values[position],meaning);
        prob++;
        printf("\n\t%d probes",prob);
        printf("\n\tWill insert pair [%s,%s]\n",word,meaning);
        return prob;
      }
      else{
      prob++;
          }
    }
  }


}


int main(int argc, char** argv)
{
  char *keys[29908];
  char filename[BUFFERSIZE];
  char *values[29908];
  int i,position=0,prob=0,repeat=0,result=0,counter=0,not_hashed=0;

  char word[BUFFERSIZE];
  char meaning[BUFFERSIZE];
  char term[BUFFERSIZE];
  int probes[500];

  for(i=0;i<500;i++)
  {
    probes[i]=0;
  }

  scanf("%s",filename);
  FILE *fp=fopen(filename,"r");
  if(!fp)
  {
    printf("File Item not found");
  }

  for(i=0;i<29908;i++)
  {
    keys[i]=(char*)malloc(sizeof(int));
    values[i]=(char*)malloc(sizeof(int));
    *keys[i]=0;
    *values[i]=0;
  }


  while(fscanf(fp,"%s",word)!=EOF)
  {
    counter++;
    fgets(meaning, BUFFERSIZE, fp);
    strip(meaning);
    position=(hash_bash(word))%29881;
    prob=1;
    repeat=0;
    while(*keys[position])
    {
      if(!strcmp(keys[position],word))
      {
        strcat(values[position],";");
        strcat(values[position],meaning);
        repeat=1;
        break;
      }
      position=(hash_bash(word)+hash_bash2(word,prob))%29881;
      prob++;
    }
    probes[prob]=probes[prob]+1;

    if(!repeat)
    {
      keys[position]=(char*)realloc(keys[position],100*sizeof(char));
      values[position]=(char*)realloc(values[position],1000*sizeof(char));
      strcpy(keys[position],word);
      strcpy(values[position],meaning);
    }
    prob=0;
    //printf("\n%d )%s || %s",position,keys[position],values[position]);
  }

double total_probes=0;
int max_prob=0;

for(i=0;i<500;i++)
{
  total_probes=total_probes+(i*probes[i]);
  if(probes[i])
  {
    if(i>max_prob)
    {
      max_prob=i;
    }
  }

}


  printf("\nHash Table");
  printf("\n        average number of probes:               %0.2f",total_probes/(counter));
  printf("\n        max_run of probes:                      %d",max_prob);
  printf("\n        total PROBES (for %d items):          %d",counter,(int)total_probes);
  printf("\n        items not hashed (out of %d items):    %d\n",counter,not_hashed);



  printf("Probes|Count of keys");
  for(i=1;i<=100;i++)
  {
    printf("\n---------------\n     %d|     %d",i,probes[i]);
  }

  scanf("%s",term);

  printf("\nEnter words to look-up. Enter -1 to stop.\n");
  counter=0;
  total_probes=0;

  while(strcmp(term,"q"))
  {
    counter++;

    if(!strcmp(term,"s"))
    {
      scanf("%s",word);
      printf("READ op:s query:%s",word);
      result=search(word,keys,values);
      total_probes=total_probes+result;
    }
    if(!strcmp(term,"i"))
    {
      scanf("%s",word);
      printf("READ op:i query:%s",word);
      fgets(meaning,BUFFERSIZE,stdin);
      strip(meaning);
      result=insert(word,meaning,keys,values);
      total_probes=total_probes+result;
    }
    if(!strcmp(term,"d"))
    {
      scanf("%s",word);
      printf("READ op:d query:%s",word);
      result=delete(word,keys,values);
      total_probes=total_probes+result;
    }
    scanf("%s",term);
  }

printf("\nAverage probes per operation: %0.2f\n",total_probes/counter);


  for( i=0;i<29908;i++)
  {
    free(keys[i]);
    free(values[i]);
  }

  return 0;
}
