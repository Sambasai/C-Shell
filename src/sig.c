#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

void sig(char *rest)
{
      int n, s;
      //printf("%s",rest);
      char *token = strtok(rest, " \n");
      n = atoi(token);
      token = strtok(NULL, " \n");
      s = atoi(token);
      token = strtok(NULL, " \n");
      //printf("%d %d", n, s);
      int flag = 0;
      if (token != NULL)
      {
            printf("Error: Incorrect number of arguments\n");
      }
      else
      {
            if (bgpids[n - 1] == 0 || bglist[n - 1] == NULL)
            {
                  printf("Error : No such process found\n");
            }
            else
            {
                  kill(bgpids[n - 1], s);
            }
      }
}