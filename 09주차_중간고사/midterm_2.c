#include <stdio.h>
#include <stdlib.h>

int n, k, *A;

int rFindElementLocation(int k, int l, int r)
{
  if (l > r)
    return -1;

  int mid = (l + r) / 2;
  if (A[mid] == k)
  {
    return mid;
  }
  else if (A[mid] > k)
  {
    printf("%d", 0);
    return rFindElementLocation(k, l, mid - 1);
  }
  else //A[mid] < k
  {
    printf("%d", 1);
    return rFindElementLocation(k, mid + 1, r);
  }
}

int findElementLocation(int k)
{
  return rFindElementLocation(k, 0, n - 1);
}

int main()
{
  scanf("%d %d", &n, &k);
  A = (int *)malloc(sizeof(int) * n);
  for (int i = 0;i < n;i++)
    scanf("%d", &A[i]);

  int loc = findElementLocation(k);
  printf(" %d\n", loc);

  free(A);

  return 0;
}
