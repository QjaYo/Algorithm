#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define RECURSIVE_DFS
//#define ITERATIVE_DFS

//structs

typedef struct _Edge_
{
  int v1;
  int v2;
  struct _Edge_ *next;
} Edge;

typedef struct _AdjListNode_
{
  Edge *edge;
  struct _AdjListNode_ *next;
} AdjListNode;

typedef struct _Vertex_
{
  int name;
  AdjListNode *adjList; //header
} Vertex;

typedef struct _Graph_
{
  Vertex *vertices;
  Edge *edges;
} Graph;

//globals

Graph graph;
int n, m, s;

//functions

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int opposite(int vName, Edge e) //return "name" of the opposite vertex
{
  if (e.v1 == vName)
    return e.v2;
  else if (e.v2 == vName)
    return e.v1;
  else
    return -1; //error
}

Edge *findPrevEdge(int vName1, int vName2)
{
  Edge *curEdge = graph.edges;
  while (curEdge->next != NULL)
  {
    if ((curEdge->next->v1 == vName1 && curEdge->next->v2 == vName2))
      return curEdge;
    curEdge = curEdge->next;
  }
  return NULL;
}

int findVertexIdx(int vName)
{
  for (int i = 0;i < n;i++)
  {
    if (graph.vertices[i].name == vName)
      return i;
  }
  return -1;
}

void initGraph()
{
  //vertices array & adjacency list
  graph.vertices = (Vertex *)malloc(sizeof(Vertex) * n);

  //edges linked list
  graph.edges = (Edge *)malloc(sizeof(Edge)); //header
  *(graph.edges) = (Edge) { 0, 0, NULL };
}

void deallocateGraph()
{
  //free adjacency list & vertices array
  for (int i = 0;i < n;i++)
  {
    AdjListNode *cur = graph.vertices[i].adjList;
    AdjListNode *next = NULL;
    while (cur != NULL)
    {
      next = cur->next;
      free(cur);
      cur = next;
    }
  }
  free(graph.vertices);

  //free edge list
  Edge *curEdge = graph.edges;
  Edge *nextEdge = NULL;
  while (curEdge != NULL)
  {
    nextEdge = curEdge->next;
    free(curEdge);
    curEdge = nextEdge;
  }
}

void insertAdjListNode(Edge *e)
{
  AdjListNode *cur = NULL;
  int v1 = e->v1;
  int v2 = e->v2;

  if (v1 == v2) //self-loop
  {
    for (int i = 0;i < n;i++)
    {
      if (graph.vertices[i].name == v1)
      {
        cur = graph.vertices[i].adjList;
        while (cur->next != NULL && opposite(graph.vertices[i].name, *(cur->next->edge)) < v2) //keep sorted order
          cur = cur->next;

        AdjListNode *newAdjNode = (AdjListNode *)malloc(sizeof(AdjListNode));
        *(newAdjNode) = (AdjListNode) { e, cur->next };
        cur->next = newAdjNode;
      }
    }
  }
  else
  {
    for (int i = 0;i < n;i++)
    {
      //insert for v1 adjList
      if (graph.vertices[i].name == v1)
      {
        cur = graph.vertices[i].adjList;
        while (cur->next != NULL && opposite(graph.vertices[i].name, *(cur->next->edge)) < v2) //keep sorted order
          cur = cur->next;

        AdjListNode *newAdjNode = (AdjListNode *)malloc(sizeof(AdjListNode));
        *(newAdjNode) = (AdjListNode) { e, cur->next };
        cur->next = newAdjNode;
      }
      //insert for v2 adjList
      if (graph.vertices[i].name == v2)
      {
        cur = graph.vertices[i].adjList;
        while (cur->next != NULL && opposite(graph.vertices[i].name, *(cur->next->edge)) < v1) //keep sorted order
          cur = cur->next;

        AdjListNode *newAdjNode = (AdjListNode *)malloc(sizeof(AdjListNode));
        *(newAdjNode) = (AdjListNode) { e, cur->next };
        cur->next = newAdjNode;
      }
    }
  }
}

