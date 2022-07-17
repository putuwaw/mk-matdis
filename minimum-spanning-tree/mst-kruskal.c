#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int v, edge, totalEdge, totalVertex;

void dfs(int num, int (*adjmtxRes)[v], bool *isVisited)
{
    int i, j;
    if (!isVisited[num])
    {
        totalVertex++;
        for (j = (num + 1); j < v; j++) // count edge in half of adj matrix
        {
            if (adjmtxRes[num][j] != 0)
            {
                totalEdge++;
            }
        }
        isVisited[num] = true; // vertex has visited
        for (i = 0; i < v; i++)
        {
            if (adjmtxRes[num][i] != 0 && !isVisited[i]) // dfs the adj if not visited yet
            {
                dfs(i, adjmtxRes, isVisited);
            }
        }
    }
}

bool isAnyCycle(int (*adjmtxRes)[v])
{
    int i, j, k;
    bool isVisited[v]; // to check the vertex has been visited
    memset(isVisited, 0, sizeof(isVisited));
    for (i = 0; i < (v - 1); i++)
    {
        for (j = (i + 1); j < v; j++)
        {
            if (adjmtxRes[i][j] != 0 && !isVisited[i]) // vertex is exist
            {
                totalEdge = 0;
                totalVertex = 0;
                dfs(i, adjmtxRes, isVisited); // dfs from that vertex
                if (totalEdge >= totalVertex) // no cycle if edge = vertex-1
                {
                    return true;
                }
            }
        }
    }
    return false;
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
        st--;
        nd--;
        adjmtx[st][nd] = wt;
        adjmtx[nd][st] = wt;
    }
    int minWeight, saveI, saveJ;
    int countEdge = 0;
    while (countEdge < (v - 1))
    {
        minWeight = 9999;
        // find the edge with minimum value
        for (i = 0; i < (v - 1); i++)
        {
            for (j = (i + 1); j < v; j++)
            {
                if (adjmtx[i][j] == 0)
                {
                    continue;
                }
                else if (adjmtx[i][j] < minWeight)
                { // next minimum
                    minWeight = adjmtx[i][j];
                    saveI = i;
                    saveJ = j;
                }
            }
        }
        // take to result mtx
        adjmtxRes[saveI][saveJ] = adjmtx[saveI][saveJ];
        adjmtxRes[saveJ][saveI] = adjmtx[saveI][saveJ];
        printf("Cek vertex %d dan %d dengan berat %d", saveI + 1, saveJ + 1, adjmtxRes[saveI][saveJ]);
        // check result mtx
        if (isAnyCycle(adjmtxRes)) // found cycle
        {
            // cancel add
            adjmtxRes[saveI][saveJ] = 0;
            adjmtxRes[saveJ][saveI] = 0;
            printf(" [Ditemukan cycle!]\n");
        }
        else // not found
        {
            printf("[Tidak ditemukan cycle]\n");
            countEdge++; // inc edge
        }
        // delete adjmtx
        adjmtx[saveI][saveJ] = 0;
        adjmtx[saveJ][saveI] = 0;
    }
    // result
    printf("Matriks hasil:\n");
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
