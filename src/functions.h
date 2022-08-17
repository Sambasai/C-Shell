#include <stdio.h>
#include <stdlib.h>

void mypwd();
void myecho(char *command);
void mycd(char *cmnd, char *home);
void lsimpl(char flags[][100], int cn, char *home);
void lsnormal(char *path, char *home);
void lsal(char *path, char *home, int code);
void myfgbg(char *command);
void myfg(char **arguements);
void mybg(char **arguements);
void pinfo(char *cmnd, char *home);
void repeat(char *rest, char *myhome);
void addbgcmnd(int pid, char *cmnd);
void myexec(char *rest, char *curcommand, char *direct, char *myhome);
void redirection(char *command);
void alljobs(char *rest);
void sig(char *rest);
void bg(char *rest);
void fg(char *rest);
void replay(char *rest, char *curcommand, char *direct, char *myhome);
int fgpid, cpid;
char fgname[100];
int bgpids[50];
char *bglist[50];

//int no = 0;