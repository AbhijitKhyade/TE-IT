#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void bubbleSort(int arr[], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1-i;j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void print_array(int arr[], int n){
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter array elements: ");
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }

    pid_t id;
    id = fork();
    if(id == 0){
        printf("\nIn Child Process...");
        printf("\nMy Process ID: %d",getpid());
        printf("\nMy parent Process ID: %d",getppid());
        bubbleSort(arr,n);
        printf("\nArray Sorted in child.");
        print_array(arr,n);
        char *arg[10], str[15];
        int i;
        for(i=0;i<n;i++){
            sprintf(str,"%d",arr[i]);
            arg[i] = malloc(sizeof(str));
            strcpy(arg[i],str);
        }
        arg[i] = NULL; //Null terminator for string
        printf("\nExecuting execve Statement\n");
        execve("./child", arg, NULL);

    }
    else if(id > 0){
        printf("\nIn Parent Process...");
        printf("\nMy Process ID: %d",getpid());
        printf("\nMy Child Process ID: %d",id);
        printf("\nParent is waiting to complete the child ...");
        printf("\n");
        wait(NULL);
        printf("\nChild execution Completed :)\n");
    }
    else{
        printf("\nChild not created.");
    }
    return 0;
}