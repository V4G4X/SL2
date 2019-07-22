#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int binarySearch(int arr[], int n, int key)             //Simple Binary Search for integers
{
    int i = 0;
    while (i < n)
    {
        if (key == arr[(i + n) / 2])
            return (i + n) / 2;
        else if (key < arr[(i + n) / 2])
            n = (i + n) / 2;
        else if (key > arr[(i + n) / 2])
            i = (i + n) / 2 + 1;
    }
    return -1;
}

void convert(int *arr, const char **argv, int argc)     //Converts the recieved arguments from string to integer
{
    int i;
    for (i = 0; i < argc; i++)
        arr[i] = atoi(argv[i]);
}

int main(int argc, char const *argv[], char *envp[])
{
    printf("This is the new Executed Process.\nProcess ID: %d",getpid());
    int *arr = (int *)calloc(sizeof(int), argc);
    convert(arr, argv, argc);                           //Converts the recieved arguments from string to integer
    printf("\n");
    printf("Enter a Search Key: ");
    int key;
    scanf("%d", &key);
    key = binarySearch(arr, argc, key);
    if (key == -1)
        printf("The key is not in array\n");
    else
        printf("The key is at index: %d\n", key);
    return 0;
}
