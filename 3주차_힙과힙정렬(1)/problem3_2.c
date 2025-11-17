#include <stdio.h>

int H[100] = { 0 };
int n = 0;

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void downHeap(int i)
{
  int left = i * 2;
  int right = i * 2 + 1;

  if (left > n)
    return;

  int greater = left;
  if (right <= n)
    if (H[left] < H[right])
      greater = right;

  if (H[greater] <= H[i])
    return;

  swap(&H[i], &H[greater]);
  downHeap(greater);
}

void rBuildHeap(int i)
{
  if (i > n)
    return;

  int left = 2 * i;
  int right = 2 * i + 1;

  rBuildHeap(left);
  rBuildHeap(right);
  downHeap(i);
}

void buildHeap_recur()
{
  rBuildHeap(1);
}

void buildHeap_nonrecur()
{
  for (int i = n / 2; i >= 1; i--)
    downHeap(i);
  return;
}

void printHeap()
{
  for (int i = 1; i <= n; i++)
    printf(" %d", H[i]);
  printf("\n");
}

int main()
{
  int n_key;
  scanf("%d", &n_key);

  for (int i = 1; i <= n_key;i++)
    scanf("%d", &H[i]);
  n = n_key;

  buildHeap_nonrecur();

  printHeap();

  return 0;
}