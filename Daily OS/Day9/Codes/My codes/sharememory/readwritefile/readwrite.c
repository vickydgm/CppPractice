#include "head.h"
int main()
{
   char ch=' ';
     struct student var;
     int  fp=open("new",O_WRONLY|O_CREAT|S_IRUSR|S_IWUSR);
      while(ch!='n')
      {
         printf("\n Enter the id of student ==");
         scanf("%d",&var.id);
         getchar();
         printf("\nEnter the name of student \n");
         scanf("%s",var.name);
         getchar();
         printf("\nEnter the address of student=\n");
         scanf("%s",var.address);
         getchar();
         printf("\n Enter the fee of student =");
         scanf("%ld",&var.fee);
         getchar();
         write(fp,&var,sizeof(struct student));
         printf("\n Do you want to continue...(y/n) ");
         ch=getchar();
         getchar();
      }
          close(fp);

    // for reading the data from file
        printf("\n reading the file \n\n");
   
        fp=open("new",O_RDONLY);
        printf("id\t | name\t |address \t| fee \n");
         
        while(read(fp,&var,sizeof(struct student)))
         {
            printf("%d\t %s\t %s\t %ld\n",var.id,var.name,var.address,var.fee);
                   
         }
         close(fp);


}      