void createEdge(Edge e)
{
  //append edge at the end of edge list
  Edge *curEdge = graph.edges;
  while (curEdge->next != NULL)
    curEdge = curEdge->next;

  Edge *newEdge = (Edge *)malloc(sizeof(Edge));
  *(newEdge) = e;
  curEdge->next = newEdge;

  //update Adjacency List
  insertAdjListNode(newEdge);
}

#ifdef RECURSIVE_DFS
void rDFS(int vIndex, int *visited)
{
  visited[vIndex] = true;
  printf("%d\n", graph.vertices[vIndex].name);

  AdjListNode *cur = graph.vertices[vIndex].adjList;
  cur = cur->next; //skip header
  while (cur != NULL)
  {
    int op = opposite(graph.vertices[vIndex].name, *(cur->edge));
    int opIndex = findVertexIdx(op);
    if (!visited[opIndex])
      rDFS(opIndex, visited);
    cur = cur->next;
  }
}
void DFS(int s)
{
  int *visited = (int *)malloc(sizeof(int) * n);
  memset(visited, false, sizeof(int) * n);

  int sIndex = findVertexIdx(s);
  rDFS(sIndex, visited);

  free(visited);
}
#endif

#ifdef ITERATIVE_DFS
typedef struct _Stack_
{
  int top;
  int size;
  int *arr;
} Stack;

void initStack(Stack *S, int size)
{
  int *Sarr = (int *)malloc(sizeof(int) * size);
  *S = (Stack) { -1, size, Sarr };
}

void push(Stack *S, int top)
{
  S->arr[++(S->top)] = top;
}

int pop(Stack *S)
{
  return S->arr[(S->top)--];
}

int isEmpty(Stack *S)
{
  return S->top == -1;
}

int isFull(Stack *S)
{
  return S->top == S->size - 1;
}

void DFS(int s)
{
  int *visited = (int *)malloc(sizeof(int) * n);
  memset(visited, 0, sizeof(int) * n);

  Stack stack;
  initStack(&stack, n);

  int sIndex = findVertexIdx(s);
  push(&stack, sIndex);

  while (!isEmpty(&stack)) {
    int vIndex = pop(&stack);

    if (visited[vIndex])
      continue;

    visited[vIndex] = true;
    int v = graph.vertices[vIndex].name;
    printf("%d\n", v);

    //push adjacent vertices to stack in reverse order
    Stack temp;
    initStack(&temp, 3 * n);

    AdjListNode *cur = graph.vertices[vIndex].adjList;
    cur = cur->next; //skip header
    while (cur != NULL)
    {
      int op = opposite(v, *(cur->edge));
      int opIndex = findVertexIdx(op);
      if (!visited[opIndex])
        push(&temp, opIndex);
      cur = cur->next;
    }

    while (!isEmpty(&temp))
    {
      int opIndex = pop(&temp);
      if (!visited[opIndex])
        push(&stack, opIndex);
    }

    free(temp.arr);
  }

  free(stack.arr);
  free(visited);
}
#endif

void buildGraph()
{
  //vertices array & adjacency list
  for (int i = 0;i < n;i++)
  {
    graph.vertices[i].name = i + 1;
    graph.vertices[i].adjList = (AdjListNode *)malloc(sizeof(AdjListNode)); //header
    *(graph.vertices[i].adjList) = (AdjListNode) { NULL, NULL };
  }

  //edges linked list
  for (int i = 0;i < m;i++)
  {
    int v1, v2;
    scanf("%d %d", &v1, &v2);
    if (v1 > v2)
      swap(&v1, &v2);
    createEdge((Edge) { v1, v2, NULL });
  }
}

int main()
{
  scanf("%d %d %d", &n, &m, &s);

  initGraph();
  buildGraph();

  DFS(s);

  deallocateGraph();

  return 0;
}
