#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int v, edge;

bool nextVertex(int i, int (*adjmtx)[v], int *path, int pos)
{
  // must be adjacent to previous vertex
  if (adjmtx[path[pos - 1]][i] == 0)
  {
    return false;
  }
  int j;
  // must be not have added to path
  for (j = 0; j < v; j++)
  {
    if (path[j] == i)
    {
      return false;
    }
  }
  return true;
}
bool hamiltonianCycle(int (*adjmtx)[v], int *path, int pos)
{
  if (pos == v)
  {
    // check if there is edge from last vertex to first vertex
    if (adjmtx[path[pos - 1]][path[0]] == 0)
    {
      return false;
    }
    return true;
  }
  else
  {
    int i;
    for (i = 1; i < v; i++)
    {
      if (nextVertex(i, adjmtx, path, pos))
      {
        path[pos] = i;
        if (hamiltonianCycle(adjmtx, path, pos + 1))
        {
          return true;
        }
        else
        {
          path[pos] = -1;
        }
      }
    }
  }
  return false;
}
void doHamiltonianCycle(int (*adjmtx)[v])
{
  int path[v];
  memset(path, -1, sizeof(path));
  // start from vertex 0
  path[0] = 0;
  if (hamiltonianCycle(adjmtx, path, 1) == false)
  {
    printf("Tidak ada Hamiltonian Cycle\n");
  }
  else
  {
    printf("Ada Hamiltonian Cycle\n");
    int i;
    for (i = 0; i < v; i++)
    {
      printf("%d -> ", path[i]);
    }
    printf("%d\n", path[0]);
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
  doHamiltonianCycle(adjmtx);
  return 0;
}
