#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void accArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Enter Element %d.: ", i);
        scanf("%d", &arr[i]);
    }
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    printf("This is Parent process\nProcess ID: %d\n", getpid());
    int n;
    printf("Enter the size of Array: ");
    scanf("%d", &n);
    int *arr = (int *)calloc(sizeof(int), n); //Accept Array
    accArr(arr, n);
    printf("Array Accepted\nIt is as follows: ");
    printArr(arr, n);
    int forkID = fork(); //Fork and Create the Child Process
    if (forkID > 0)
    {
        //Parent Process Here, it will sort the array
        printf("Parent Process Here, it will sort the array\n");
        bubbleSort(arr, n);
        printf("Sorted Array: ");
        printArr(arr, n);
    }
    if (forkID == 0)
    {
        //Child process here, it will wait for Parent to sort the array, it will run EXECVE
        sleep(1);
        //Convert Integers to Strings
        int i;
        char argv[n][n];
        for (i = 0; i < n; i++)
            sprintf(argv[i], "%d", arr[i]);
        //Testing if sprintf works
        for (i = 0; i < n; i++)
            printf("%s\n", argv[i]);
        system("gcc Ass2_B2.c -o Ass2_B2");
        execve("Ass2_B2", argv, NULL);
    }

    return 0;
}
