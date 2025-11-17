#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct _node_
{
  int key;
  int height;
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

node *create_node(int key, int height, node *parent)
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

int updateHeight(node *z)
{
  int h = max(z->left->height, z->right->height) + 1;
  if (h != z->height)
  {
    z->height = h;
    return 1;
  }
  else
    return 0;
}

int isBalanced(node *z)
{
  int diff = z->left->height - z->right->height;
  return (diff >= -1 && diff <= 1);
}

void expandExternal(node *v)
{
  v->left = create_node(-1, 0, v);
  v->right = create_node(-1, 0, v);
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

node *reduceExternal(node *z)
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
  return zs;
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

node *restructure(node *x, node *y, node *z)
{
  node *a, *b, *c;
  node *T0, *T1, *T2, *T3;
  if (z->key < y->key && y->key < x->key)
  {
    /*
        z                         y
       / \                      /   \
      T0   y     -->           z     x
          / \                 / \   / \
         T1  x               T0 T1 T2 T3
            / \
           T2 T3
    */
    a = z; b = y; c = x;
    T0 = z->left; T1 = y->left; T2 = x->left; T3 = x->right;
  }
  else if (x->key < y->key && y->key < z->key)
  {
    /*
           z                        y
          / \                     /   \
         y   T3    -->           x     z
        / \                     / \   / \
       x  T2                   T0 T1 T2 T3
      / \
     T0 T1
    */
    a = x; b = y; c = z;
    T0 = x->left; T1 = x->right; T2 = y->right; T3 = z->right;
  }
  else if (z->key < x->key && x->key < y->key)
  {
    /*
         z                         x
       /  \                      /   \
      T0   y     -->            z     y
          / \                  / \   / \
         x  T3                T0 T1 T2 T3
        / \
       T1 T2
    */
    a = z; b = x; c = y;
    T0 = z->left; T1 = x->left; T2 = x->right; T3 = y->right;
  }
  else
  {
    /*
         z                          x
        /  \                      /   \
       y   T3     -->            y     z
      / \                       / \   / \
     T0  x                     T0 T1 T2 T3
        / \
       T1 T2
    */
    a = y; b = x; c = z;
    T0 = y->left; T1 = x->left; T2 = x->right; T3 = z->right;
  }

  if (z->parent == NULL)
  {
    T.root = b;
    b->parent = NULL;
  }
  else if (z->parent->left == z)
  {
    z->parent->left = b;
    b->parent = z->parent;
  }
  else
  {
    z->parent->right = b;
    b->parent = z->parent;
  }

  a->left = T0; a->right = T1;
  T0->parent = a; T1->parent = a;
  updateHeight(a);

  c->left = T2; c->right = T3;
  T2->parent = c; T3->parent = c;
  updateHeight(c);

  b->left = a; b->right = c;
  a->parent = b; c->parent = b;
  updateHeight(b);

  return b;
}

//w is leaf node
void searchAndFixAfterInsertion(node *w)
{
  //Update heights and search for imbalance
  w->left->height = 0;
  w->right->height = 0;
  w->height = 1;
  if (w->parent == NULL)
    return;

  node *z = w->parent;
  while (updateHeight(z) && isBalanced(z))
  {
    if (z->parent == NULL)
      return;
    z = z->parent;
  }
  if (isBalanced(z))
    return;

  //Fix imbalance
  node *y, *x;
  if (z->left->height > z->right->height)
    y = z->left;
  else
    y = z->right;
  if (y->left->height > y->right->height)
    x = y->left;
  else
    x = y->right;
  restructure(x, y, z);

  return;
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
    searchAndFixAfterInsertion(w);
  }
}

void searchAndFixAfterRemoval(node *z)
{
  while (updateHeight(z) && isBalanced(z))
  {
    if (z->parent == NULL)
      return;
    z = z->parent;
  }
  if (isBalanced(z))
    return;

  node *y, *x;
  if (z->left->height >= z->right->height)
    y = z->left;
  else
    y = z->right;

  if (y->left->height >= y->right->height)
    x = y->left;
  else
    x = y->right;

  node *b = restructure(x, y, z);
  if (b->parent == NULL)
    return;
  searchAndFixAfterRemoval(b->parent);
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
  node *zs;
  if (!isExternal(z))
    z = w->right;
  if (isExternal(z))
    zs = reduceExternal(z);
  else
  {
    node *y = inOrderSuccessor(w);
    w->key = y->key;
    z = y->left;
    zs = reduceExternal(z);
  }
  searchAndFixAfterRemoval(zs->parent);
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

void freeTree(node *w)
{
  if (isExternal(w))
  {
    free(w);
    return;
  }
  freeTree(w->left);
  freeTree(w->right);
  free(w);
}

int main()
{
  char cmd;
  int key;

  T.root = create_node(-1, 0, NULL);

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
        freeTree(T.root);
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