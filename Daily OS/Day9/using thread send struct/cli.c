#include "header.h"

void *client(void *p)
{
	MSG m , m1;
	int sockfd1 = *(int *)p , x = 5; 
	char    buff[50] , b1[50];
	int   n;  
	for(;;) { 	
		printf("enter line :\n") ;
		fgets(buff, 50, stdin) ;
		strcpy(m.message , buff);

		if(strcmp(buff, "quit\n") == 0)  
		   	pthread_exit((void *)&x);
	
		write(sockfd1 , m.message , strlen(m.message)) ;
		n = read(sockfd1, m1.message, 50) ; 
		write(1, m1.message, n) ;
	}
}


int main(void) 
{
	struct sockaddr_in  serv_addr ; 
	int sockfd , y;

	pthread_t t1 ;
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) ;
	bzero((char *)&serv_addr, sizeof(serv_addr)) ;
	serv_addr.sin_family = AF_INET ;
	serv_addr.sin_port = htons(PORT) ;
	inet_aton(IP, &(serv_addr.sin_addr)) ;

	connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) ;

	pthread_create(&t1 , 0 ,client ,(void *)&sockfd ); 
	 
	pthread_join(t1 , (void **)&y);

	close(sockfd) ;

	return (0);	
}


