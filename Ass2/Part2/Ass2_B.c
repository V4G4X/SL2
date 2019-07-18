#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void accArr(int arr[], int n)                   //Accepts Array
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Enter Element %d.: ", i);
        scanf("%d", &arr[i]);
    }
}

void printArr(int arr[], int n)                 //Prints Array
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int arr[], int n)               //Sorts using Bubble Sort
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

int main()
{
    int n; 
    printf("This is Parent process\nProcess ID: %d\n", getpid());
    printf("Enter the size of Array: ");
    scanf("%d", &n);
    int *arr = (int *)calloc(sizeof(int), n); //Accept Array
    accArr(arr, n);
    printf("Array Accepted\nIt is as follows: ");
    printArr(arr, n);                                           //Before Sort
    printf("Parent Process before Fork Here, it will sort the array\n");
    bubbleSort(arr, n);
    printf("Sorted Array: ");                                   //After Sort
    printArr(arr, n);
    int forkID = fork(); //Fork and Create the Child Process
    if (forkID > 0)
    {
        //Parent Process Here, it will wait for child to EXECVE
        wait(NULL);
        printf("This is back to a line of parent\n");
    }
    if (forkID == 0)
    {
        printf("\n\nThis is Child process\nProcess ID: %d\n", getpid());
        //Convert Integers to Strings
        int i;
        char **argv;
        argv = (char**)calloc(sizeof(char*),n);
        for (i = 0; i < n; i++)
        {
            argv[i] = (char*)calloc(sizeof(char),n);
            sprintf(argv[i], "%d", arr[i]);
        }
        argv[n] = NULL;                                         //Final Element must be NULL
        printf("This is line before EXECVE\n");
        system("gcc Ass2_B2.c -o Ass2_B2");                     //Compile Second Program during runtime
        execve("./Ass2_B2", argv, NULL);

        printf("This is a printf after EXECVE\n");              //After EXECVE is done being executed, child process returns to Parent, this line doesn't Run
    }
    return 0;
}
