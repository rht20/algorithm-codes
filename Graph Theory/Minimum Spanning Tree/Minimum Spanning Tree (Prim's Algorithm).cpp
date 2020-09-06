#include<bits/stdc++.h>
using namespace std;

#define MXN 100005
#define LL  long long int
#define PII pair<int, int>
#define X   first
#define Y   second

vector<PII> edges[MXN], tree_edges[MXN];
bool visited[MXN];
LL total_weight;
int n, m;

struct data
{
    int x, y, w;

    bool operator < (data d) const
    {
        return	(d.w < w);
    }
};

void mst_prim(int s)
{
    priority_queue<data> pq;
    pq.push({s, -1, 0});

    for(int i=0; i<n; i++)
    {
    	while(!pq.empty() && visited[pq.top().x])	pq.pop();
		
	data d = pq.top();
	pq.pop();

	if(d.y != -1)
	{
	    tree_edges[d.x].push_back({d.y, d.w});
	    tree_edges[d.y].push_back({d.x, d.w});
	}

	visited[d.x] = true;
	total_weight += d.w;

	for(PII pr : edges[d.x])
	{
	    if(!visited[pr.X])	pq.push({pr.X, d.x, pr.Y});
	}
    }
}

int main()
{
    int x, y, w;

    scanf("%d %d", &n, &m);	// number of nodes and edges
    for(int i=0; i<m; i++)	// edges
    {
        scanf("%d %d %d", &x, &y, &w);
        edges[x].push_back({y, w});
        edges[y].push_back({x, w});
    }

    mst_prim(1);

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
