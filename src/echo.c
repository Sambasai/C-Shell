#include <stdio.h>
#include <unistd.h>
#include <string.h>

void myecho(char *command)
{
      char *idk;
      //printf("%s\n",command);
      char rest1[100];
      strcpy(rest1, command);
      char * rest = rest1;
      //char *idk = strtok_r(rest, " \t\n", &rest);
      //printf("%s", idk);
      while ((idk = strtok_r(rest, " \n", &rest)))
      {
            printf("%s", idk);
            //idk = strtok(NULL, "\n");
      }
      printf("\n");
}