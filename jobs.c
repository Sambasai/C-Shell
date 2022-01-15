#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "functions.h"

typedef struct jobs
{
      int ind;
      char stat[1000];
      char name[10000];
      int pid;
} job;

int comp(const void *a, const void *b)
{
      struct jobs *ia = (struct jobs *)a;
      struct jobs *ib = (struct jobs *)b;
      if (strcmp(ia->stat, ib->stat) != 0)
      {
            return strcmp(ia->stat, ib->stat);
      }
      else
      {
            return strcmp(ia->name, ib->name);
      }
}
void alljobs(char *rest)
{
      job out[50];
      int j = 0;
      int f = 0;
      //printf("%s", rest);
      if (!strcmp(rest, "-r\n"))
      {
            f = 1;
      }
      else if (!strcmp(rest, "-s\n"))
      {
            f = 2;
      }
      //printf("%d", f);
      for (int i = 0; i < 50; i++)
      {
            if (bgpids[i] == 0 || bglist[i] == NULL)
            {
                  continue;
            }
            //printf("%d",bgpids[i]);
            int pid = bgpids[i];
            char name[10000], file[10000], status, s[100000];
            strcpy(name, bglist[i]);

            sprintf(file, "/proc/%d/stat", pid);
            FILE *fd;
            fd = fopen(file, "r");
            if (fd < 0)
                  perror("Error: no such process exists\n");
            else
            {
                  fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status);
                  fclose(fd);
            }

            if (status == 'T')
            {
                  strcpy(s, "Stopped");
            }
            else
            {
                  strcpy(s, "Running");
            }
            if (f == 1 && strcmp(s, "Running") == 0)
            {
                  out[j].ind = i + 1;
                  strcpy(out[j].name, name);
                  strcpy(out[j].stat, s);
                  out[j].pid = pid;
                  j++;
                  //printf("[%d] %s %s [%d]\n", i, s, name, pid);
            }
            else if (f == 2 && strcmp(s, "Stopped") == 0)
            {
                  out[j].ind = i + 1;
                  strcpy(out[j].name, name);
                  strcpy(out[j].stat, s);
                  out[j].pid = pid;
                  j++;
                  //printf("[%d] %s %s [%d]\n", i, s, name, pid);
            }
            else if (f == 0)
            {
                  out[j].ind = i + 1;
                  strcpy(out[j].name, name);
                  strcpy(out[j].stat, s);
                  //printf("%d\n",pid);
                  out[j].pid = pid;
                  //printf("%d\n", out[0].pid);
                  j++;
                  //printf("[%d] %s %s [%d]\n", i, s, name, pid);
            }
      }
      qsort(out, j, sizeof(struct jobs), comp);
      for (int i = 0; i < j; i++)
      {
            printf("[%d] %s %s [%d]\n", out[i].ind, out[i].stat, out[i].name, out[i].pid);
      }
      //free(out);
}