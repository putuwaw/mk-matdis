#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int v, edge;

void doMSTPrims(int (*adjmtx)[v], int (*adjmtxRes)[v])
{
    int totalEdge = 0;
    int possibleVertex[v];
    bool isVisited[v];
    memset(isVisited, 0, sizeof(isVisited));
    memset(possibleVertex, 0, sizeof(possibleVertex));
    // pick first node
    isVisited[0] = true;      // has visited
    possibleVertex[0] = true; // search adj of this node
    while (totalEdge < (v - 1))
    {
        int i, j, minimumEdge = 9999;
        int saveI, saveJ;
        // check all possible vertex
        for (i = 0; i < v; i++)
        {
            if (possibleVertex[i] == true)
            {
                for (j = 0; j < v; j++) // find adj of that vertex
                {
                    if (adjmtx[i][j] != 0 && !isVisited[j])
                    {
                        // find the minimum
                        if (adjmtx[i][j] < minimumEdge)
                        {
                            minimumEdge = adjmtx[i][j];
                            saveI = i;
                            saveJ = j;
                        }
                    }
                }
            }
        }
        // to adjmtxRes
        adjmtxRes[saveI][saveJ] = adjmtx[saveI][saveJ];
        adjmtxRes[saveJ][saveI] = adjmtx[saveJ][saveI];
        possibleVertex[saveJ] = true;
        isVisited[saveJ] = true;
        totalEdge++;
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
    int i, j;
    for (i = 0; i < edge; i++)
    {
        int st, nd, wt;
        scanf("%d %d %d", &st, &nd, &wt);
        st--; // in case vertex start from 0..
        nd--; // ..remove if vertex start from 0
        adjmtx[st][nd] = wt;
        adjmtx[nd][st] = wt;
    }
    doMSTPrims(adjmtx, adjmtxRes);
    // output
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            printf("%d ", adjmtxRes[i][j]);
        }
        printf("\n");
    }
    return 0;
}
