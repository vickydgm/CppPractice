#include<stdio.h>
#include<string.h>


int main()
{
 int fd1[10] , fd2[10] ;
  pipe(fd1);
  pipe(fd2); 

 if(fork()) //par
 {
   char str[15];
   int n; 
   close(fd1[0]) ; close(fd2[1]) ;
   write(fd1[1] ,"Smruti" ,6);

   n = read(fd2[0] ,str ,10);
   str[n] ='\0' ;
   printf("Par ::: %s ",str);
   
 }
 else //child
 {
 char ch[10] ;
 int n ;
 close(fd1[1] ); close(fd2[0]);
 n =read(fd1[0] ,ch , 15);
 ch[n] ='\0' ;
 printf(" %s\n",ch); 

 printf("chars -> %s \nEnter Data ::: ",ch);
 scanf("%s",ch);
 write(fd2[1] ,ch ,strlen(ch));
 } 

 return (0);
}
