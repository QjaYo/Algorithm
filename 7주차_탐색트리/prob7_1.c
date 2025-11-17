#include <stdio.h>
#include <stdlib.h>

typedef struct _node_
{
  int key;
  struct _node_ *parent;
  struct _node_ *left;
  struct _node_ *right;
} node;

typedef struct _tree_
{
  node *root;
} tree;

//global variable
tree T;

node *create_node(int key, node *parent)
{
  node *new_node = (node *)malloc(sizeof(node));
  new_node->key = key;
  new_node->parent = parent;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

int isExternal(node *v)
{
  return (v->left == NULL && v->right == NULL);
}

void expandExternal(node *v)
{
  v->left = create_node(-1, v);
  v->right = create_node(-1, v);
}

node *sibling(node *v)
{
  if (v->parent == NULL)
    return NULL;
  if (v == v->parent->left)
    return v->parent->right;
  else
    return v->parent->left;
}

void reduceExternal(node *z)
{
  //z is not root node
  node *p = z->parent;
  node *zs = sibling(z);
  if (p->parent == NULL)
  {
    zs->parent = NULL;
    T.root = zs;
  }
  else
  {
    node *g = p->parent;
    zs->parent = g;
    if (p == g->left)
      g->left = zs;
    else
      g->right = zs;
  }
  free(p);
  free(z);
}

node *search_node(node *v, int k)
{
  if (isExternal(v))
    return v;
  if (k == v->key)
    return v;
  else if (k < v->key)
    return search_node(v->left, k);
  else
    return search_node(v->right, k);
}

void insert_node(node *v, int k)
{
  node *w = search_node(v, k);
  if (!isExternal(w))
    return;
  else
  {
    w->key = k;
    expandExternal(w);
  }
}

node *inOrderSuccessor(node *v)
{
  if (!isExternal(v->right))
  {
    node *y = v->right;
    while (!isExternal(y->left))
      y = y->left;
    return y;
  }
  else
  {
    node *y = v;
    node *p = v->parent;
    while (p != NULL && y == p->right)
    {
      y = p;
      p = p->parent;
    }
    return p;
  }
}

int delete_node(node *v, int k)
{
  node *w = search_node(v, k);
  if (isExternal(w))
    return -1;

  int deleted_key = w->key;
  node *z = w->left;
  if (!isExternal(z))
    z = w->right;
  if (isExternal(z))
    reduceExternal(z);
  else
  {
    node *y = inOrderSuccessor(w);
    z = y->left;
    w->key = y->key;
    reduceExternal(z);
  }
  return deleted_key;
}

void print_tree(node *v)
{
  if (isExternal(v))
    return;
  printf(" %d", v->key);
  print_tree(v->left);
  print_tree(v->right);
}

int main()
{
  char cmd;
  int key;

  T.root = create_node(0, NULL);

  while (1)
  {
    scanf(" %c", &cmd);
    switch (cmd)
    {
    case 'i':
      {
        scanf("%d", &key);
        insert_node(T.root, key);
        break;
      }
      break;
    case 'd':
      {
        scanf("%d", &key);
        int deleted_key = delete_node(T.root, key);
        if (deleted_key == -1)
          printf("X\n");
        else
          printf("%d\n", deleted_key);
        break;
      }
    case 's':
      {
        scanf("%d", &key);
        node *w = search_node(T.root, key);
        if (isExternal(w))
          printf("X\n");
        else
          printf("%d\n", w->key);
        break;
      }
    case 'p':
      {
        print_tree(T.root);
        printf("\n");
        break;
      }
    case 'q':
      {
        return 0;
      }
    default:
      {
        printf("Invalid command\n");
        break;
      }
    }
  }

  return 0;
}