#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *A, int n)
{
  for (int i = 1; i <= n - 1; i++)
  {
    int save = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > save)
    {
      A[j + 1] = A[j];
      j--;
    }
    A[j + 1] = save;
  }
}

int main()
{
  int n;

  scanf("%d", &n);
  int *A = (int *)malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++)
    scanf("%d", &A[i]);

  insertionSort(A, n);

  for (int i = 0; i < n; i++)
    printf(" %d", A[i]);

  free(A);

  return 0;
}