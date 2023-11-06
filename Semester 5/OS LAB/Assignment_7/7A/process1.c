// Process 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024
int main(){
    int fd1, fd2, num;
    char buffer[BUFFER_SIZE];
    // Create the first pipe
    if (mkfifo("pipe1", 0666) < 0){
        perror("mkfifo");
        exit(1);
    }
    // Create the second pipe
    if (mkfifo("pipe2", 0666) < 0){
        perror("mkfifo");
        exit(1);
    }
    // Open the first pipe for writing
    fd1 = open("pipe1", O_WRONLY);
    // Open the second pipe for reading
    fd2 = open("pipe2", O_RDONLY);
    // Read input from user
    printf("Enter a sentence: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    // Write input to the first pipe
    write(fd1, buffer, strlen(buffer) + 1);
    // Read output from the second pipe
	while ((num = read(fd2, buffer, BUFFER_SIZE)) > 0){
		write(STDOUT_FILENO, buffer, num); // Display to the console
	}
    // Close the pipes
    close(fd1);
    close(fd2);
    // Remove the pipes
    unlink("pipe1");
    unlink("pipe2");
    return 0;
}