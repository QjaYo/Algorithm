#include <stdio.h>
#include <stdlib.h>

typedef struct _node_
{
  int key;
  struct _node_ *next;
} node;

//global variables
int M;
node **H;

node *create_node(int key, node *next)
{
  node *new_node = (node *)malloc(sizeof(node));
  new_node->key = key;
  new_node->next = next;
  return new_node;
}

int h(int x)
{
  return x % M;
}

void init()
{
  for (int i = 0;i < M;i++)
    H[i] = create_node(-1, NULL); //header
}

void insert(int x)
{
  int v = h(x);
  node *header = H[v];
  node *next = header->next;
  node *new = create_node(x, next);
  header->next = new;
}

int search(int x)
{
  int v = h(x);
  node *cur = H[v]->next;
  int rank = 1;
  while (cur != NULL)
  {
    if (cur->key == x)
      return rank;
    else
      cur = cur->next;
    rank++;
  }
  return 0;
}

int delete(int x)
{
  int v = h(x);
  node *prev = H[v];
  node *cur = H[v]->next;
  int rank = 1;
  while (cur != NULL)
  {
    if (cur->key == x)
    {
      prev->next = cur->next;
      free(cur);
      return rank;
    }
    else
    {
      cur = cur->next;
      prev = prev->next;
    }
    rank++;
  }
  return 0;
}

void print()
{
  for (int i = 0;i < M;i++)
  {
    node *cur = H[i]->next;
    while (cur != NULL)
    {
      printf(" %d", cur->key);
      cur = cur->next;
    }
  }
  printf("\n");
}

void freeH(node **H)
{
  for (int i = 0;i < M;i++)
  {
    node *cur = H[i];
    while (cur != NULL)
    {
      node *next = cur->next;
      free(cur);
      cur = next;
    }
  }
  free(H);
}

int main()
{
  scanf("%d", &M);
  H = (node **)malloc(sizeof(node *) * M);

  init();

  char cmd;
  int key;
  int result;

  while (1)
  {
    scanf("%c", &cmd);
    switch (cmd)
    {
    case 'i':
      {
        scanf("%d", &key);
        insert(key);
        break;
      }
    case 's':
      {
        scanf("%d", &key);
        result = search(key);
        printf("%d\n", result);
        break;
      }
    case 'd':
      {
        scanf("%d", &key);
        result = delete(key);
        printf("%d\n", result);
        break;
      }
    case 'p':
      {
        print();
        break;
      }
    case 'e':
      {
        free(H);
        exit(0);
        break;
      }
    }
  }

  return 0;
}