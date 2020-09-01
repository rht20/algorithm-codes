#include<bits/stdc++.h>
using namespace std;

#define MXN 105
#define INF 1000000000000000LL
#define LL  long long int

LL dist[MXN][MXN];
int path[MXN][MXN];
int n, m;

void floyd_warshall()
{
    for(int k=1; k<=n; k++) /// select mid point
    {
        for(int i=1; i<=n; i++) /// select start point
        {
            for(int j=1; j<=n; j++) /// select end point
            {
                if((dist[i][k] + dist[k][j]) < dist[i][j])  /// update if distance from i->j is higher then distance from (i->k + k->j)
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];    /// path[i][j] represents next vertex if any mid point exists to go from i->j
                }
            }
        }
    }
}

void print_shortest_path(int x, int y)
{
    while(1)
    {
        printf(" %d", x);
        if(x == y)  break;
        x = path[x][y];
    }
    puts("");
}

void clr()
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i == j)
            {
                dist[i][j] = 0;
                path[i][j] = i;
            }
            else
            {
                dist[i][j] = INF;
                path[i][j] = -1;
            }
        }
    }
}

int main()
{
    int x, y, w;

    scanf("%d %d", &n, &m); /// number of nodes and edges
    clr();
    for(int i=0; i<m; i++)  /// edges
    {
        scanf("%d %d %d", &x, &y, &w);
        dist[x][y] = w;
        path[x][y] = y;
    }

    floyd_warshall();

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(dist[i][j] == INF)   printf("%d is not reachable from %d\n", j, i);
            else
            {
                printf("Shortest path from %d to %d => distance: %d, path:", i, j, dist[i][j]);
                print_shortest_path(i, j);
            }
        }
    }
    return 0;
}

/*
4 7

1 2 3
1 4 7
2 1 8
2 3 2
3 1 5
3 4 1
4 1 2
*/
