#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortAsc(int a[], int n)
{
    int i = 0, j = 0;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

void bubbleSortDesc(int a[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] < a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

void accArr(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("Array Element %d:\n", i);
        scanf("%d", &a[i]);
    }
}

void printArr(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

int main()
{
    int n = 0;
    int pid = getpid(), pidC = 0;
    printf("The currect pid is %d.\n", pid);
    printf("Enter the number of terms in the array:");
    scanf("%d", &n);
    int *arr = (int *)calloc(sizeof(int), n);
    accArr(arr, n);                         //Accept Array
    printArr(arr, n);                       //Print Unsorted Array
    printf("\n");
    bubbleSortDesc(arr, n);
    printArr(arr, n);                       //Sort Descending ordered Array
    printf("\n");

    int forkId = fork();
    if (forkId == 0)
    {
        sleep(1);                         //Child will sleep for a second  
        printf("\nThis is Child Process\n");
        printf("It's PID is %d\nIts PPID is %d\n", getpid(), getppid());
        bubbleSortAsc(arr, n);            //Child sorts ascendingly BubbleSort
        printArr(arr, n);
        while (1)                         //Infinite Loop so that can be viewed in Terminal
        {
        }
    }
    else
    {
        return 0;                       //Parent will execute itself
    }
    return 0;
}