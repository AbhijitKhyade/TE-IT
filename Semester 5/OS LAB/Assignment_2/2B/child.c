#include<stdio.h>

int main(int argc, char *argv[]){
    int arr[10];
    printf("\n");
    printf("\t\t\tEntered in new child program :)");
    printf("\n");
    //convert string to integer
    for(int i=0;i<argc;i++){
        arr[i] = atoi(argv[i]);
    }
    printf("\nEnter no to search: ");
    int val;
    scanf("%d", &val);

    int low =0, high=argc-1;
    while(low<=high){
        int mid = (low+high)/2;
        if(arr[mid] == val){
            printf("\nThe value found in array :)\n");
            return;
        }
        else if(val < arr[mid]){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    if(low > high){
        printf("\nThe value not found in array :(\n");
    }
    return 0;
}