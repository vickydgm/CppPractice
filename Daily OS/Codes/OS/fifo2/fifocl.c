#include"header.h"
int main()
{
    int fd1,fd2;
    char data[25];
    int n;
    char ch;
    struct file f1;
    fd1=open("myfifo",O_RDWR);
    fd2=open("myfifo1",O_RDWR);
    do
    {
         printf("Enter file name...");
         gets(f1.name);
         printf("want to toggle(0/1)...");
         scanf("%d",&f1.toggle);
         printf("Enter offset...");
         scanf("%d",&f1.offset);
         printf("Enter number of bytes...");
         scanf("%d",&f1.len);
         write(fd1,&f1,sizeof(struct file));
         n=read(fd2,data,24);
         data[n]='\0';
         printf("server printed....%s\n",data);
         if(strcmp(data,"done")==0)
         {
             printf("successfully written...\n");
         }
         printf("Continue...(y/n)  ");
         getchar();
         ch=getchar();
         getchar();
    }while(ch!='n');
}
