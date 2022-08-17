#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>

int isDirectory(char *path)
{
      struct stat props;
      if (stat(path, &props) != 0)
      {
            return 0;
      }
      return S_ISDIR(props.st_mode);
}

void lsal(char *path, char *home, int code)
{
      printf("%s:\n", path);
      DIR *dir;
      struct dirent *str;
      char wrkngdir[1000];
      getcwd(wrkngdir, sizeof(wrkngdir));
      char *abspath = (char *)malloc(sizeof(char) * 1000);
      if (path[0] == '~')
      {
            //printf("oi\n");
            strcpy(abspath, home);
            strcat(abspath, path + 1);
      }
      else if (path[0] == '/')
      {
            strcpy(abspath, path);
      }
      else
      {
            strcpy(abspath, wrkngdir);
            //printf("%s\n", cdir);
            strcat(abspath, "/");
            strcat(abspath, path);
      }
      //printf("%s\n", abspath);
      if (isDirectory(abspath) == 0 && fopen("abspath", "r"))
      {
            //lsfile(abspath, code);
            struct stat props;
            lstat(abspath, &props);
            struct tm *tstat;
            printf((S_ISDIR(props.st_mode)) ? "d" : "");
            printf((S_ISREG(props.st_mode)) ? "-" : "");
            printf((S_ISLNK(props.st_mode)) ? "l" : "");
            printf((props.st_mode & S_IRUSR) ? "r" : "-");
            printf((props.st_mode & S_IWUSR) ? "w" : "-");
            printf((props.st_mode & S_IXUSR) ? "x" : "-");
            printf((props.st_mode & S_IRGRP) ? "r" : "-");
            printf((props.st_mode & S_IWGRP) ? "w" : "-");
            printf((props.st_mode & S_IXGRP) ? "x" : "-");
            printf((props.st_mode & S_IROTH) ? "r" : "-");
            printf((props.st_mode & S_IWOTH) ? "w" : "-");
            printf((props.st_mode & S_IXOTH) ? "x" : "-");
            //printf("\t");
            printf(" %ld ", props.st_nlink);
            printf("%s ", getpwuid(props.st_uid)->pw_name);
            printf("%s ", getgrgid(props.st_gid)->gr_name);

            printf("%10ld ", props.st_size);
            char propser[80];
            time_t timeStamp = props.st_atime;
            tstat = localtime(&timeStamp);
            strftime(propser, 80, " %h %e\t", tstat);
            printf("%s ", propser);
            char tym[20];
            strftime(tym, 20, "%T", localtime(&(props.st_mtime)));
            printf("%s ", tym);
            //c = props.st_blocks;
            //sum += c / 2;
            printf("%s\n", path);
            return;
      }
      else if (isDirectory(abspath) == 0 && fopen("abspath", "r") == NULL)
      {
            printf("No such file/dir exists\n");
            return;
      }

      dir = opendir(abspath);
      //printf("%s\n", abspath);
      if (code == 1)
      {
            while ((str = readdir(dir)))
            {
                  printf("%s \n", str->d_name);
            }
      }
      else if (code == 2)
      {
            long long int sum = 0, c, max = 0;
            while ((str = readdir(dir)))
            {
                  char *naam = str->d_name;
                  //printf("%s\n", naam);
                  char *abspath1 = (char *)malloc(sizeof(char) * 1000);
                  strcpy(abspath1, abspath);
                  strcat(abspath1, "/");
                  strcat(abspath1, naam);
                  //printf("%s\n", abspath);
                  char f = abspath1[0];
                  if (naam[0] != '.')
                  {
                        struct stat props;
                        lstat(abspath1, &props);
                        struct tm *tstat;
                        printf((S_ISDIR(props.st_mode)) ? "d" : "");
                        printf((S_ISREG(props.st_mode)) ? "-" : "");
                        printf((S_ISLNK(props.st_mode)) ? "l" : "");
                        printf((props.st_mode & S_IRUSR) ? "r" : "-");
                        printf((props.st_mode & S_IWUSR) ? "w" : "-");
                        printf((props.st_mode & S_IXUSR) ? "x" : "-");
                        printf((props.st_mode & S_IRGRP) ? "r" : "-");
                        printf((props.st_mode & S_IWGRP) ? "w" : "-");
                        printf((props.st_mode & S_IXGRP) ? "x" : "-");
                        printf((props.st_mode & S_IROTH) ? "r" : "-");
                        printf((props.st_mode & S_IWOTH) ? "w" : "-");
                        printf((props.st_mode & S_IXOTH) ? "x" : "-");
                        //printf("\t");
                        printf(" %ld ", props.st_nlink);
                        printf("%s ", getpwuid(props.st_uid)->pw_name);
                        printf("%s ", getgrgid(props.st_gid)->gr_name);

                        printf("%10ld ", props.st_size);
                        char propser[80];
                        time_t timeStamp = props.st_atime;
                        tstat = localtime(&timeStamp);
                        strftime(propser, 80, " %h %e\t", tstat);
                        printf("%s ", propser);
                        char tym[20];
                        strftime(tym, 20, "%T", localtime(&(props.st_mtime)));
                        printf("%s ", tym);
                        c = props.st_blocks;
                        sum += c / 2;
                        printf("%s\n", str->d_name);
                  }
            }
            printf("total : %lld\n", sum);
      }
      else
      {
            long long int sum = 0, c;
            while ((str = readdir(dir)))
            {

                  char *naam = str->d_name;
                  strcat(abspath, "/");
                  strcat(abspath, naam);
                  //char f = naam[0];
                  struct stat props;
                  lstat(abspath, &props);
                  struct tm *tstat;
                  printf((S_ISDIR(props.st_mode)) ? "d" : "");
                  printf((S_ISREG(props.st_mode)) ? "-" : "");
                  printf((S_ISLNK(props.st_mode)) ? "l" : "");
                  printf((props.st_mode & S_IRUSR) ? "r" : "-");
                  printf((props.st_mode & S_IWUSR) ? "w" : "-");
                  printf((props.st_mode & S_IXUSR) ? "x" : "-");
                  printf((props.st_mode & S_IRGRP) ? "r" : "-");
                  printf((props.st_mode & S_IWGRP) ? "w" : "-");
                  printf((props.st_mode & S_IXGRP) ? "x" : "-");
                  printf((props.st_mode & S_IROTH) ? "r" : "-");
                  printf((props.st_mode & S_IWOTH) ? "w" : "-");
                  printf((props.st_mode & S_IXOTH) ? "x" : "-");
                  //printf("\t");
                  printf(" %ld ", props.st_nlink);
                  printf("%s ", getpwuid(props.st_uid)->pw_name);
                  printf("%s ", getgrgid(props.st_gid)->gr_name);

                  printf("%10ld ", props.st_size);
                  char propser[80];
                  time_t timeStamp = props.st_atime;
                  tstat = localtime(&timeStamp);
                  strftime(propser, 80, " %h %e\t", tstat);
                  printf("%s ", propser);
                  char tym[20];
                  strftime(tym, 20, "%T", localtime(&(props.st_mtime)));
                  printf("%s ", tym);
                  c = props.st_blocks;
                  sum += c / 2;
                  printf("%s\n", str->d_name);
            }
            printf("total : %lld\n", sum);
            printf("\n");
      }
}

