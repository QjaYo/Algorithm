#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char name;
  int priority;
} Process;

Process H[10];
int n = 0;

void swap(Process *a, Process *b)
{
  Process temp = *a;
  *a = *b;
  *b = temp;
}

void upHeap(int i)
{
  int root = 1;
  int parent = i / 2;

  if (i <= root)
    return;

  if (H[i].priority >= H[parent].priority)
    return;

  swap(&H[i], &H[parent]);
  upHeap(parent);
}

void insertProcess(Process p)
{
  n++;
  H[n] = p;
  upHeap(n);
}

void printHeap()
{
  for (int i = 1;i <= n;i++)
    printf("%c %d\n", H[i].name, H[i].priority);
}

int main()
{
  while (1)
  {
    char cmd;
    scanf(" %c", &cmd);

    if (cmd == 'i')
    {
      char name;
      int priority;
      scanf(" %c %d", &name, &priority);
      insertProcess((Process) { name, priority });
    }
    else if (cmd == 'd')
    {
      ;
    }
    else if (cmd == 'p') //just for debugging
    {
      printHeap();
    }
    else if (cmd == 'q')
    {
      printHeap();
      return 0;
    }
    else
    {
      printf("Invalid Command\n");
    }
  }

  return 0;
}