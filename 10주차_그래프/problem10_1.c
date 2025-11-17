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
  Vertex vertices[n_vertices]; //array
  Edge *edges;   //linked list
} Graph;

Graph graph;

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int opposite(int vName, Edge e) //return "name of the opposite vertex"
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
  for (int i = 0;i < n_vertices;i++)
  {
    if (graph.vertices[i].name == vName)
      return i;
  }
  return -1;
}

void initGraph()
{
  //vertices & adjacency list
  for (int i = 0;i < n_vertices;i++)
  {
    graph.vertices[i].name = i + 1;
    graph.vertices[i].adjList = (AdjListNode *)malloc(sizeof(AdjListNode)); //header
    *(graph.vertices[i].adjList) = (AdjListNode) { NULL, NULL };
  }
  //edges
  graph.edges = (Edge *)malloc(sizeof(Edge)); //header
  *(graph.edges) = (Edge) { 0, 0, 0, NULL };
}

void insertAdjNode(Edge *newEdge)
{
  AdjListNode *cur = NULL;
  int v1 = newEdge->v1;
  int v2 = newEdge->v2;

  if (v1 == v2)
  {
    AdjListNode *cur = NULL;
    for (int i = 0;i < n_vertices;i++)
    {
      if (graph.vertices[i].name == newEdge->v1)
      {
        cur = graph.vertices[i].adjList;
        while (cur->next != NULL && opposite(graph.vertices[i].name, *(cur->next->edge)) < v2) //keep sorted order
          cur = cur->next;

        AdjListNode *newAdjNode = (AdjListNode *)malloc(sizeof(AdjListNode));
        *(newAdjNode) = (AdjListNode) { newEdge, cur->next };
        cur->next = newAdjNode;
      }
    }
  }
  else
  {
    for (int i = 0;i < n_vertices;i++)
    {
      //insert for v1 adjList
      if (graph.vertices[i].name == v1)
      {
        cur = graph.vertices[i].adjList;
        while (cur->next != NULL && opposite(graph.vertices[i].name, *(cur->next->edge)) < v2) //keep sorted order
          cur = cur->next;

        AdjListNode *newAdjNode = (AdjListNode *)malloc(sizeof(AdjListNode));
        *(newAdjNode) = (AdjListNode) { newEdge, cur->next };
        cur->next = newAdjNode;
      }
      //insert for v2 adjList
      if (graph.vertices[i].name == v2)
      {
        cur = graph.vertices[i].adjList;
        while (cur->next != NULL && opposite(graph.vertices[i].name, *(cur->next->edge)) < v1) //keep sorted order
          cur = cur->next;

        AdjListNode *newAdjNode = (AdjListNode *)malloc(sizeof(AdjListNode));
        *(newAdjNode) = (AdjListNode) { newEdge, cur->next };
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
  insertAdjNode(newEdge);
}

void deleteAdjNode(Edge *edgeToDelete)
{
  int v1 = edgeToDelete->v1;
  int v2 = edgeToDelete->v2;

  if (v1 == v2)
  {
    for (int i = 0;i < n_vertices;i++)
    {
      if (graph.vertices[i].name == v1)
      {
        AdjListNode *cur = graph.vertices[i].adjList;
        while (cur->next->edge->v1 != v1)
          cur = cur->next;

        AdjListNode *deleted = cur->next;
        cur->next = deleted->next;
        free(deleted);
        break;
      }
    }
  }
  else
  {
    int found1 = false;
    int found2 = false;
    for (int i = 0;i < n_vertices;i++)
    {
      if (graph.vertices[i].name == v1)
      {
        AdjListNode *cur = graph.vertices[i].adjList;
        while (cur->next->edge->v2 != v2)
          cur = cur->next;

        AdjListNode *deleted = cur->next;
        cur->next = deleted->next;
        free(deleted);
        found1 = true;
      }
      if (graph.vertices[i].name == edgeToDelete->v2)
      {
        AdjListNode *cur = graph.vertices[i].adjList;
        while (cur->next->edge->v1 != v1)
          cur = cur->next;

        AdjListNode *deleted = cur->next;
        cur->next = deleted->next;
        free(deleted);
        found2 = true;
      }
      if (found1 && found2)
        break;
    }
  }
}

void modifyEdge(Edge *e, int newWeight)
{
  e->w = newWeight;
}

void deleteEdge(Edge *prevEdge)
{
  Edge *edgeToDelete = prevEdge->next;
  int v1 = edgeToDelete->v1;
  int v2 = edgeToDelete->v2;

  //update Adjacency List
  deleteAdjNode(edgeToDelete);

  //delete Edge
  prevEdge->next = edgeToDelete->next;
  free(edgeToDelete);
}

void printAdjList(int vIndex)
{
  AdjListNode *curAdjEdge = graph.vertices[vIndex].adjList->next;
  while (curAdjEdge != NULL)
  {
    int op = opposite(graph.vertices[vIndex].name, *(curAdjEdge->edge));
    int opIndex = findVertexIdx(op);
    printf(" %d %d", graph.vertices[opIndex].name, curAdjEdge->edge->w);
    curAdjEdge = curAdjEdge->next;
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

  //deallocate Adjacency List
  for (int i = 0;i < n_vertices;i++)
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