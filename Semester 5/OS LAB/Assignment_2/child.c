// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main(int argc, char *argv[])
// {
//     printf("\nChild process is reversing the array...\n");

//     for (int i = argc - 1; i > 1; i--)
//     {
//         int val = atoi(argv[i]);
//         printf("%d ", val);
//     }
//     printf("\n");

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    printf("\nChild process is running...\n");
    printf("Array elements received: ");
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\nArray elements in reverse order: ");
    for (int i = argc - 1; i >= 1; i--)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}

