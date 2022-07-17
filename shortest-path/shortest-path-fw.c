#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int v, edge;

void doFloydWarshall(int (*adjmtx)[v])
{
	int i, j, k;
	for (i = 0; i < v; i++)
	{
		for (j = 0; j < v; j++)
		{
			for (k = 0; k < v; k++)
			{
				if (adjmtx[j][i] + adjmtx[i][k] < adjmtx[j][k])
				{
					adjmtx[j][k] = adjmtx[j][i] + adjmtx[i][k];
				}
			}
		}
	}
	printf("Matriks hasil:\n");
	for (i = 0; i < v; i++)
	{
		for (j = 0; j < v; j++)
		{
			printf("%-4d ", adjmtx[i][j]);
		}
		printf("\n");
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
		st--;
		nd--;
		adjmtx[st][nd] = wt;
		adjmtx[nd][st] = wt; // remove this line if directed graph
	}
	doFloydWarshall(adjmtx);
}
