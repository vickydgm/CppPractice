#include"header.h"
int main()
{
   
   struct init in;
   int mid=msgget(KEY,IPC_CREAT|0660);
   int pid=fork();    
   if(pid)
   {
      while(1)
      {
           in.pid=pid;
           in.mtype=2;
           msgsnd(mid,&in,sizeof(int),0);
           struct msg m1;
           printf("Enter Messege : \n");
           gets(m1.messeg.messege);
           m1.messeg.pid=pid;
           m1.mtype=1;
           msgsnd(mid,&m1,sizeof(struct myst),0); 
      }
  }
  else
  {
       while(1)
       {
            struct msg m;            
            msgrcv(mid,&m,sizeof(struct myst),getpid(),0);
            printf("Messege Recived : \n");
            printf("Type :- %ld\n",m.mtype); 	
            printf("Messege : - %s\n",m.messeg.messege);
            printf("Enter Messege : \n");
       }    
   }

}
