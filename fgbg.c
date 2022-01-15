#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "functions.h"

void myfg(char **arguements)
{
      //printf("fork");
      //printf("%s\n%s\n", arguements[0], arguements[1]);
      int forkret = fork();
      fgpid = forkret;
      strcpy(fgname, arguements[0]);
      if (forkret < 0)
      {
            perror("error: ");
      }
      else if (forkret == 0)
      {
            if (execvp(arguements[0], arguements) == -1)
            {
                  printf("Incorrect command entered\n");
                  exit(0);
            }
      }
      else
      {
            //printf("%d", forkret);
            int shellPid = getpid();
            int status;
            waitpid(forkret, &status, WUNTRACED);
      }
}

void mybg(char **arguements)
{
      //printf("yatha");
      int forkret = fork();
      if (forkret < 0)
      {
            perror("error: ");
      }
      else if (forkret == 0)
      {
            setpgid(0, 0);
            if (execvp(arguements[0], arguements) == -1)
            {
                  printf("Incorrect command entered\n");
                  exit(0);
            }
      }
      else
      {
            //printf("%d", forkret);
            addbgcmnd(forkret, arguements[0]);
            setpgid(forkret, forkret);
      }
}

void myfgbg(char *command)
{
      //printf("yay");
      char *tkn = strtok(command, " \t\n");
      char **arguements = (char **)malloc(sizeof(char *) * 100);
      int i = 0, check = 0;
      while (tkn != NULL)
      {
            arguements[i] = tkn;
            tkn = strtok(NULL, " \t\n");
            i++;
      }
      //i++;
      arguements[i] = NULL;
      for (int j = 0; j < i; j++)
      {
            //printf("%s\n", arguements[j]);
            if (strcmp(arguements[j], "&") == 0)
            {
                  //printf("yay");
                  check = 1;
                  arguements[j] = NULL;
            }
      }
      if (check == 1)
      {
            mybg(arguements);
      }
      else if (check == 0)
      {
            //printf("yayyy");
            myfg(arguements);
      }
}