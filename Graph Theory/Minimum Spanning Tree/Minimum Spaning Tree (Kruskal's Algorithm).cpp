#include<bits/stdc++.h>
using namespace std;

#define MXN 100005
#define LL  long long int
#define PII pair<int, int>
#define X   first
#define Y   second

struct edge
{
    int x, y, w;
};
vector<edge> edges;
vector<PII> tree_edges[MXN];
int parent[MXN];
LL total_weight;
int n, m;

bool comp(edge e1, edge e2)
{
    return  (e1.w < e2.w);
}

int find(int p)
{
    if(parent[p] == p)  return  p;
    return  parent[p] = find(parent[p]);
}

void mst_kruskal()
{
    sort(edges.begin(), edges.end(), comp);

    for(int i=1; i<=n; i++) parent[i] = i;
    
    int cnt = 0;
    for(edge e : edges)
    {
        int x = find(e.x);
        int y = find(e.y);
        if(x != y)
        {
            parent[y] = x;
            total_weight += e.w;
            tree_edges[e.x].push_back({e.y, e.w});
            tree_edges[e.y].push_back({e.x, e.w});
            cnt++;
            if(cnt == (n - 1))  break;
        }
    }
}

int main()
{
    int x, y, w;

    scanf("%d %d", &n, &m); // number of nodes and edges
    for(int i=0; i<m; i++)  // edges
    {
        scanf("%d %d %d", &x, &y, &w);
        edges.push_back({x, y, w});
    }

    mst_kruskal();

    printf("Minimum weight = %lld\n", total_weight);
    puts("MST edges:");
    for(int i=1; i<=n; i++)
    {
        for(PII pr : tree_edges[i])
        {
            if(pr.X > i)    printf("%d %d %d\n", i, pr.X, pr.Y);
        }
    }
    return 0;
}

/*
6 9

5 4 9
5 1 4
4 1 1
4 2 3
4 3 5
3 2 3
3 6 8
6 2 7
1 2 2
*/
