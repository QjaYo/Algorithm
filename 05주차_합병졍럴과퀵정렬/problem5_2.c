#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int *A = NULL;
int n = 0;

void swap(int *p, int *q)
{
  int tmp = *p;
  *p = *q;
  *q = tmp;
}

void buildArray(int n)
{
  A = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i < n;i++)
    scanf("%d", &A[i]);
}

int findPivot(int l, int r)
{
  return rand() % (r - l + 1) + l;
}

int inPlacePartition_Hoare(int l, int r, int k)
{
  int p = A[k];
  swap(&A[r], &A[k]);

  int i = l;
  int j = r - 1;

  while (i <= j)
  {
    while (i <= j && A[i] <= p)
      i++;
    while (i <= j && A[j] >= p)
      j--;
    if (i < j)
      swap(&A[i], &A[j]);
  }
  swap(&A[r], &A[i]);
  return i;
}

int inPlacePartition_Lomuto(int l, int r, int k)
{
  int p = A[k];
  swap(&A[k], &A[r]);

  int gt = l;

  for (int cur = l; cur < r; cur++)
  {
    if (A[cur] < p)
    {
      swap(&A[cur], &A[gt]);
      gt++;
    }
  }
  swap(&A[gt], &A[r]);
  return gt;
}

void inPlaceQuickSort_unique(int l, int r)
{
  if (l >= r)
    return;

  int k = findPivot(l, r);
  k = inPlacePartition_Hoare(l, r, k);
  //k = inPlacePartition_Lomuto(l, r, k);

  inPlaceQuickSort_unique(l, k - 1);
  inPlaceQuickSort_unique(k + 1, r);
}

typedef struct _vec2
{
  int x;
  int y;
} vec2;

vec2 inPlacePartition_3way(int l, int r, int k)
{
  int p = A[k];
  swap(&A[k], &A[r]);

  int eq_start = l;
  int eq_end = r-1;

  int cur = l;
  while (cur <= eq_end)
  {
    if (A[cur] < p)
    {
      swap(&A[cur], &A[eq_start]);
      eq_start++;
      cur++;
    }
    else if (A[cur] > p)
    {
      swap(&A[cur], &A[eq_end]);
      eq_end--;
    }
    else
      cur++;
  }
  swap(&A[eq_end + 1], &A[r]);
  return (vec2) { eq_start, eq_end + 1 };
}

void inPlaceQuickSort_duplicate(int l, int r)
{
  if (l >= r)
    return;

  int k = findPivot(l, r);
  vec2 EQ = inPlacePartition_3way(l, r, k);

  inPlaceQuickSort_duplicate(l, EQ.x - 1);
  inPlaceQuickSort_duplicate(EQ.y + 1, r);
}

void printArray()
{
  for (int i = 0;i < n;i++)
    printf(" %d", A[i]);
}

int main()
{
  scanf("%d", &n);
  buildArray(n);

  srand(time(NULL));

  inPlaceQuickSort_duplicate(0, n - 1);

  printArray();

  return 0;
}