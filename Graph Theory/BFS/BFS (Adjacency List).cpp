#include<bits/stdc++.h>
using namespace std;

#define MXN 100005

vector<int> edges[MXN];
int dist[MXN], parent[MXN];
bool visited[MXN];
int n, m;

void bfs(int s)
{
    queue<int> q;
    q.push(s);
    visited[s] = true;
    dist[s] = 0;
    memset(parent, -1, sizeof(parent));

    while(!q.empty())
    {
        s = q.front();
        q.pop();

        for(int x : edges[s])
        {
            if(visited[x])  continue;

            q.push(x);
            visited[x] = true;
            dist[x] = dist[s] + 1;
            parent[x] = s;
            
            /// break here if you want to find the shortest distance/path from source to a particular node and x is the destination node.
        }
    }
}

void print_shortest_path(int x)
{
    if(x == -1) return;

    print_shortest_path(parent[x]);
    printf(" %d", x);
}

int main()
{
    int x, y;

    scanf("%d %d", &n, &m); /// number of nodes and edges
    for(int i=0; i<m; i++)  /// edges
    {
        scanf("%d %d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    scanf("%d", &x);    /// source

    bfs(x);

    for(int i=1; i<=n; i++)
    {
        if(!visited[i])
        {
            printf("%d is not reachable from %d\n", i, x);
            continue;
        }
        printf("Shortest path from %d to %d => distance: %d, path:", x, i, dist[i]);
        print_shortest_path(i);
        puts("");
    }
    return 0;
}

/*
10 13

1 2
2 6
6 10
10 5
5 8
1 3
3 8
3 7
7 9
9 10
1 4
4 7
7 8

1
*/

