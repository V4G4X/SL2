#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int binarySearch(int arr[], int n, int key)
{
    int i;
    while (i < n)
    {
        if (key == arr[(i + n) / 2])
            return i;
        else if (key < arr[(i + n) / 2])
            n = n / 2 - 1;
        else if (key > arr[(i + n) / 2])
            i = n / 2 + 1;
    }
    return i;
}

int main(int argc, char const *argv[])
{
    printf("This is a new Executable.\n");  
    exit(0);
    return 0;
}
