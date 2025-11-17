#include <stdio.h>

int H[100] = { 0 };
int n = 0;

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void upHeap(int i)
{
  int root = 1;
  int parent = i / 2;

  if (i <= root)
    return;

  if (H[i] <= H[parent])
    return;

  swap(&H[i], &H[parent]);
  upHeap(parent);
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

void insertItem(int key)
{
  n++;
  H[n] = key;
  upHeap(n);
}

int removeMax()
{
  int key = H[1];
  H[1] = H[n];
  n--;
  downHeap(1);
  return key;
}

void printHeap()
{
  for (int i = 1; i <= n; i++)
    printf(" %d", H[i]);
  printf("\n");
}

int main()
{
  char cmd;
  int key;

  while (1)
  {
    scanf("%c", &cmd);
    if (cmd == 'q')
      break;

    switch (cmd)
    {
    case 'i':
      {
        scanf("%d", &key);
        insertItem(key);
        printf("0\n");
        break;
      }
    case 'd':
      {
        key = removeMax();
        printf("%d\n", key);
        break;
      }
    case 'p':
      {
        printHeap();
        break;
      }
    default:
      break;
    }
  }

  return 0;
}