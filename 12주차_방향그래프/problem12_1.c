#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CONSTANTS
#define MAX_VERTICES 100
#define true 1
#define false 0
#define bool int

// DATA STRUCTURE
#define QUEUE

// SWITCHES
#define ADJLIST
//#define ADJMATRIX

#ifdef QUEUE
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

void enQueue(Queue *Q, int v)
{
  if (isFull(Q))
    return;
  Q->rear = (Q->rear + 1) % Q->size;
  Q->arr[Q->rear] = v;
}

int deQueue(Queue *Q)
{
  if (isEmpty(Q))
    return -1;

  int save = Q->arr[Q->front];
  Q->front = (Q->front + 1) % Q->size;
  return save;
}

void dallocQueue(Queue *Q)
{
  free(Q->arr);
}
#endif //QUEUE

#ifdef ADJLIST
//structs
typedef struct _AdjListNode
{
  int dest;
  struct _AdjListNode *next;
} AdjListNode;

typedef struct _Vertex_
{
  char name;
  AdjListNode *adjList;
} Vertex;

typedef struct _Graph_
{
  Vertex vertices[100];
  int n_vertices;
} Graph;

// global variables
Graph G;
int T[MAX_VERTICES];

//functions
void initGraph()
{
  G.n_vertices = 0;
}

void appendVertex(char v)
{
  // assign name
  G.vertices[G.n_vertices].name = v;
  // create header
  G.vertices[G.n_vertices].adjList = (AdjListNode *)malloc(sizeof(AdjListNode));
  *(G.vertices[G.n_vertices].adjList) = (AdjListNode) { -1, NULL };
  G.n_vertices++;
}

void appendEdge(char v1, char v2)
{
  int v1Index = -1, v2Index = -1;
  for (int i = 0; i < G.n_vertices; i++)
  {
    if (G.vertices[i].name == v1)
      v1Index = i;
    if (G.vertices[i].name == v2)
      v2Index = i;
    if (v1Index != -1 && v2Index != -1)
      break;
  }

  if (v1Index == -1 || v2Index == -1)
  {
    printf("appendEdge()::invalid vertex input\n");
    return;
  }

  AdjListNode *h = G.vertices[v1Index].adjList;
  AdjListNode *new = (AdjListNode *)malloc(sizeof(AdjListNode));
  *(new) = (AdjListNode) { v2Index, h->next };
  h->next = new;
}

int inDegree(int vIndex)
{
  int count = 0;
  for (int i = 0; i < G.n_vertices; i++)
  {
    AdjListNode *cur = G.vertices[i].adjList->next; // pass header
    while (cur != NULL)
    {
      if (cur->dest == vIndex)
        count++;
      cur = cur->next;
    }
  }
  return count;
}

bool topologicalSort()
{
  Queue Q;
  initQueue(&Q, G.n_vertices);

  int in[MAX_VERTICES];
  for (int i = 0;i < G.n_vertices;i++)
  {
    in[i] = inDegree(i);
    if (in[i] == 0)
      enQueue(&Q, i);
  }

  int t = 0;
  while (!isEmpty(&Q))
  {
    int vIdx = deQueue(&Q);
    T[t] = vIdx;
    t++;
    AdjListNode *cur = G.vertices[vIdx].adjList->next;
    while (cur != NULL)
    {
      int opIdx = cur->dest;
      in[opIdx]--;
      if (in[opIdx] == 0)
        enQueue(&Q, opIdx);
      cur = cur->next;
    }
  }
  dallocQueue(&Q);

  if (t < G.n_vertices)
    return 0;
  else
    return 1;
}

void rTopologicalSort_DFS(int visited[], int *t, int vIdx)
{
  visited[vIdx] = true;

  AdjListNode *cur = G.vertices[vIdx].adjList->next;
  while (cur != NULL)
  {
    int opIdx = cur->dest;
    if (visited[opIdx] == false)
      rTopologicalSort_DFS(visited, t, opIdx);
    cur = cur->next;
  }
  T[*t] = vIdx;
  (*t)--;
}

