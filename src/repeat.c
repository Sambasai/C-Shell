#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"

void repeat(char *rest, char *myhome)
{
      char dupe[100];
      strcpy(dupe, rest);
      char *tkn = strtok(dupe, " \t\n");
      int n = atoi(tkn);
      //printf("%d", n);
      //printf("%s %s",rest,tkn);
      tkn = strtok(NULL, " \t\n");
      //printf("%s %s", rest, tkn);
      rest = rest + 2;
      //printf("%s", rest);
      char curcommand[100];
      strcpy(curcommand, rest);
      char *subcommand = strtok_r(rest, " \t\n", &rest);

      if (strcmp(subcommand, "pwd") == 0)
      {
            //printf("oi\n");
            for (int i = 0; i < n; i++)
            {
                  mypwd();
            }
      }
      else if (strcmp(subcommand, "quit") == 0)
      {
            for (int i = 0; i < n; i++)
            {
                  exit(0);
            }
      }
      else if (strcmp(subcommand, "echo") == 0)
      {
            for (int i = 0; i < n; i++)
            {
                  myecho(rest);
            }
      }
      else if (strcmp(subcommand, "cd") == 0)
      {
            char *mypath = strtok(rest, " \t\n");
            if (mypath == NULL)
            {
                  //printf("lesgoo");
            }
            //printf("%s", rest);
            for (int i = 0; i < n; i++)
            {
                  mycd(mypath, myhome);
            }
      }
      else if (strcmp(subcommand, "ls") == 0)
      {
            //printf("%s", rest);
            if (strlen(rest) == 0)
            {
                  //printf("only ls");
                  for (int i = 0; i < n; i++)
                  {
                        char cdir[1000];
                        getcwd(cdir, sizeof(cdir));
                        lsnormal(cdir, myhome);
                  }
                  return;
            }
            char tmp[100];
            //strcpy(tmp, rest);
            int k = 0;
            while (rest[k] != '\n')
            {
                  tmp[k] = rest[k];
                  k++;
            }
            //printf("%s\n", rest);
            int cn = 1;
            char *idk = strtok(tmp, " \t\n");
            while (idk != NULL)
            {
                  cn++;
                  idk = strtok(NULL, " \t\n");
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
            for (int i = 0; i < n; i++)
            {
                  lsimpl(flags, cn, myhome);
            }
      }
      else if (strcmp(subcommand, "pinfo") == 0)
      {
            //printf("%s\n", myhome);
            for (int i = 0; i < n; i++)
            {
                  pinfo(rest, myhome);
            }
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
            for (int i = 0; i < n; i++)
            {
                  myfgbg(curcommand);
            }
      }
}
