#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void pinfo(char *cmnd, char *home)
{
      char rest1[100];
      strcpy(rest1, cmnd);
      char *rest = rest1;
      char *spid = (char *)malloc(sizeof(char) * 100);
      char *command = strtok(rest, " \t\n");
      if (command == NULL)
      {
            int pid = getppid();
            //sprintf(spid, "%d", pid);
            spid = "self";
            //printf("%s\n", spid);
      }
      else
      {
            spid = command;
            //printf("%s\n", spid);
      }
      //printf("pid -- %s\n", spid);
      char *file = (char *)malloc(sizeof(char) * 100);
      strcat(file, "/proc/");
      //printf("%s%s", file, spid);
      strcat(file, spid);
      strcat(file, "/stat");
      int fd = open(file, O_RDONLY);
      if (fd == -1)
      {
            perror("pinfo");
      }
      else
      {
            char *content = (char *)malloc(sizeof(char) * 1000);
            read(fd, content, 1000);
            //printf("%s\n", content);
            char *parameters[100];
            char *tkn = strtok(content, " \n");
            int i = 0;
            while (tkn != NULL)
            {
                  parameters[i] = tkn;
                  i++;
                  tkn = strtok(NULL, " \n");
            }
            printf("pid -- %s\n", parameters[0]);
            printf("Process Status -- %s", parameters[2]);
            //int x = atoi(spid);
            //if (getpgid(x) == x)
            {
                  // printf("+");
            }
            if (strcmp(parameters[0], parameters[7]) == 0)
            {
                  printf("+");
            }
            printf("\n");
            printf("memory -- %s {Virtual Memory}\n", parameters[22]);
            char *file2 = (char *)malloc(sizeof(char) * 100);
            strcat(file2, "/proc/");
            //printf("%s%s", file, spid);
            strcat(file2, "self");
            strcat(file2, "/exe");
            //int fd2 = open(file2, O_RDONLY);
            char *buff = (char *)malloc(sizeof(char) * 1000);
            //printf("%s", file2);
            int ret = readlink(file2, buff, 1000);
            if (ret == -1)
            {
                  perror("error: ");
            }
            else
            {
                  //printf("%s", buff);
                  buff[ret] = '\0';
                  if (strlen(buff) >= strlen(home))
                  {
                        int flag = 0;
                        for (int i = 0; i < strlen(home); i++)
                        {
                              if (buff[i] != home[i])
                              {
                                    flag = 1;
                                    break;
                              }
                        }
                        if (flag == 0)
                        {
                              buff = buff + strlen(home) - 1;
                              buff[0] = '~';
                        }
                  }
            }
            printf("Executable Path -- %s\n", buff);
      }
}