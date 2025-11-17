#include <stdio.h>
#include <stdlib.h>

int n, k, *A;

/*
int findElementLocation(int k)
{
  int l = 0;
  int r = n - 1;
  int loc = n;

  while (l <= r)
  {
    int mid = l + (r - l) / 2;

    if (A[mid] == k)
      return mid;

    else if (A[mid] > k)
    {
      r = mid - 1;
      loc = mid;
    }

    else
    {
      l = mid + 1;
    }
  }
  return loc;
}
*/

int findElementLocation(int k)
{
  int l = 0;
  int r = n - 1;

  while (l <= r)
  {
    int mid = l + (r - l) / 2;

    if (A[mid] == k)
      return mid;

    else if (A[mid] > k)
      r = mid - 1;

    else
      l = mid + 1;
  }
  return l;
}

int main()
{
  scanf("%d %d", &n, &k);
  A = (int *)malloc(sizeof(int) * n);
  for (int i = 0;i < n;i++)
    scanf("%d", &A[i]);

  int loc = findElementLocation(k);
  printf("%d\n", loc);

  free(A);

  return 0;
}
