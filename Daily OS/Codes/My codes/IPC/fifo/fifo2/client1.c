
   // program for client will send the file to server and data will be converted accoring to condition 
 #include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "inc.h"

 int main()
 {
     int togal_flag;
     char data[100];
     char filename[20];
      printf(" Enter the file name =\n");
      scanf("%s",filename);
      mkfifo(filename,S_IRUSR|S_IWUSR);                    	//fifo
	int fd1=open(filename,O_RDWR);
	if(fd1==-1)
             {

                printf("file not found ");
                 return ;
             }
      printf("Enter the toggle_flag =");
      scanf("%d",&togal_flag);
      getchar();
      printf("\n Enter the data =");
      scanf("%[^\n]",data);
       
       write(fd1,data,sizeof(data));
      

       




 return 0;
 }
