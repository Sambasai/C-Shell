#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void mycd(char *cmnd, char *home)
{
      //printf("oi\n");
      //printf("%s\n", cmnd);
      char cdir[1000];
      getcwd(cdir, sizeof(cdir));
      char rest1[100];
      strcpy(rest1, cmnd);
      char *rest = rest1;
      char npath[1000];
      if (rest == NULL)
      {
            rest = "~";
      }
      //printf("%s", cmnd);
      if (rest[0] == '-')
      {
            char *tstr = getenv("OLDPWD");
            //npath = tstr;
            strcpy(npath, tstr);
            printf("%s\n", tstr);
            // int check = chdir(getenv("OLDPWD"));
            //if (check < 0)
            {
                  // printf("Error!! No such directory exists\n");
            }
      }
      else
      {
            if (rest[0] == '~')
            {
                  //printf("oi\n");
                  strcpy(npath, home);
                  strcat(npath, rest + 1);
            }
            else
            {
                  strcpy(npath, cdir);
                  //printf("%s\n", cdir);
                  strcat(npath, "/");
                  strcat(npath, rest);
            }
      }
      if (chdir(npath) < 0)
      {
            printf("Error!! No such directory exists\n");
      }
      else
      {
            setenv("OLDPWD", getenv("PWD"), 1);
            setenv("PWD", npath, 1);
      }
}