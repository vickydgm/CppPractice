#include"header.h"


int main()
{
    int shid = shmget(SHMKEY,100*sizeof(struct student)+sizeof(int),IPC_CREAT|0660);
    int mid = msgget(MSGKEY,IPC_CREAT|0660);
    void *p = shmat(shid,0,0);
    int *no_of_rec=p,i,ch;
    struct student *stptr = (struct student *)(no_of_rec+1);
    struct student st;
    struct reqmsg rm;
    struct resmsg rsm;

    do
    {
        printf("1 to add \n");
        printf("2 to modify\n");
        printf("3 to display\n");
        printf("4 for exit\n");
        scanf("%d",&ch);
        getchar();
        switch(ch)
        {
            case 1:
                if(*no_of_rec==100)
                {
                    printf("Cant Add more records\n");
                    break; 
                }
                printf("Enter Student Name : - ");
                gets(st.name);
                printf("Enter Age : ");
                scanf("%d",&st.age);
                rm.mtype=1;
                rm.st=st;
                msgsnd(mid,&rm,sizeof(struct student),0);      
                msgrcv(mid,&rsm,50,4,0);
                printf("Server Responded : - %s\n",rsm.msg);
                break;
            case 2:
                printf("Enter Student Name : - ");
                gets(st.name);
                st.age=-1;
                for(i=0;i<*no_of_rec;i++)
                {
                    if(strcmp((stptr+i)->name,st.name)==0)
                    {
                        printf("Enter Age : ");
                        scanf("%d",&st.age);
                        rm.mtype=2;
                        rm.st=st;
                        msgsnd(mid,&rm,sizeof(struct student),0);      
                        msgrcv(mid,&rsm,50,4,0);
                        printf("Server Responded : - %s\n",rsm.msg);
                    }                      
                }
                if(st.age==-1)
                {
                    printf("No such record found\n");
                }
                break;
            case 3:
                printf("no of rec : %d\n",*no_of_rec);
                for(i=0;i<*no_of_rec;i++)
                {
                    printf("Name : %s    Age : %d\n",(stptr+i)->name,(stptr+i)->age);                      
                }
                break;
        }
    }while(ch!=4);    
    rm.mtype=3;    
    msgsnd(mid,&rm,sizeof(struct student),0);
}
