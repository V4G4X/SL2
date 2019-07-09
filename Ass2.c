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
    printf("Enter the number of terms in the array:");
    scanf("%d", &n);
    int *arr = (int *)calloc(sizeof(int), n);
    accArr(arr, n);
    printArr(arr, n);
    printf("pid is %d\n", getpid());
    int forkId = fork();
    if (forkId == 0)
    {
        printf("pid is %d\n", getpid());
        if (pid == getpid())
        {
            printf("This is the parent process\n");
            
        }
        else if (getppid() == pid)
        {
            printf("This is the child process\n");
        }
    }
    return 0;
}