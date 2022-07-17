#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int v, edge;

void getShortestFromTarget(int target, int (*adjmtx)[v], int (*adjmtxRes)[v])
{
    int i;
    int getShortest[v];
    memset(getShortest, -1, sizeof(getShortest));
    bool isVisited[v];
    memset(isVisited, 0, sizeof(isVisited));
    bool repeat = true;
    int start = target;
    getShortest[start] = 0;
    while (repeat)
    {
        isVisited[start] = true;
        for (i = 0; i < v; i++)
        {
            if (adjmtx[start][i] != 0 && !isVisited[i])
            {
                if (start == target && getShortest[i] == -1)
                {
                    getShortest[i] = adjmtx[start][i];
                }
                else
                {
                    if (getShortest[i] == -1)
                    {
                        getShortest[i] = getShortest[start] + adjmtx[start][i];
                    }
                    else
                    {
                        if (getShortest[start] + adjmtx[start][i] < getShortest[i])
                        {
                            getShortest[i] = getShortest[start] + adjmtx[start][i];
                        }
                    }
                }
            }
        }
        int minimumVertex = -1;
        repeat = false;
        for (i = 0; i < v; i++)
        {
            if (!isVisited[i] && getShortest[i] != -1)
            {
                repeat = true;
                if (minimumVertex == -1)
                {
                    minimumVertex = getShortest[i];
                    start = i;
                }
                else
                {
                    if (getShortest[i] < minimumVertex)
                    {
                        minimumVertex = getShortest[i];
                        start = i;
                    }
                }
            }
        }
    }
    // print
    for (i = 0; i < v; i++)
    {
        printf("%d --> %d = %d\n", target + 1, i + 1, getShortest[i]);
    }
}

int main()
{
    printf("Masukkan jumlah vertex: ");
    scanf("%d", &v);
    int adjmtx[v][v], adjmtxRes[v][v];
    memset(adjmtx, 0, sizeof(adjmtx));
    memset(adjmtxRes, 0, sizeof(adjmtxRes));
    printf("Masukkan jumlah edge: ");
    scanf("%d", &edge);
    int i;
    for (i = 0; i < edge; i++)
    {
        int st, nd, wt;
        scanf("%d %d %d", &st, &nd, &wt);
        st--;
        nd--;
        adjmtx[st][nd] = wt;
        adjmtx[nd][st] = wt;
    }
    int target;
    printf("Pilih vertex awal: ");
    scanf("%d", &target);
    target--;
    getShortestFromTarget(target, adjmtx, adjmtxRes);
    return 0;
}