#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int v, edge;

void doBellmanFord(int (*adjmtx)[v])
{
  int i, j, k, start, dist[v];
  bool isNegativeCycle = false;
  printf("Masukkan titik awal: ");
  scanf("%d", &start);
  start--; // remove this if vertex start from 0
  for (i = 0; i < v; i++)
  {
    dist[i] = 999999;
  }
  dist[start] = 0;
  for (i = 0; i < (v - 1); i++)
  {
    for (j = 0; j < v; j++)
    {
      for (k = 0; k < v; k++)
      {
        if (adjmtx[j][k] != 0 && (adjmtx[j][k] + dist[j]) < dist[k])
        {
          dist[k] = adjmtx[j][k] + dist[j];
        }
      }
    }
  }
  for (i = 0; i < v; i++)
  {
    for (j = 0; j < v; j++)
    {
      if (adjmtx[i][j] != 0 && (adjmtx[i][j] + dist[i]) < dist[j])
      {
        isNegativeCycle = true;
      }
    }
  }
  if (isNegativeCycle)
  {
    printf("Graph mengandung negatif cycle\n");
  }
  else
  {
    printf("Graph tidak mengandung negatif cycle\n");
    for (i = 0; i < v; i++)
    {
      printf("Jarak terpendek dari %d ke %d: %d\n", start + 1, i + 1, dist[i]);
    }
  }
}

int main()
{
  printf("Masukkan jumlah vertex: ");
  scanf("%d", &v);
  int adjmtx[v][v], i, j;
  for (i = 0; i < v; i++)
  {
    for (j = 0; j < v; j++)
    {
      if (i == j)
      {
        adjmtx[i][j] = 0;
      }
      else
      {
        adjmtx[i][j] = 999999;
      }
    }
  }
  printf("Masukkan jumlah edge: ");
  scanf("%d", &edge);
  for (i = 0; i < edge; i++)
  {
    int st, nd, wt;
    scanf("%d %d %d", &st, &nd, &wt);
    st--; // remove this line if
    nd--; // ..vertex start from 0
    adjmtx[st][nd] = wt;
  }
  doBellmanFord(adjmtx);
}
