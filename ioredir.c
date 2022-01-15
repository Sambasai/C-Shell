#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"

void redirection(char *command)
{
      //printf("%s\n", command);
      int stdoutput = dup(STDOUT_FILENO);
      int stdinput = dup(STDIN_FILENO);
      int status;

      char *output[2], *input[2];
      char *out_file = NULL;
      char *in_file = NULL;

      char *inp = strstr(command, "<");
      //int in = !(inp == NULL);
      int in;
      if (inp == NULL)
      {
            in = 0;
      }
      else
      {
            in = 1;
      }
      int out_type = 0;
      char *out = strstr(command, ">>");

      if (out != NULL)
      {
            out_type = 2;
      }

      else
      {
            out = strstr(command, ">");
            if (out != NULL)
            {
                  out_type = 1;
            }
      }
      char command1[100];
      strcpy(command1, command);
      output[0] = &command[0];
      char *output1[2];
      output1[0] = &command1[0];
      if (out_type)
      {
            output[0] = strtok(command, ">");
            output[1] = strtok(NULL, ">");
            out_file = strtok(output[1], " \r\t\n");
            //printf("%s\n", out_file); //c.txt
      }
      /*if (out_type == 2)
      {
            input[0] = output1[0];
      }
      else*/
      //{
      input[0] = output[0];
      //}
      //input[0] = strtok(output[0], " "); MESSED UP Iredir
      //printf("%s\n", input[0]); //b.txt
      if (in)
      {
            //input[0] = strtok(input[0], "<");
            char *token = strtok(input[0], "< ");
            input[0] = token;
            //printf("%s\n", input[0]);
            while (token != NULL)
            {
                  token = strtok(NULL, " <\n");
                  //printf("%s\n",token);
                  if (token != NULL)
                  {
                        input[1] = token;
                  }
            }
            //printf("%s\n", input[1]);
      }

      char **args = (char **)malloc(sizeof(char *) * 300);
      int no_args = 0;

      if (in)
      {
            if (input[1] == NULL)
            {
                  printf("Specify file name for input\n");
                  return;
            }

            in_file = strtok(input[1], "\n>");
            //in_file = strtok(input[1], " \n\r\t");
            //sprintf("%s\n", in_file);
            struct stat f;
            if (stat(in_file, &f) != 0 || S_ISDIR(f.st_mode))
            {
                  printf("File does not exist\n");
                  return;
            }
      }
      //printf("%s\n", input[0]);
      char *tkn = strtok(input[0], " \n\r\t");
      //printf("%syey", input[0]); //b.txt

      while (tkn != NULL)
      {
            //printf("oi");
            args[no_args] = (char *)malloc(sizeof(char) * strlen(tkn) + 10);
            strcpy(args[no_args], tkn);
            //printf("%s\n", tkn);
            tkn = strtok(NULL, " \n\t\r");
            no_args++;
      }
      /*if (out_type == 2)
      {
            args[no_args] = (char *)malloc(sizeof(char) *3);
            strcpy(args[no_args], ">>");
            no_args++;

            args[no_args] = (char *)malloc(sizeof(char) * strlen(out_file) + 10);
            strcpy(args[no_args], out_file);
            no_args++;
      }*/
      args[no_args] = NULL;
      for (int i = 0; i < no_args; i++)
      {
            //printf("%s\n", args[i]);
      }
      if (out_type)
      {
            if (out_file == NULL)
            {
                  printf("Enter output file\n");
                  return;
            }

            //printf("%s %d\n", out_file, out_type);
      }
      //printf("%s %s",in_file,out_file);
      pid_t pid = fork();
      if (pid < 0)
      {
            perror("Error in forking");
            return;
      }

      if (pid == 0)
      {
            if (in)
            {
                  int fd_in = open(in_file, O_RDONLY);
                  if (fd_in < 0)
                  {
                        perror("Input redirection");
                        return;
                  }

                  dup2(fd_in, 0);
                  close(fd_in);
            }

            if (out_type)
            {
                  int fd_out;
                  if (out_type == 1)
                        fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                  else if (out_type == 2)
                        fd_out = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);

                  if (fd_out < 0)
                  {
                        perror("Output Redirection");
                        return;
                  }

                  dup2(fd_out, 1);
                  close(fd_out);
            }
            for (int i = 0; i < no_args; i++)
            {
                  //printf("%s\n", args[0]);
            }
            if (execvp(args[0], args) < 0)
            {
                  perror("Command not found");
                  exit(EXIT_FAILURE);
            }

            dup2(stdinput, 0);
            close(stdinput);

            dup2(stdoutput, 1);
            close(stdoutput);
      }

      else
      {
            while (wait(&status) != pid)
                  ;
      }
}