
                         // for server
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<signal.h>
#include<fcntl.h>
#include "s5c.h"



int copy(char *src , char *dest)
 {
  int fd1=open(src,O_RDONLY);
  int fd2=open(dest,O_WRONLY|O_CREAT|S_IRUSR|S_IWUSR);
  char c;
   while(read(fd1,&c,1))
     {

         write(fd2,&c,1);
    }

 }
 void update(int x)
  {
   copy("CLIENT","SERVER");
   printf("coping your client file ");
 }
void ext(int x)
{
   exit(0);
}

int main()
 {
   signal(SIGUSR1,update);
   signal(SIGUSR2,ext);
   printf("server pid is %d",getpid());

  
   while(1);
   return 0;
 }
