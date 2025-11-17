#include <stdio.h>
#include <stdlib.h>

typedef struct node_
{
  int data;
  struct node_ *next;
} node;

node *createNode(int data, node *next)
{
  node *newnode = (node *)malloc(sizeof(node));
  *newnode = (node) { data, next };
  return newnode;
}

node* buildList(int n)
{
  node *L = createNode(0, NULL);
  node *last = L;

  for (int i = 0;i < n;i++)
  {
    int input;
    scanf("%d", &input);
    node *newnode = createNode(input, NULL);
    last->next = newnode;
    last = newnode;
  }

  return L;
}

void deleteList(node* L)
{
  node *cur = L;
  while (cur != NULL)
  {
    node *del = cur;
    cur = cur->next;
    free(del);
  }
}

node* getMiddle(node *L)
{
  if (L == NULL || L->next == NULL)
    return L;

  node *slow = L;
  node *fast = L->next;

  while (fast != NULL && fast->next != NULL)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  return slow;
}

node *merge(node *L1, node *L2)
{
  node *n1 = L1->next;
  node *n2 = L2->next;
  node *header = createNode(0, NULL);
  node *last = header;
  while (n1 != NULL && n2 != NULL)
  {
    if (n1->data <= n2->data)
    {
      last->next = n1;
      n1 = n1->next;
    }
    else
    {
      last->next = n2;
      n2 = n2->next;
    }
    last = last->next;
  }
  while (n1 != NULL)
  {
    last->next = n1;
    n1 = n1->next;
    last = last->next;
  }
  while (n2 != NULL)
  {
    last->next = n2;
    n2 = n2->next;
    last = last->next;
  }

  return header;
}

node* mergeSort(node* L)
{
  //두개로 분할하기 위한 최소조건 (항 두개 이상)
  if (L->next == NULL || L->next->next == NULL)
    return L;
  
  node *L1 = L;
  node *mid = getMiddle(L);
  node *L2 = createNode(0, mid->next);
  mid->next = NULL;

  L1 = mergeSort(L1);
  L2 = mergeSort(L2);

  node *sortedL = merge(L1, L2);

  free(L1);
  free(L2);

  return sortedL;
}

void printList(node *L)
{
  node *cur = L->next;
  while (cur != NULL)
  {
    printf(" %d", cur->data);
    cur = cur->next;
  }
  printf("\n");
}

int main()
{
  int n;
  scanf("%d", &n);
  node *L = buildList(n);

  L = mergeSort(L);

  printList(L);

  deleteList(L);

  return 0;
}