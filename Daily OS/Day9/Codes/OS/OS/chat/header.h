#define KEY 1000
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
struct myst
{
    char messege[80];
    int pid;
};
struct msg
{
   long mtype;
   struct myst messeg;
};
struct init
{
   long mtype;
   int pid;
};
