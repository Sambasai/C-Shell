#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

int cpip(char *command)
{
      char *a = strstr(command, "|");
      if (a != NULL)
      {
            return 1;
      }
      else
      {
            return 0;
      }
}

char **pipe_elements(char *input)
{
      char *p = strtok(input, "|");
      char **argu = malloc(256 * sizeof(char *));

      int no = 0;

      while (p != NULL)
      {
            argu[no++] = p;
            p = strtok(NULL, "|");
      }

      return argu;
}

void piping(char *rest, char *curcommand, char *direct, char *myhome)
{
      char **argu = pipe_elements(curcommand);
      int type = 0, parr[2], fd = 0;
      pid_t pid;

      for (int j = 0; argu[j] != NULL; j++)
      {
            pipe(parr);
            //printf("%s\n", argu[j]);
            pid = fork();
            if (pid == 0)
            {
                  dup2(fd, 0);
                  if (argu[j + 1] != NULL)
                        dup2(parr[1], 1);
                  close(parr[0]);
                  myexec(rest, argu[j], direct, myhome);
                  exit(2);
            }
            else
            {

                  wait(NULL);
                  close(parr[1]);
                  fd = parr[0];
            }
      }
}

int redir(char *command)
{
      char *out = strstr(command, ">");
      char *in = strstr(command, "<");

      if ((out == NULL) && (in == NULL))
      {
            return 0;
      }
      else
      {
            return 1;
      }
}

void myexec(char *rest, char *curcommand, char *direct, char *myhome)
{
      char *subcommand = strtok_r(rest, " \t\n", &rest);
      //printf("%s\n",rest);
      if (cpip(curcommand))
      {
            piping(rest, curcommand, direct, myhome);
            return;
      }
      if (subcommand == NULL)
      {
            //printf("ntng");
            return;
      }
      else if (redir(curcommand))
      {
            redirection(curcommand);
            return;
      }
      else if (strcmp(subcommand, "pwd") == 0)
      {
            //printf("oi\n");
            mypwd();
      }
      else if (strcmp(subcommand, "quit") == 0)
      {
            exit(0);
      }
      else if (strcmp(subcommand, "echo") == 0)
      {
            myecho(rest);
      }
      else if (strcmp(subcommand, "jobs") == 0)
      {
            //printf("oi");
            alljobs(rest);
      }
      else if (strcmp(subcommand, "sig") == 0)
      {
            sig(rest);
      }
      else if (strcmp(subcommand, "bg") == 0)
      {
            bg(rest);
      }
      else if (strcmp(subcommand, "fg") == 0)
      {
            fg(rest);
      }
      else if (strcmp(subcommand, "replay") == 0)
      {
            replay(rest, curcommand, direct, myhome);
      }
      else if (strcmp(subcommand, "cd") == 0)
      {
            if (strlen(rest) == 0)
            {
                  mycd(rest, myhome);
            }
            else
            {
                  char *mypath = strtok(rest, " \t\n");
                  //printf("%s\n",mypath);
                  if (mypath == NULL)
                  {
                        //printf("lesgoo");
                  }
                  //printf("%s", rest);
                  mycd(mypath, myhome);
            }
      }
      else if (strcmp(subcommand, "ls") == 0)
      {
            //printf("%s", rest);
            if (strlen(rest) == 0)
            {
                  //printf("only ls");
                  lsnormal(direct, myhome);
                  return;
            }
            char tmp1[100];
            strcpy(tmp1, rest);
            char *tmp = tmp1;
            //int k = 0;
            //while (rest[k] != '\n')
            {
                  //tmp[k] = rest[k];
                  //k++;
            }
            //printf("%s\n", rest);
            int cn = 1;
            char *idk = strtok(tmp, " \t\n");
            while (idk != NULL)
            {
                  cn++;
                  idk = strtok(NULL, " \t\n");
            }
            if (cn == 1)
            {
                  lsnormal(direct, myhome);
                  return;
            }
            //printf("%d\n", cn);
            char flags[cn][100];
            memset(flags, 0, cn * 100); //char flags[4][10] = {0};
            char *tkn = strtok(rest, " \t\n");
            //printf("%s\n", rest);
            int i = 0;
            while (tkn != NULL)
            {
                  strcpy(flags[i], tkn); //flags[i] = tkn;
                  //sprintf("%s\n", tkn);
                  i++;
                  tkn = strtok(NULL, " \t\n");
            }
            //strcpy(flags[i], NULL);
            //strcpy(flags[i], tkn);
            //flags[3] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            for (int i = 0; i < cn; i++)
            {
                  if (flags[i] == NULL)
                  {
                        //printf("oi");
                  }
                  //printf("%s\n", flags[i]);
            }
            lsimpl(flags, cn, myhome);
      }
      else if (strcmp(subcommand, "pinfo") == 0)
      {
            //printf("%s\n", myhome);
            pinfo(rest, myhome);
      }
      else if (strcmp(subcommand, "repeat") == 0)
      {
            repeat(rest, myhome);
      }
      else
      {
            //printf("%s\n", command[i]);
            //printf("%s\n", curcommand);
            //strcat(subcommand, rest);
            //printf("%s%s", rest, subcommand);
            //printf("oi");
            myfgbg(curcommand);
      }
}