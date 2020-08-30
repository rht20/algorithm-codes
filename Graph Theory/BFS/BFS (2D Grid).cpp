#include<bits/stdc++.h>
using namespace std;

#define MXN 1005
#define PII pair<int, int>
#define X   first
#define Y   second

int fx[4] = {1, 0, -1, 0};
int fy[4] = {0, -1, 0, 1};

char grid[MXN][MXN];
int dist[MXN][MXN];
PII parent[MXN][MXN];
bool visited[MXN][MXN];
int n, m;

void bfs(PII s)
{
    queue<PII>q;
    q.push(s);
    visited[s.X][s.Y] = true;
    dist[s.X][s.Y] = 0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)  parent[i][j] = {-1, -1};
    }

    while(!q.empty())
    {
        s = q.front();
        q.pop();

        for(int i=0; i<4; i++)
        {
            int x = s.X + fx[i];
            int y = s.Y + fy[i];

            if(x>=0 && x<n && y>=0 && y<m && grid[x][y] != '#' && !visited[x][y])
            {
                q.push({x, y});
                visited[x][y] = true;
                dist[x][y] = dist[s.X][s.Y] + 1;
                parent[x][y] = s;
                
                /// break here if you want to find the shortest distance/path from source to a particular destination and (x, y) is the destination.
            }
        }
    }
}

void print_shortest_path(PII x)
{
    if(x.X == -1 && x.Y == -1)  return;

    print_shortest_path(parent[x.X][x.Y]);
    printf(" (%d %d)", x.X, x.Y);
}

int main()
{
    int x, y;

    scanf("%d %d", &n, &m); /// number of rows and columns
    for(int i=0; i<n; i++)  scanf("%s", grid[i]);   /// grid

    scanf("%d %d", &x, &y); /// source

    bfs({x, y});

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(!visited[i][j])
            {
                printf("(%d, %d) is not reachable from (%d, %d)\n", i, j, x, y);
                continue;
            }
            printf("Shortest path from (%d, %d) to (%d, %d) => distance: %d, path:", x, y, i, j, dist[i][j]);
            print_shortest_path({i, j});
            puts("");
        }
    }
    return 0;
}

/*
4 5
...#.
.#.#.
##.#.
.#..#

1 2
*/

