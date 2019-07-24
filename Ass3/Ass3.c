#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int m, k1;
int k2, n;
int **matA = NULL;
int **matB = NULL;
int **matP = NULL;

struct prodData // Structure to pass Data Between Calling Function and
                // pthread_create
{
  int i;
  int j;
  int k;
};

void *getProdElement(struct prodData *data) // function that calculates value of
                                            // single element of final Product
                                            // Matrix
{
  int i = data->i;
  int j = data->j;
  int k = data->k;
  printf("The Created thread received i,j,k as %d,%d,%d\n", i, j, k);

  int x;
  int *prod = (int *)malloc(sizeof(int));
  for (x = 0; x < k; x++) {
    printf("matA[%d][%d] = %d\t", i, x, (matA[i][x]));
    printf("matB[%d][%d] = %d\n", x, j, (matB[x][j]));
    (*prod) += (matA[i][x] * matB[x][j]);
  }
  printf("Thread[%d][%d] returning value %d\n\n", i, j, *prod);
  matP[i][j] = *prod;
  return NULL;
}

void inputMatrix(int *mat[], int m, int n, char c) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("\nEnter %c[%d][%d]: ", c, i, j);
      scanf("%d", &mat[i][j]);
    }
  }
}

void printMatrix(int *mat[], int m, int n) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++)
      printf("%d\t", mat[i][j]);
    printf("\n");
  }
}

int main(int argc, const char **argv) {
  printf("Enter the size( m x n ) of Matrix A: "); // Ask for Matrix A's Order
  scanf("%d%d", &m, &k1);
  printf("Enter the size( m x n ) of Matrix B: "); // Ask for Matrix B's Order
  scanf("%d%d", &k2, &n);
  if (k1 != k2) {
    printf("Order Mismatch\nThe Matrix Multiplication is not Possible.\n");
    return 1;
  }
  int k = k1;
  // Declaring pthread pointers;
  pthread_t **thread = NULL;
  printf("Allocating Memory to base thread pointer\n");
  thread = (pthread_t **)calloc(sizeof(pthread_t *), m);

  // Allocating Memory to All Matrices
  printf("Allocating Memory to Double Pointers of All Matrices\n");
  matA = (int **)calloc(sizeof(int *), m);
  matB = (int **)calloc(sizeof(int *), k);
  matP = (int **)calloc(sizeof(int *), m);
  int i, j;
  printf("Allocating to Matrices A,P\n");
  for (i = 0; i < m; i++) {
    matA[i] = (int *)calloc(sizeof(int), k);
    matP[i] = (int *)calloc(sizeof(int), n);
    thread[i] = (pthread_t *)calloc(sizeof(pthread_t), n);
  }
  printf("Allocating to Matrices B\n");
  for (i = 0; i < k; i++)
    matB[i] = (int *)calloc(sizeof(int *), n);

  // Inputting Matrix Elements
  printf("Inputting Matrix Elements\n");
  // Matrix A
  printf("Matrix A\n");
  inputMatrix(matA, m, k, 'A');
  // Matrix B
  printf("Matrix B\n");
  inputMatrix(matB, k, n, 'B');

  // Printing the Matrices as Follows
  printf("The Matrix A is as Follows\n");
  printMatrix(matA, m, k);
  printf("The Matrix B is as Follows\n");
  printMatrix(matB, k, n);

  // Creating Thread Jobs
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      struct prodData *data =
          (struct prodData *)malloc(sizeof(struct prodData));
      data->i = i;
      data->j = j;
      data->k = k;
      printf("Creating Thread[%d][%d]\n", i, j);
      pthread_create(&thread[i][j], NULL, (void *)getProdElement, data);
      // sleep(2);
    }
  }
  sleep(3);
  // By Now the the individual elements of the Product matrix must be calculated
  // Hence we join all threads
  printf("Now we join all Threads\n");
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      // sleep(0.2);
      printf("Joining Thread[%d][%d]\n", i, j);
      pthread_join(thread[i][j], NULL);
    }
  }
  printf("The Final Product Matrix is as follows:\n");
  printMatrix(matP, m, n);

  return 0;
}