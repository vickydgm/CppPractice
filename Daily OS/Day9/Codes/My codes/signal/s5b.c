#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "s5c.h"

void add_record(struct client stu)
 {
   char ch=' ';
   while(ch!='n')
  {
   fd=open("client",O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR);
    printf("\n Enter the id of client ");
     scanf("%d",&stu.id);
     getchar();
    printf("\n Enter the name of client =");
     scanf("%s",stu.name);
    printf("\n Enter the address of client =\n");
     scanf("%s",stu.address);
 
    printf("Enter the fee of client =");
       scanf("%f",&stu.fee);
      write(fd,&stu,sizeof(struct client));
   printf("\nDO YOU WANT TO CONTINUE ");
     ch=getchar();
      getchar();
  }
}

void display_record(struct client stu)
 {
    while(read(fd,&stu,sizeof(stu)))
    {
   fd=open("client",O_RDONLY);
   printf("id\t|name\t|address\tfee");
   printf("%d\t%s\t%s\t%f",stu.id,stu.name,stu.address,stu.fee);
  
 //  read(fd,&stu,sizeof(struct client));
 }

 void modify_record(struct client stu)
  {
    fd=open("client",O_APPEND);
    int  cid=0;
    struct client stu;
    printf("\n Enter the id  ");
    scanf("%d",&cid);
   if(cid==stu.cid)
     { 
       
       printf("\n Enter the new name of client =");
       scanf("%s",stu.name);
       printf("\n Enter the new address of client =");
       scanf("%s",stu.address);
       printf("\n Enter the fee of client =");
       scanf("%f",stu.fee);
       write(fd,&stu,sizeof(stu));
      }
 }
int main()
{
 
   int choice ;
   struct student stu;
   int pid;
   printf("\nEnter your pid ");
   printf("1.Add the record \n");
   printf("2.MODify the record \n");
   printf("3.View the record \n");
   printf("4. exit \n");
   printf("Enter your choice ");
   scanf("%d",&choice);
   
   switch(choice)
     {
       case 1:
                  printf("\n Adding the record ");
                  add_record(stu);
                     break;
       case 2:
                   printf"\n modify the record ");
                   modify_record(stu);
                      break;
      case 3:
                   printf("view the record ");
                   display_record(stu);
                     break;
      case 4:
                  printf("exit");
                      exit(0);
        default:
                   printf("WRONG OUTPUT ");

    }
 
 return 0;
}
