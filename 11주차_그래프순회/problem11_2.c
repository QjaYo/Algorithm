#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

//#define RECURSIVE_BFS
#define ITERATIVE_BFS

typedef struct _Edge_
{
  int v1;
  int v2;
  struct _Edge_ *next;
} Edge;

typedef struct _Vertex_
{
  int name;
} Vertex;

typedef struct _Graph_
{
  Vertex *vertices;
  Edge ***adjMatrix;
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
  //vertices & adjacency matrix
  graph.vertices = (Vertex *)malloc(sizeof(Vertex) * n);
  graph.adjMatrix = (Edge ***)malloc(sizeof(Edge **) * n);
  for (int i = 0; i < n; i++) {
    graph.adjMatrix[i] = (Edge **)malloc(sizeof(Edge *) * n);
  }

  for (int i = 0;i < n;i++)
    for (int j = 0;j < n;j++)
      graph.adjMatrix[i][j] = NULL;

  //edges
  graph.edges = (Edge *)malloc(sizeof(Edge)); //header
  *(graph.edges) = (Edge) { 0, 0, NULL };
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

  //update Adjacency Matrix
  int v1Index = findVertexIdx(e.v1);
  int v2Index = findVertexIdx(e.v2);
  graph.adjMatrix[v1Index][v2Index] = newEdge;
  graph.adjMatrix[v2Index][v1Index] = newEdge;
}

void deallocateGraph()
{
  //deallocate edges
  Edge *curEdge = graph.edges;
  Edge *nextEdge = NULL;
  while (curEdge != NULL)
  {
    nextEdge = curEdge->next;
    free(curEdge);
    curEdge = nextEdge;
  }

  //deallocate adjacency matrix
  for (int i = 0; i < n; i++) {
    free(graph.adjMatrix[i]);
  }
  free(graph.adjMatrix);

  //deallocate vertices array
  free(graph.vertices);
}

#ifdef RECURSIVE_BFS
//not good...
#endif

#ifdef ITERATIVE_BFS
typedef struct _Queue_
{
  int front;
  int rear;
  int size;
  int *arr;
} Queue;

void initQueue(Queue *Q, int size)
{
  int *Qarr = (int *)malloc(sizeof(int) * size);
  *Q = (Queue) { 0, -1, size, Qarr };
}

int isEmpty(Queue *Q)
{
  return Q->front == (Q->rear + 1) % Q->size;
}

int isFull(Queue *Q)
{
  return Q->front == (Q->rear + 2) % Q->size;
}

void push(Queue *Q, int v)
{
  if (isFull(Q))
    return;
  Q->rear = (Q->rear + 1) % Q->size;
  Q->arr[Q->rear] = v;
}

int pop(Queue *Q)
{
  if (isEmpty(Q))
    return -1;

  int save = Q->arr[Q->front];
  Q->front = (Q->front + 1) % Q->size;
  return save;
}

void BFS(int s)
{
  int *visited = (int *)malloc(sizeof(int) * n);
  memset(visited, false, sizeof(int) * n);

  Queue Q;
  initQueue(&Q, n);

  int sIndex = findVertexIdx(s);
  push(&Q, sIndex);
  visited[sIndex] = true;

  while (!isEmpty(&Q))
  {
    int vIndex = pop(&Q);
    int v = graph.vertices[vIndex].name;
    printf("%d\n", v);

    for (int i = 0;i < n;i++)
    {
      if (graph.adjMatrix[vIndex][i] != NULL)
      {
        int opIndex = i;
        if (!visited[opIndex])
        {
          push(&Q, opIndex);
          visited[opIndex] = true;
        }
      }
    }
  }

  free(Q.arr);

  free(visited);
}
#endif

void buildGraph()
{
  //vertices array & adjacency list
  for (int i = 0;i < n;i++)
  {
    graph.vertices[i].name = i + 1;
  }

  //edges linked list & adjacency matrix
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

  BFS(s);

  deallocateGraph();

  return 0;
}