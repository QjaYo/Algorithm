//#define problem1_1
#ifdef problem1_1

#include <stdio.h>
#include <stdlib.h>

typedef struct node_
{
  char elem;
  struct node_ *prev;
  struct node_ *next;
} node;

typedef struct list_
{
  node *header;
  node *trailer;
  int size;
} list;

int initList(list *L)
{
  L->header = (node *)malloc(sizeof(node));
  L->trailer = (node *)malloc(sizeof(node));
  if (L->header == NULL || L->trailer == NULL)
    return -1;
  L->header->prev = NULL;
  L->header->next = L->trailer;
  L->trailer->prev = L->header;
  L->trailer->next = NULL;
  L->size = 0;
  return 0;
}

int add(list *L, const int r, const char e)
{
  if (r < 1 || r > L->size + 1)
    return -1;

  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
    return -1;
  new_node->elem = e;
  new_node->prev = NULL;
  new_node->next = NULL;

  node *p = L->header;
  for (int i = 1; i < r; i++)
    p = p->next;

  new_node->prev = p;
  new_node->next = p->next;
  p->next->prev = new_node;
  p->next = new_node;
  L->size++;

  return 0;
}

int delete(list *L, const int r)
{
  if (r < 1 || r > L->size)
    return -1;

  node *p = L->header;
  for (int i = 1; i < r; i++)
    p = p->next;

  node *to_delete = p->next;
  p->next = to_delete->next;
  to_delete->next->prev = p;
  free(to_delete);
  L->size--;

  return 0;
}

node *get(const list *L, const int r)
{
  if (r < 1 || r > L->size)
    return NULL;

  node *p = L->header;
  for (int i = 1; i <= r; i++)
    p = p->next;

  return p;
}

int print(const list *L)
{
  node *p = L->header->next;
  while (p != L->trailer)
  {
    printf("%c", p->elem);
    p = p->next;
  }
  printf("\n");
  return 0;
}

void freeList(list *L)
{
  node *p = L->header;
  node *next = NULL;
  while (p != NULL)
  {
    next = p->next;
    free(p);
    p = next;
  }
  L->header = L->trailer = NULL;
  L->size = 0;
}

int main()
{
  list L;
  initList(&L);

  int count;
  scanf("%d", &count);

  char command;
  char e;
  int r;

  for (int i = 0; i < count; i++)
  {
    // %c 앞에 공백을 추가하여 버퍼에 남아있는 개행문자 등을 무시합니다.
    scanf(" %c", &command);

    switch (command)
    {
    case 'A':
      {
        scanf("%d %c", &r, &e);
        if (add(&L, r, e) == -1)
          printf("invalid position\n");
        break;
      }
    case 'D':
      {
        scanf("%d", &r);
        if (delete(&L, r) == - 1)
          printf("invalid position\n");
        break;
      }
    case 'G':
      {
        scanf("%d", &r);
        node *result = get(&L, r);
        if (result == NULL)
          printf("invalid position\n");
        else
          printf("%c\n", result->elem);
        break;
      }
    case 'P':
      {
        print(&L);
        break;
      }

    default:
      break;
    }
  }

  freeList(&L);
  return 0;
}

#endif //problem1_1