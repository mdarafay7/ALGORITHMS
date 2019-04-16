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
    sum=(int)(sum+string[i]*pow(128,(strlen(string)-(i+1))))%29879;
  }
  return value*sum;
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
    printf("\nNot Found");
    fflush(NULL);
    return 0;
  }
  else if(!strcmp(keys[position],word))
  {
    printf("\nMeaning %s \n",values[position]);
    return 0;
  }
  else
  {
    while(*keys[position]&&strcmp(keys[position],word))
    {
      position=(hash_bash(word)+hash_bash2(word,prob))%29881;
      if(!strcmp(keys[position],word))
      {

        printf("\nMeaning %s \n",values[position]);
        result=1;
        break;
      }
      prob++;
    }
  }
  printf("\n%d probes ",prob);
  if(!result)
  {
    printf("\nNot Foundpp\n\n\n");
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
    printf("\nNot Found");
    fflush(NULL);
    return 0;
  }
  else if(!strcmp(keys[position],word))
  {
    free(keys[position]);
    free(values[position]);
    keys[position]=(char*)malloc(sizeof(int));
    values[position]=(char*)malloc(sizeof(int));
    printf("\nDeleted");
    return 0;
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
        printf("\nDeleted");
        result=1;
        break;
      }
      prob++;
    }
  }
  printf("\n%d probes ",prob);
  if(!result)
  {
    printf("\nNot Foundpp\n\n\n");
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
    printf("\nNot Found");
    fflush(NULL);
    return 0;
  }
  else if(!strcmp(keys[position],word))
  {
    strcat(values[position],";");
    strcat(values[position],meaning);
    printf("\n1 probe");

    return 0;
  }
  else
  {
    while(*keys[position]&&strcmp(keys[position],word))
    {
      position=(hash_bash(word)+hash_bash2(word,prob))%29881;
      if(!strcmp(keys[position],word))
      {
        strcat(values[position],";");
        strcat(values[position],meaning);
        result=1;
        break;
      }
      prob++;
    }
  }
  printf("\n%d probes ",prob);
  if(!result)
  {
    printf("\nNot Foundpp\n\n\n");
  }

}


int main(int argc, char** argv)
{
  char *keys[29908];
  char filename[BUFFERSIZE];
  char *values[29908];
  int i,position=0,length=0,prob=0,repeat=0;
  char word[BUFFERSIZE];
  char meaning[BUFFERSIZE];

  scanf("%s",filename);
  FILE *fp=fopen(filename,"r");
  if(!fp)
  {
    printf("File Not Found");
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
      prob=0;

      if(!repeat)
      {
      keys[position]=(char*)realloc(keys[position],100*sizeof(char));
      values[position]=(char*)realloc(values[position],1000*sizeof(char));
      strcpy(keys[position],word);
      strcpy(values[position],meaning);
      }
      printf("\n%d )%s || %s",position,keys[position],values[position]);


    }

    
      for( i=0;i<29908;i++)
      {
        free(keys[i]);
        free(values[i]);
      }

  return 0;
}
