#include <stdio.h>
#include <stdlib.h>

#define n_vertices 6
#define true 1
#define false 0

typedef struct _Edge_
{
  int v1;
  int v2;
  int w;
  struct _Edge_ *next;
} Edge;

typedef struct _Vertex_
{
  int name;
} Vertex;

typedef struct _Graph_
{
  Vertex vertices[n_vertices];
  Edge *edges;
} Graph;

Edge *AdjMatrix[n_vertices][n_vertices];
Graph graph;

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int findVertexIdx(int vName)
{
  for (int i = 0;i < n_vertices;i++)
  {
    if (graph.vertices[i].name == vName)
      return i;
  }
  return -1;
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

void initGraph()
{
  //vertices & adjacency matrix
  for (int i = 0;i < n_vertices;i++)
    for (int j = 0;j < n_vertices;j++)
      AdjMatrix[i][j] = NULL;
  //edges
  graph.edges = (Edge *)malloc(sizeof(Edge)); //header
  *(graph.edges) = (Edge) { 0, 0, 0, NULL };
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
  AdjMatrix[v1Index][v2Index] = newEdge;
  AdjMatrix[v2Index][v1Index] = newEdge;
}

void modifyEdge(Edge *e, int newWeight)
{
  e->w = newWeight;
}

void deleteEdge(Edge *prevEdge)
{
  Edge *edgeToDelete = prevEdge->next;

  //update Adjacency Matrix
  int v1Index = findVertexIdx(edgeToDelete->v1);
  int v2Index = findVertexIdx(edgeToDelete->v2);
  AdjMatrix[v1Index][v2Index] = NULL;
  AdjMatrix[v2Index][v1Index] = NULL;

  //delete Edge
  prevEdge->next = edgeToDelete->next;
  free(edgeToDelete);
}

void printAdjList(int vIndex)
{
  for (int i = 0;i < n_vertices;i++)
  {
    if (AdjMatrix[vIndex][i] != NULL)
      printf(" %d %d", graph.vertices[i].name, AdjMatrix[vIndex][i]->w);
  }
  printf("\n");
}

void deallocateGraph()
{
  //deallocate Edges
  Edge *curEdge = graph.edges;
  Edge *nextEdge = NULL;
  while (curEdge != NULL)
  {
    nextEdge = curEdge->next;
    free(curEdge);
    curEdge = nextEdge;
  }
}

void buildGraph()
{
  //vertices
  for (int i = 0;i < n_vertices;i++)
    graph.vertices[i].name = i + 1;

  //edges
  createEdge((Edge) { 1, 2, 1, NULL });
  createEdge((Edge) { 1, 3, 1, NULL });
  createEdge((Edge) { 1, 4, 1, NULL });
  createEdge((Edge) { 1, 6, 2, NULL });
  createEdge((Edge) { 2, 3, 1, NULL });
  createEdge((Edge) { 3, 5, 4, NULL });
  createEdge((Edge) { 5, 5, 4, NULL });
  createEdge((Edge) { 5, 6, 3, NULL });
}

int main()
{
  initGraph();
  buildGraph();

  char cmd;
  while (1)
  {
    scanf(" %c", &cmd);
    switch (cmd)
    {
    case 'a':
      {
        int v;
        scanf("%d", &v);
        int vIndex = findVertexIdx(v);
        if (vIndex == -1)
          printf("-1\n");
        else
          printAdjList(vIndex);
        break;
      }
    case 'm':
      {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        if (a > b)
          swap(&a, &b);

        if (findVertexIdx(a) == -1 || findVertexIdx(b) == -1)
        {
          printf("-1\n");
          continue;
        }
        else
        {
          if (w != 0)
          {
            Edge *e = findPrevEdge(a, b);
            if (e != NULL) //edges exists
              modifyEdge(e->next, w);
            else //edges not exists
              createEdge((Edge) { a, b, w, NULL });
          }
          else // w == 0
          {
            Edge *e = findPrevEdge(a, b);
            if (e != NULL) //edges exists
            {
              deleteEdge(e);
            }
            else //edges not exists
              printf("-1\n");
          }
          break;
        }
      }
    case 'q':
      {
        deallocateGraph();
        return 0;
      }
    default:
      break;
    }
  }
  deallocateGraph();

  return 0;
}