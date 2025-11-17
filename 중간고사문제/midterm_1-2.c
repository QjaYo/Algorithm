#include <stdio.h>
#include <stdlib.h>

int padovan_nonrecur(int n)
{
  if (n == 0 || n == 1 || n == 2)
    return 1;

  int p_prev3 = 1;
  int p_prev2 = 1;
  int p_prev1 = 1;
  int pn;

  for (int i = 3; i <= n; i++)
  {
    pn = p_prev2 + p_prev3;
    p_prev3 = p_prev2;
    p_prev2 = p_prev1;
    p_prev1 = pn;
  }

  return pn;
}

int main()
{
  int n;
  scanf("%d", &n);

  int result = padovan_nonrecur(n);
  printf("%d\n", result);

  return 0;
}