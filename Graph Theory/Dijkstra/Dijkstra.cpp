#include<bits/stdc++.h>
using namespace std;

#define MXN 100005
#define LL  long long int
#define PII pair<int, int>
#define X   first
#define Y   second

vector<PII> edges[MXN];
LL dist[MXN];
int parent[MXN];
bool visited[MXN];
int n, m;

struct node
{
    int x;
    LL w;

    bool operator < (node nd) const
    {
        return  (nd.w < w);
    }
};
priority_queue<node>pq;

void dijkstra(int s)
{
    pq.push({s, 0});
    visited[s] = true;
    dist[s] = 0;
    memset(parent, -1, sizeof(parent));

    while(!pq.empty())
    {
        node nd = pq.top();
        pq.pop();

        /// break here if you want to find the shortest distance/path from source to a particular node and nd.x is the destination node.

        for(PII pr : edges[nd.x])
        {
            if(!visited[pr.X] || (dist[nd.x] + pr.Y) < dist[pr.X])
            {
                dist[pr.X] = dist[nd.x] + pr.Y;
                pq.push({pr.X, dist[pr.X]});
                visited[pr.X] = true;
                parent[pr.X] = nd.x;
            }
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
    int x, y, w;

    scanf("%d %d", &n, &m); /// number of nodes and edges
    for(int i=0; i<m; i++)  /// edges
    {
        scanf("%d %d %d", &x, &y, &w);
        edges[x].push_back({y, w});
        edges[y].push_back({x, w});
    }

    scanf("%d", &x);    /// source

    dijkstra(x);

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
9 13

1 2 4
1 8 8
2 3 8
2 8 11
3 4 7
3 9 2
4 5 9
4 6 14
5 6 10
6 7 2
7 8 1
7 9 6
8 9 7

1
*/
