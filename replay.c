#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

void replay(char *rest, char *curcommand, char *direct, char *myhome)
{
      int i, p;
      //printf("%s",rest);
      char *token = strtok(rest, " ");
      //printf("%s", token);
      //token = strtok(NULL, " ");
      //printf("%s", token);
      token = strtok(NULL, "-");
      curcommand = token;
      //printf("%s", curcommand);
      token = strtok(NULL, " ");
      token = strtok(NULL, " ");
      i = atoi(token);
      token = strtok(NULL, " ");
      token = strtok(NULL, " ");
      p = atoi(token);
      //printf("%d %d", i, p);
      token = strtok(NULL, " \n");
      char dupd[100];
      strcpy(dupd, curcommand);
      for (int j = 0; j < p / i; j++)
      {
            sleep(i);
            myexec(curcommand, curcommand, direct, myhome);
            strcpy(curcommand, dupd);
            //printf("%s", curcommand);
      }
      sleep(p - (p / i) * i);
}