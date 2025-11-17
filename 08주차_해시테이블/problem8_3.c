#include <stdio.h>
#include <stdlib.h>

//global variables
int M;
int *H;
int n;
int q;

int h(int x)
{
  return x % M;
}

int h_(int x)
{
  return q - (x % q);
}

int getNextBucket(int v, int stride, int i)
{
  return (v + i * stride) % M;
}

void init()
{
  H = (int *)malloc(sizeof(int) * M);
  for (int i = 0;i < M;i++)
    H[i] = 0;
}

int insert(int x)
{
  int v = h(x);
  int i = 0;
  while (i < M)
  {
    int b = getNextBucket(v, h_(x), i);
    if (H[b] == 0)
    {
      H[b] = x;
      return b;
    }
    else
    {
      printf("C");
      i++;
    }
  }
  return -1;
}

int search(int x)
{
  int v = h(x);
  int i = 0;
  while (i < M)
  {
    int b = getNextBucket(v, h_(x), i);
    if (H[b] == 0)
      return -1;
    else if (H[b] == x)
      return b;
    else
    {
      i++;
    }
  }
  return -1;
}

void print()
{
  for (int i = 0;i < M;i++)
  {
    printf(" %d", H[i]);
  }
  printf("\n");
}

int main()
{
  scanf("%d %d %d", &M, &n, &q);

  char cmd;
  int key;
  int result;

  init();

  while (1)
  {
    scanf(" %c", &cmd);
    switch (cmd)
    {
    case 'i':
      {
        scanf("%d", &key);
        result = insert(key);
        printf("%d\n", result);
        break;
      }
    case 's':
      {
        scanf("%d", &key);
        result = search(key);
        if (result == -1)
          printf("-1\n");
        else
          printf("%d %d\n", result, H[result]);
        break;
      }
    case 'p':
      {
        print();
        break;
      }
    case 'e':
      {
        print();
        free(H);
        exit(0);
        break;
      }
    }
  }

  return 0;
}