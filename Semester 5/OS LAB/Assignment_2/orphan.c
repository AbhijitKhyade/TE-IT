#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t p;
    p = fork();
    if(p == 0){  //child
        sleep(10);
        printf("\nI am child...");
        printf("\nMy process ID: %d", getpid());
        printf("\nMy parent process ID: %d", getppid());
    }
    else{   //parent
        sleep(2);  
        printf("\nI am parent...");
        printf("\nMy process ID: %d", getpid());
        printf("\nMy child process ID: %d", p);
    }
    return 0;
}