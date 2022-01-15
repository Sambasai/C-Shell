#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

void bgexit()
{
      int status;
      int pid = waitpid(-1, &status, WNOHANG);
      if (pid > 0)
      {
            int i = 0;
            if (WIFSTOPPED(status))
            {
                  return;
            }
            while (bgpids[i] != pid)
            {
                  i++;
            }
            printf("%s with pid %d exited ", bglist[i], bgpids[i]);
            if (WIFEXITED(status))
            {
                  printf("normally");
            }
            else
            {
                  printf("abnormally");
            }
            printf("\n");
            bgpids[i] = 0;
            bglist[i] = NULL;
      }
}

void addbgcmnd(int pid, char *cmnd)
{
      int size = strlen(cmnd) + 1;
      int i = 0;
      while (bgpids[i] != 0)
      {
            i++;
      }
      bglist[i] = (char *)malloc(sizeof(char) * size);
      bgpids[i] = pid;
      strcpy(bglist[i], cmnd);
}

void ctrl_c(int signo)
{
      pid_t p = getpid();
      if (p != cpid)
      {
            //printf("oi");
            return;
      }
      if (p == cpid && fgpid == -1)
      {
            fflush(stdout);
      }
      if (fgpid != -1)
      {
            kill(fgpid, SIGINT);
      }
      signal(SIGINT, ctrl_c);
}

void ctrl_z(int signo)
{
      pid_t p = getpid();
      if (p != cpid)
      {
            //printf("oi");
            return;
      }
      if (fgpid != -1)
      {
            kill(fgpid, SIGTTIN);
            kill(fgpid, SIGTSTP);
            //printf("oi");
            //job_count++;
            //job_arr[job_count].pid = current_fore.pid;
            //strcpy(job_arr[job_count].name, current_fore.name);
            addbgcmnd(fgpid, fgname);
            return;
      }
      signal(SIGTSTP, ctrl_z);
      if (p == cpid)
      {
            fflush(stdout);
      }

      return;
}

int main()
{
      cpid = getpid();
      signal(SIGINT, ctrl_c);
      signal(SIGTSTP, ctrl_z);
      char *uname = getenv("USER");
      //char *root = getenv("PWD");
      //printf("%s\n", root);
      //printf("%s\n", getenv("PATH"));
      //printf("%s\n", getenv("HOME"));
      //printf("%s\n", getenv("ROOT"));
      char hname[100];
      gethostname(hname, sizeof(hname));
      char myhome[1000];
      getcwd(myhome, sizeof(myhome));
      while (1)
      {
            fgpid = -1;
            //bgexit();
            //printf("oi");
            char direct[1000];
            getcwd(direct, sizeof(direct));
            //printf("%s\n", direct);
            printf(">%s", uname);
            printf("@%s:", hname);
            //printf("%d", fgpid);
            if (strcmp(direct, myhome) == 0)
            {
                  //strcpy(direct, "~");
                  printf("~$");
            }
            else if (strlen(direct) > strlen(myhome))
            {
                  printf("~");
                  for (int i = strlen(myhome); i < strlen(direct); i++)
                  {
                        printf("%c", direct[i]);
                  }
                  printf("$");
            }
            else
            {
                  printf("%s$", direct);
            }
            long unsigned int size = 1000;
            char *commands = (char *)malloc(size);
            //fgets(commands, sizeof(commands), stdin);
            if (getline(&commands, &size, stdin) < 0)
            {
                  exit(0);
            }
            //getline(&commands, &size, stdin);
            //printf("oiiiii");
            //exit(0);
            //printf("%s", commands);
            int count = 1;
            for (int i = 0; commands[i] != '\n'; i++)
            {
                  //printf("%c",commands[i]);
                  if (commands[i] == ';')
                  {
                        count++;
                  }
            }
            char *command[count];
            char *token = strtok(commands, ";");
            int i = 0;
            while (token != NULL)
            {
                  command[i] = token;
                  i++;
                  token = strtok(NULL, ";");
            }
            for (int i = 0; i < count; i++)
            {
                  //printf("%s\n",command[i]);
            }

            //printf("%d", count);
            char *subcommand;
            for (int i = 0; i < count; i++)
            {
                  //printf("idek");
                  bgexit();
                  char curcommand[100];
                  strcpy(curcommand, command[i]);
                  char *rest = command[i];
                  //printf("wronggg");
                  myexec(rest, curcommand, direct, myhome);
                  /*if (subcommand == NULL)
                  {
                        break;
                  }
                  if (strcmp(subcommand, "pwd") == 0)
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
                  else if (strcmp(subcommand, "cd") == 0)
                  {
                        char *mypath = strtok(rest, " \t\n");
                        if (mypath == NULL)
                        {
                              //printf("lesgoo");
                        }
                        //printf("%s", rest);
                        mycd(mypath, myhome);
                  }
                  else if (strcmp(subcommand, "ls") == 0)
                  {
                        //printf("%s", rest);
                        if (strlen(rest) == 0)
                        {
                              //printf("only ls");
                              lsnormal(direct, myhome);
                              continue;
                        }
                        char tmp1[100];
                        strcpy(tmp1, rest);
                        char * tmp = tmp1;
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
                        myfgbg(curcommand);
                  }*/
            }
            //bgexit();
            //break;
      }
}
