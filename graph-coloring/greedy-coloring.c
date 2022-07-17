#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isColored(int *color, int v)
{
    int i;
    for (i = 0; i < v; i++)
    {
        if (color[i] == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int v;
    printf("Ketikkan jumlah vertex: ");
    scanf("%d", &v);
    int adjmtx[v][v], deg[v], vertex[v];
    int i, j;
    memset(deg, 0, sizeof(deg));
    for (i = 0; i < v; i++)
    {
        vertex[i] = i;
        for (j = 0; j < v; j++)
        {
            if (i != j)
            {
                printf("Hubungan vertex %d dan %d adalah: ", i + 1, j + 1);
                scanf("%d", &adjmtx[i][j]);
            }
            else
            {
                adjmtx[i][j] = 0;
            }
        }
    }
    printf("Matriks yang dihasilkan adalah: \n");
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            printf("%d ", adjmtx[i][j]);
        }
        printf("\n");
    }
    printf("Derajat dari setiap vertex adalah: \n");
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            deg[i] += adjmtx[i][j];
        }
        printf("Derajat vertex %d adalah %d\n", i + 1, deg[i]);
    }
    // sorting
    for (i = 0; i < v - 1; i++)
    {
        for (j = 0; j < v - i - 1; j++)
        {
            if (deg[j] < deg[j + 1])
            {
                int temp = deg[j];
                deg[j] = deg[j + 1];
                deg[j + 1] = temp;
                // do it to vertex
                temp = vertex[j];
                vertex[j] = vertex[j + 1];
                vertex[j + 1] = temp;
            }
        }
    }
    // after sorting
    for (i = 0; i < v; i++)
    {
        printf("Vertex ke %d memiliki derajat: %d\n", vertex[i] + 1, deg[i]);
    }
    int color[v], giveColor = 0, init = 0;
    memset(color, 0, sizeof(color));
    while (!isColored(color, v))
    {
        giveColor++; // need more color
        // give color to vertex w/ highest deg that not colored yet
        while (color[vertex[init]] != 0)
        {
            init++;
        }
        color[vertex[init]] = giveColor;
        // check to all vertex that possible to have same color
        for (i = 0; i < v; i++)
        {
            if (color[vertex[i]] == 0) // if is not colored
            {
                // check is that vertex adj with colored
                bool takeColor = true;
                for (j = 0; j < v; j++)
                {
                    if (adjmtx[vertex[i]][j] == 1) // if adj
                    {
                        if (color[j] == giveColor) // same color, can't give color
                        {
                            takeColor = false;
                        }
                    }
                }
                if (takeColor == true)
                {
                    color[vertex[i]] = giveColor;
                }
            }
        }
    }
    // after coloring
    for (i = 0; i < v; i++)
    {
        printf("Vertex ke-%d memiliki warna: %d\n", i + 1, color[i]);
    }
    return 0;
}
