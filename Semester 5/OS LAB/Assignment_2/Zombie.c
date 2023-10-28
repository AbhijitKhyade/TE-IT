#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>


int main(){

    pid_t p;
    p = fork();
    if(p == 0){
        printf("\nI am child...");
        printf("\nMy process ID: %d", getpid());
        printf("\nMy parent process ID: %d", getppid());
    }
    else{
        sleep(10);  //to remove child from zombie process use wait() in parent 
        printf("\nI am parent...");
        printf("\nMy process ID: %d", getpid());
        printf("\nMy child process ID: %d", p);
    }
    return 0;
}