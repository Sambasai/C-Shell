#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

void fg(char *rest)
{
      char *token = strtok(rest, " \n");
      int n = atoi(token);
      int f = 0;
      for (int i = 0; i < 50; i++)
      {
            if (i == n - 1)
            {
                  int status;
                  signal(SIGTTIN, SIG_IGN);
                  signal(SIGTTOU, SIG_IGN);
                  tcsetpgrp(STDIN_FILENO, bgpids[i]);
                  f = 1;
                  fgpid = bgpids[i];
                  strcpy(fgname, bglist[i]);
                  kill(bgpids[i], SIGCONT);
                  bgpids[i] = 0;
                  bglist[i] = NULL;             // DELETING THE PROCESS FROM THE BACKGROUND PROC ARRAY
                  waitpid(-1, NULL, WUNTRACED); // WAITING FOR THAT PROCESS TO FINISH EXECUTION
                  tcsetpgrp(STDIN_FILENO, getpgrp());
                  signal(SIGTTIN, SIG_DFL);
                  signal(SIGTTOU, SIG_DFL);
                  //printf("%d",WIFSTOPPED(status));
                  if (WIFSTOPPED(status))
                  {
                        printf("%s with PID %d is suspended\n", fgname, fgpid);
                        addbgcmnd(fgpid, fgname);
                  }
            }
      }
      if (f == 0)
      {
            printf("Error: No such job exists\n");
      }
}