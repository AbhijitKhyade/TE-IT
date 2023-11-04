#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t p;
    p = fork();
    if(p==0){
        printf("\nI am child process");
        printf("\nMy process ID: %d",getpid());
    }
    else{
        printf("\nI am parent process");
        printf("\nMy process ID: %d",getppid());
    }
    return 0;
}