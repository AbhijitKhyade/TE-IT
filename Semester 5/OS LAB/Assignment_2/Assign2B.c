#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n)
{
    int temp, i, j;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

int main()
{

    int n;
    printf("\nEnter the size of Array: ");
    scanf("%d", &n);

    int arr[n];
    // Input array elements
    printf("Enter %d element: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Fork system call to create a child process
    pid_t p;
    p = fork();

    // Parent process
    if (p > 0)
    {
        printf("\nI am parent...");
        printf("\nMy process ID: %d", getpid());
        printf("\n");
        // printArray(arr,n);
        bubbleSort(arr,n);
        printf("\nArray is sorted in Parent Process");
        printf("\n");
        wait(NULL); 
    }
    else
    {
        printf("\nI am child...");
        printf("\nMy process ID: %d", getpid());
        printf("\n");
        bubbleSort(arr, n);
        char str[100]; // String to store the serialized array  // for dynamic memory allocation use malloc
        int index = 0;

        for (int i = 0; i < n; i++)
        {
            // Use sprintf to convert the integer to a string
            index += sprintf(str + index, "%d", arr[i]);

            if (i != n - 1)
            {
                str[index++] = ','; // Add a comma separator
            }
        }

        str[index] = '\0'; // Null-terminate the string
        printf("Serialized array: %s\n", str);
        char *args[] = {"/home/vishwas/Desktop/OS/child", str, NULL};
        execve("/home/vishwas/Desktop/OS/child", args, NULL);
        perror("execve");
        exit(1);
    }
}