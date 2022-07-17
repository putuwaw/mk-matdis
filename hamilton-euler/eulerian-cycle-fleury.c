#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int v, edge;

int dfsCountVertices(int start, bool *isVisited, int (*adjmtx)[v])
{
  isVisited[start] = true;
  int count = 1, i;
  for (i = 0; i < v; i++)
  {
    if (adjmtx[start][i] == 1 & !isVisited[i])
    {
      count += dfsCountVertices(i, isVisited, adjmtx);
    }
  }
  return count;
}

bool isBridgeEdge(int start, int end, int (*adjmtx)[v])
{
  bool isVisited[v];
  int sumAfter, sumBefore;
  // count
  memset(isVisited, 0, sizeof(isVisited));
  sumBefore = dfsCountVertices(start, isVisited, adjmtx);
  // remove the edge and count again
  adjmtx[start][end] = 0;
  adjmtx[end][start] = 0;
  memset(isVisited, 0, sizeof(isVisited));
  sumAfter = dfsCountVertices(start, isVisited, adjmtx);
  // bring back the edge
  adjmtx[start][end] = 1;
  adjmtx[end][start] = 1;
  if (sumBefore != sumAfter)
  {
    // dif sum, so a bridge
    return true;
  }
  return false;
}

void eulerianFleury(int start, int (*adjmtx)[v])
{
  printf("%d", start);
  int adjVertex = 0, saveVertex, i;
  for (i = 0; i < v; i++)
  {
    if (adjmtx[start][i] == 1)
    {
      saveVertex = i;
      adjVertex++;
    }
  }
  // condition according to the number of adjacent vertices
  if (adjVertex == 0)
  {
    printf("\n");
  }
  else if (adjVertex == 1)
  {
    printf(" -> ");
    adjmtx[start][saveVertex] = 0;
    adjmtx[saveVertex][start] = 0;
    eulerianFleury(saveVertex, adjmtx);
  }
  else
  {
    printf(" -> ");
    // check for every adj of pos
    for (i = 0; i < v; i++)
    {
      // adj and not bridge
      if (adjmtx[start][i] == 1 && !isBridgeEdge(start, i, adjmtx))
      {
        adjmtx[start][i] = 0;
        adjmtx[i][start] = 0;
        eulerianFleury(i, adjmtx);
        break;
      }
    }
  }
}

void doEulerianFleury(int (*adjmtx)[v])
{
  int sumOddVertex = 0, saveOdd, degVertex, i, j;
  for (i = 0; i < v; i++)
  {
    degVertex = 0;
    for (j = 0; j < v; j++)
    {
      if (adjmtx[i][j] == 1)
      {
        degVertex++;
      }
    }
    if (degVertex % 2 == 1)
    {
      sumOddVertex++;
      saveOdd = i;
    }
  }
  // check with 3 possibilities:
  if (sumOddVertex == 0)
  {
    printf("Ditemukan eulerian cycle\n");
    eulerianFleury(0, adjmtx);
  }
  else if (sumOddVertex == 2)
  {
    printf("Ditemukan eulerian path:\n");
    eulerianFleury(saveOdd, adjmtx);
  }
  else
  {
    printf("Eulerian cycle atau eulerian path tidak ada\n");
  }
}

int main()
{
  printf("Masukkan jumlah vertex: ");
  scanf("%d", &v);
  int adjmtx[v][v], i, j;
  memset(adjmtx, 0, sizeof(adjmtx));
  printf("Masukkan jumlah edge: ");
  scanf("%d", &edge);
  for (i = 0; i < edge; i++)
  {
    int st, nd;
    scanf("%d %d", &st, &nd);
    // vertex start from 0, undirected
    adjmtx[st][nd] = 1;
    adjmtx[nd][st] = 1;
  }
  doEulerianFleury(adjmtx);
  return 0;
}