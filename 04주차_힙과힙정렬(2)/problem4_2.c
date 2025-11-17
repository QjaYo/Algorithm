#include <stdio.h>

int H[101];
int n;

/////////////////////////////FUNC//////////////////////////////

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void downHeap(int i, int last)
{
  int left = i * 2;
  int right = i * 2 + 1;

  if (left > last)
    return;

  int greater = left;
  if (right <= last)
    if (H[left] < H[right])
      greater = right;

  if (H[greater] <= H[i])
    return;

  swap(&H[i], &H[greater]);
  downHeap(greater, last);
}

void buildMaxHeap()
{
  for (int i = n; i >= 1; i--)
    downHeap(i, n);
}

void inPlaceHeapSort()
{
  buildMaxHeap();
  for (int i = n; i >= 2; i--)
  {
    swap(&H[1], &H[i]);
    downHeap(1, i - 1);
  }
}

void printArray()
{
  for (int i = 1;i <= n;i++)
    printf(" %d", H[i]);
  printf("\n");
}

/////////////////////////////MAIN//////////////////////////////

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n;i++)
    scanf("%d", &H[i]);

  inPlaceHeapSort();
  printArray();
}