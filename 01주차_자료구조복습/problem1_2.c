//#define problem1_2
#ifdef problem1_2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_
{
  int number;
  struct node_ *left;
  struct node_ *right;
} node;

typedef struct tree_
{
  node *root;
} tree;

void initTree(tree *T)
{
  T->root = NULL;
}

node *getnode(const int data, node *left, node *right)
{
  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
    return NULL;
  new_node->number = data;
  new_node->left = left;
  new_node->right = right;
  return new_node;
}

node *rBuildTree()
{
  int x, y, z;

  if (scanf("%d %d %d", &x, &y, &z) != 3)
    return NULL;

  node *v = getnode(x, NULL, NULL);
  if (v == NULL)
  {
    printf("malloc failed\n");
    return NULL;
  }

  if (y != 0)
    v->left = rBuildTree();

  if (z != 0)
    v->right = rBuildTree();

  return v;
}

void buildTree(tree *T)
{
  T->root = rBuildTree();
}

void printTree(node *v) {
  if (v == NULL)
    return;
  printf(" %d", v->number);
  printTree(v->left);
  printTree(v->right);
}

void freeTree(node *v) {
  if (v == NULL)
    return;
  freeTree(v->left);
  freeTree(v->right);
  free(v);
}

int main()
{
  int n_node;
  scanf("%d", &n_node);

  tree T;
  initTree(&T);
  buildTree(&T);

  int n_cmd;
  scanf("%d", &n_cmd);

  char cmd[101];
  cmd[0] = '\0';

  for (int i = 0; i < n_cmd; i++)
  {
    scanf("%s", cmd);
    node *cur = T.root;
    for (int j = 0; j < strlen(cmd); j++) {
      printf(" %d", cur->number);
      if (cmd[j] == 'L')
        cur = cur->left;
      else if (cmd[j] == 'R')
        cur = cur->right;
    }
    printf(" %d", cur->number);
    printf("\n");
  }

  freeTree(T.root);

  return 0;
}

#endif //problem1_2
