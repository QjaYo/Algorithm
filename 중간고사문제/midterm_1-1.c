#include <stdio.h>
#include <stdlib.h>

int call_count = 0;

int padovan_recur(int n)
{
  call_count++;

  if (n == 0 || n == 1 || n == 2)
    return 1;

  return padovan_recur(n - 2) + padovan_recur(n - 3);
}

int main()
{
  int n;
  scanf("%d", &n);

  int result = padovan_recur(n);

  printf("%d %d\n", result, call_count);

  return 0;
}