#include "head.h"
	 int main()
	{
          int id=shmget(111,10*sizeof(struct rec),IPC_CREAT|0600);
 	  void *p=shmat(id,0,0);
          struct rec obj;
	  
          struct rec *recptr=p;
          memcpy(recptr,&obj,sizeof(obj));

          recptr++;
          printf("%d\t %s \t%c",recptr->x,recptr->arr,recptr->c);
          return 0;
        } 
           	  
