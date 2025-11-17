#include <stdio.h>
#include <stdlib.h>

char *info;
int n;

int findElement_nonRecursive(int a, int b)
{
  if (a > b)
  {
    printf("no number satisfies the condition\n");
    return -1;
  }

  for (int i = 0; i < n; i++)
  {
    char answer = info[i];
    int mid = a + (b - a) / 2;

    //is (k > mid) true?
    if (answer == 'Y')
      a = mid + 1;
    else if (answer == 'N')
      b = mid;
    else
    {
      printf("invalid answer\n");
      return -1;
    }
  }

  if (a == b)
    return a;
  else
  {
    printf("no number satisfies the condition\n");
    return -1;
  }
}

int findElement_recursive(int a, int b)
{
  if (a > b)
    return -1;
  else if (a == b)
    return a;

  static int i = 0;
  int mid = a + (b - a) / 2;
  char answer = info[i++];

  if(answer == 'Y')
    return findElement_recursive(mid + 1, b);
  else if (answer == 'N')
    return findElement_recursive(a, mid);
  else
    return -1;
}

int main()
{
  int a, b;
  scanf("%d %d %d", &a, &b, &n);

  info = (char *)malloc(sizeof(char) * n);
  scanf("%s", info);

  printf("%d\n", findElement_recursive(a, b));

  free(info);

  return 0;
}
