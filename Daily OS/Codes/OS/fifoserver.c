#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
    int fd1,fd2;
    char data[25];
    int n;
    fd1=open("myfifo",O_WRONLY);
    fd2=open("myfifo1",O_RDONLY);
    while(1)
    {
         printf("Enter data...");
         gets(data);
         write(fd2,data,strlen(data));
         n=read(fd1,data,24);
         data[n]='\0';
         printf("server printed....%s\n",data);
         if(strcmp(data,"exit")==0)
         {
             exit(0);
         }
    }
}
