#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

void bg(char *rest)
{
      char *token = strtok(rest, " \n");
      int n = atoi(token);
      token = strtok(NULL, " \n");
      if (token != NULL)
      {
            printf("Error: Incorrect number of arguments\n");
            return;
      }
      int f = 0;
      for (int i = 0; i < 50; i++)
      {
            if (i == n - 1)
            {
                  f = 1;
                  kill(bgpids[i], SIGTTIN);
                  kill(bgpids[i], SIGCONT);
            }
      }
      if (f == 0)
      {
            printf("Error: No such job exists\n");
      }
}