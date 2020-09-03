#include<bits/stdc++.h>
using namespace std;

#define MXN 100005
#define INF 1000000000000000LL
#define LL  long long int

struct edge
{
    int x, y;
    LL w;
};
vector<edge> edges;
LL dist[MXN];
int parent[MXN];
int n, m;
bool negative_cycles;

void bellman_ford(int s)
{
    fill(dist, dist + n + 1, INF);
    memset(parent, -1, sizeof(parent));
    dist[s] = 0;

    // relax edges repeatedly
    for(int i=1; i<n; i++)
    {
        bool update = false;
        for(edge e : edges)
        {
            if(dist[e.x] != INF && (dist[e.x] + e.w) < dist[e.y])
            {
                dist[e.y] = dist[e.x] + e.w;
                parent[e.y] = e.x;
                update = true;
            }
        }
        if(!update)	break;
    }
    
    // check for negative-weight cycles
    for(edge e : edges)
    {
    	if(dist[e.x] != INF && (dist[e.x] + e.w) < dist[e.y])
    	{
    	    negative_cycles = true;
    	    return;
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

    // number of nodes and edges
    scanf("%d %d", &n, &m);
    
    // edges
    for(int i=0; i<m; i++)
    {
        scanf("%d %d %d", &x, &y, &w);
        edges.push_back({x, y, w});
    }
    
    // source
    scanf("%d", &x);
    
    bellman_ford(x);

    if(negative_cycles)	puts("Negative cycle exists.");
    else
    {
    	for(int i=1; i<=n; i++)
    	{
    	    if(dist[i] == INF)	printf("%d is not reachable from %d\n", i, x);
    	    else
    	    {
    	        printf("Shortest path from %d to %d => distance: %d, path:", x, i, dist[i]);
    	        print_shortest_path(i);
    	        puts("");
    	    }
	}
    }
    return  0;
}

/*
5 8

1 2 -1
1 3 4
2 3 3
2 4 2
2 5 2
4 2 1
4 3 5
5 4 -3

1


3 3

2 3 2
1 2 3
3 1 -10

1
*/
