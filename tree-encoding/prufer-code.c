#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int v, edge;

void treeToPrufer(int (*adjmtx)[v])
{
  int deg[v], counter = 0;
  bool isSelected[v];
  memset(isSelected, 0, sizeof(isSelected));
  memset(deg, 0, sizeof(deg));
  while (counter < v - 2)
  {
    // find vertex w/ minimum degree
    memset(deg, 0, sizeof(deg));
    int i, j, saveDeg, minDeg = 999999;
    for (i = 0; i < v; i++)
    {
      for (j = 0; j < v; j++)
      {
        if (adjmtx[i][j] == 1)
        {
          deg[i]++;
        }
      }
      if (deg[i] < minDeg && !isSelected[i])
      {
        minDeg = deg[i];
        saveDeg = i;
      }
    }
    // remove that vertex
    for (j = 0; j < v; j++)
    {
      if (adjmtx[saveDeg][j] != 0)
      {
        printf("%d ", j + 1);
        adjmtx[saveDeg][j] = 0;
        adjmtx[j][saveDeg] = 0;
      }
    }
    isSelected[saveDeg] = true;
    counter++;
  }
}

int main()
{
  printf("Masukkan jumlah vertex: ");
  scanf("%d", &v);
  int adjmtx[v][v];
  memset(adjmtx, 0, sizeof(adjmtx));
  printf("Masukkan jumlah edge: ");
  scanf("%d", &edge);
  int i, j;
  for (i = 0; i < edge; i++)
  {
    int st, nd;
    scanf("%d %d", &st, &nd);
    st--; // in case vertex start from 1..
    nd--; // ..remove if vertex start from 0
    adjmtx[st][nd] = 1;
    adjmtx[nd][st] = 1;
  }
  treeToPrufer(adjmtx);
}