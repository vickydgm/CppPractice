#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    int a=54325;
    char buffer[20];
    itoa(a,buffer,2);   // here 2 means binary
    printf("Binary value = %s\n", buffer);
 
    return 0;
}