void lsnormal(char *path, char *home)
{
      DIR *dir;
      struct dirent *str;
      printf("%s:\n", path);
      char wrkngdir[1000];
      getcwd(wrkngdir, sizeof(wrkngdir));
      char *abspath = (char *)malloc(sizeof(char) * 200);
      if (path[0] == '~')
      {
            //printf("oi\n");
            strcpy(abspath, home);
            strcat(abspath, path + 1);
      }
      else if (path[0] == '/')
      {
            strcpy(abspath, path);
      }
      else
      {
            strcpy(abspath, wrkngdir);
            //printf("%s\n", cdir);
            strcat(abspath, "/");
            strcat(abspath, path);
      }
      //printf("%s\n", abspath);
      dir = opendir(abspath);
      if (dir == NULL)
      {
            printf("%s\n", path);
      }
      else
      {
            while ((str = readdir(dir)))
            {
                  char *naam = str->d_name;
                  char f = naam[0];
                  if (f != '.')
                  {
                        printf("%s \n", str->d_name);
                  }
            }
            printf("\n");
      }
}

void lsimpl(char flags[][100], int cn, char *home)
{
      //printf("oi");
      int lflag = 0, aflag = 0, dirc = 0;
      for (int i = 0; i < cn; i++)
      {
            for (int j = 0; flags[i][j] != '\0'; j++)
            {
                  if (flags[i][j] == '-')
                  {
                        if (flags[i][j + 1] == 'l')
                        {
                              lflag++;
                              if (flags[i][j + 2] == 'a')
                              {
                                    aflag++;
                              }
                        }
                        if (flags[i][j + 1] == 'a')
                        {
                              aflag++;
                              if (flags[i][j + 2] == 'l')
                              {
                                    lflag++;
                              }
                        }
                  }
                  else
                  {
                        dirc++;
                  }
            }
      }
      int impflag = 0;
      //printf("%d\n%d\n", lflag, aflag);
      for (int i = 0; i < cn - 1; i++)
      {
            if (flags[i][0] != '-')
            {
                  impflag = 1;
                  if (lflag == 0 && aflag == 0)
                  {
                        lsnormal(flags[i], home);
                        //printf("%s\n", flags[i]);
                  }
                  else if (lflag == 0 && aflag > 0)
                  {
                        //printf("oi");
                        lsal(flags[i], home, 1);
                  }
                  else if (lflag > 0 && aflag == 0)
                  {
                        lsal(flags[i], home, 2);
                  }
                  else
                  {
                        lsal(flags[i], home, 3);
                  }
            }
      }
      if (cn == 2 && impflag == 0)
      {
            char wrkngdir[1000];
            getcwd(wrkngdir, sizeof(wrkngdir));
            //printf("%s\n",wrkngdir);
            if (lflag == 0 && aflag == 0)
            {
                  lsnormal(wrkngdir, home);
                  //printf("%s\n", flags[i]);
            }
            else if (lflag == 0 && aflag > 0)
            {
                  //printf("oi");
                  lsal(wrkngdir, home, 1);
            }
            else if (lflag > 0 && aflag == 0)
            {
                  lsal(wrkngdir, home, 2);
            }
            else
            {
                  lsal(wrkngdir, home, 3);
            }
      }
}
