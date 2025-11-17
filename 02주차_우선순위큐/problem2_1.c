#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectionSort(int *A, int n)
{
  for (int i = n - 1; i >= 1; i--)
  {
    int maxLoc = i;
    for (int j = i; j >= 0; j--)
    {
      if (A[j] > A[maxLoc])
        maxLoc = j;
    }
    swap(&A[i], &A[maxLoc]);
  }
}

int main()
{
  int n;

  scanf("%d", &n);
  int *A = (int *)malloc(sizeof(int) * n);

  for (int i = 0;i < n;i++)
    scanf("%d", &A[i]);

  selectionSort(A, n);

  for (int i = 0;i < n;i++)
    printf(" %d", A[i]);

  free(A);

  return 0;
}