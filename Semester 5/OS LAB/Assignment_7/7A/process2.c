// Process 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1024
int main()
{
    int fd1, fd2, num;
    char buffer[BUFFER_SIZE];
    char filename[] = "output.txt";
    FILE *fp;
    // Open the first pipe for reading
    fd1 = open("pipe1", O_RDONLY);
    // Open the second pipe for writing
    fd2 = open("pipe2", O_WRONLY);
    // Read input from the first pipe
    num = read(fd1, buffer, BUFFER_SIZE);
    // Count number of characters, words, and lines
    int char_count = 0, word_count = 0, line_count = 0;
    for (int i = 0; i < num; i++)
    {
        char_count++;
        if (buffer[i] == ' ' || buffer[i] == '\n')
        {
            word_count++;
        }
        if (buffer[i] == '\n')
        {
            line_count++;
        }
    }
    // Write output to file
    fp = fopen(filename, "w");
    fprintf(fp, "Number of characters: %d\n", char_count);
    fprintf(fp, "Number of words: %d\n", word_count);
    fprintf(fp, "Number of lines: %d\n", line_count);
    fclose(fp);
    // Read output from file
    fp = fopen(filename, "r");
    fgets(buffer, BUFFER_SIZE, fp);
    fclose(fp);

    // Write output to the second pipe
    write(fd2, buffer, strlen(buffer) + 1);
    // Close the pipes
    close(fd1);
    close(fd2);
    return 0;
}