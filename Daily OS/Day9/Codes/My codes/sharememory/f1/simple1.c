#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/shm.h>

       struct rec{
          int x;
	 char arr[10],c;
        };
	 int main()
	{
          int id=shmget(111,10*sizeof(struct rec),IPC_CREAT|0600);
 	  void *p=shmat(id,0,0);
          struct rec obj;
	  obj.x=1;
          obj.c='q';
 	  strcpy(obj.arr,"bbb");
          
          struct rec *recptr=p;
          memcpy(recptr,&obj,sizeof(obj));

          recptr++;
          scanf("%d %s %c",&recptr->x,recptr->arr,&recptr->c);
          return 0;
        } 
           	  
