#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n){
    int temp, i, j;
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
// Function to perform selection Sort
void selectionSort(int arr[], int n) {
    int i, j, min_index;
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        // Find the index of the minimum element in the unsorted part of the array
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        // Swap the found minimum element with the first element
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

void printArray(int arr[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
}

int main(){
    int n;
    printf("\nEnter the size of Array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d element: ", n);
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    pid_t p;
    p = fork();

    // Child process
    if (p == 0){
        printf("\n");
        // sleep(2);
        printf("\nI am child...");
        printf("\nMy process ID: %d", getpid());
        printf("\nMy parent process ID: %d", getppid());
        printf("\n");
        // printf("\nIn Child Process");
        printf("\nArray after sorting in child process: ");
        bubbleSort(arr, n);
        printArray(arr, n);
        system("ps");
    }
    // parent process
    else{
        printf("\n");
        // sleep(5);
        printf("\nI am parent...");
        printf("\nMy process ID: %d", getpid());
        printf("\nMy child process ID: %d", p);
        printf("\n");
        printf("\nArray after sorting in parent process: ");
        selectionSort(arr, n);
        printArray(arr, n);
        system("ps");
        // wait(NULL); //for avoiding zombie
    }
}