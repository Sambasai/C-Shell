#include <stdio.h>
#include <unistd.h>

void mypwd()
{
      char wrkngdir[1000];
      getcwd(wrkngdir, sizeof(wrkngdir));
      printf("%s\n", wrkngdir);
}