bool topologicalSort_DFS()
{
  int visited[MAX_VERTICES];
  memset(visited, 0, sizeof(visited));

  int t = G.n_vertices - 1;
  for (int i = 0;i < G.n_vertices;i++)
  {
    if (visited[i] == 0)
      rTopologicalSort_DFS(visited, &t, i);
  }

  if (t < 0)
    return true;
  else
    return false;
}
#endif // ADJLIST

#ifdef ADJMATRIX
typedef struct _Graph_
{
  char vertices[MAX_VERTICES];       //name of vertices
  int n_vertices;                    //number of vertices
  int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

//global variables
Graph G;
int T[MAX_VERTICES];

void initGraph()
{
  memset(G.vertices, '\0', MAX_VERTICES);
  G.n_vertices = 0;
  memset(G.adjMatrix, 0, sizeof(G.adjMatrix));
}

void appendVertex(char v)
{
  G.vertices[G.n_vertices] = v;
  G.n_vertices++;
}

int appendEdge(char v1, char v2) // v1 -> v2
{
  int v1Index = -1, v2Index = -1;
  for (int i = 0; i < G.n_vertices; i++)
  {
    if (G.vertices[i] == v1)
      v1Index = i;
    if (G.vertices[i] == v2)
      v2Index = i;
    if (v1Index != -1 && v2Index != -1)
      break;
  }

  if (v1Index == -1 || v2Index == -1)
  {
    printf("appendEdge()::invalid vertex input\n");
    return -1;
  }

  G.adjMatrix[v1Index][v2Index] = 1;
  return 0;
}

int findVertexIdx(char v)
{
  for (int i = 0; i < G.n_vertices; i++)
  {
    if (G.vertices[i] == v)
      return i;
  }
  return -1;
}

int inDegree(int vIndex)
{
  int count = 0;
  for (int i = 0; i < G.n_vertices; i++)
  {
    if (G.adjMatrix[i][vIndex] == 1)
      count++;
  }
  return count;
}

int topologicalSort()
{
  Queue Q;
  initQueue(&Q, G.n_vertices);

  int in[MAX_VERTICES];
  for (int i = 0;i < G.n_vertices;i++)
  {
    in[i] = inDegree(i);
    if (in[i] == 0)
      enQueue(&Q, i);
  }
  int t = 0;
  while (!isEmpty(&Q))
  {
    int u = deQueue(&Q);
    T[t] = u;
    t++;
    for (int i = 0; i < G.n_vertices; i++)
    {
      if (G.adjMatrix[u][i] == 1) //connected
      {
        in[i]--;
        if (in[i] == 0)
          enQueue(&Q, i);
      }
    }
  }
  dallocQueue(&Q);

  if (t < G.n_vertices)
    return 0;
  else
    return 1;
}

void printVertices()
{
  for (int i = 0; i < G.n_vertices; i++)
  {
    printf("%c ", G.vertices[i]);
  }
  printf("\n");
}

void printAdjMatrix()
{
  for (int i = 0; i < G.n_vertices; i++)
  {
    for (int j = 0; j < G.n_vertices; j++)
    {
      printf("%d ", G.adjMatrix[i][j]);
    }
    printf("\n");
  }
}
#endif //ADJMATRIX

int main()
{
  int n, m;
  scanf("%d", &n);
  initGraph();
  for (int i = 0; i < n; i++)
  {
    char v;
    scanf(" %c", &v);
    appendVertex(v);
    //printVertices();
  }

  scanf("%d", &m);
  for (int i = 0; i < m; i++)
  {
    char v1, v2;
    scanf(" %c %c", &v1, &v2);
    appendEdge(v1, v2);
    //printAdjMatrix();
  }

  //int acyclic = topologicalSort();
  int acyclic = topologicalSort_DFS(); // DFS버전으로는 방향사이클 여부 판단 불가!!!

  if (acyclic)
  {
    for (int i = 0;i < G.n_vertices;i++)
      printf("%c ", G.vertices[T[i]].name);
    printf("\n");
  }
  else
  {
    printf("0\n");
  }

  return 0;
}