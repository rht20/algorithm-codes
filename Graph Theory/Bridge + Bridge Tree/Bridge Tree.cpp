#include<bits/stdc++.h>
using namespace std;

#define MXN 100005
#define PII pair<int, int>
#define X   first
#define Y   second

vector<PII> edges[MXN];	// {opposite vertex, edge id}
vector<int> bridge_tree[MXN];
int discovery[MXN], low[MXN], tym;
bool bridge[MXN], visited[MXN];
int comp_id[MXN];
int n, m, comp;

void mark_bridges_dfs(int s, int p)
{
    visited[s] = true;
    discovery[s] = low[s] = ++tym;

    for(PII pr : edges[s])
    {
    	int x = pr.X;
    	int id = pr.Y;

	if(x == p)    continue;
	if(visited[x])	low[s] = min(low[s], discovery[x]);
	else
	{
	    mark_bridges_dfs(x, s);
	    low[s] = min(low[s], low[x]);
		    
	    if(discovery[s] < low[x])	bridge[id] = true;
	}
    }
}

void bridge_tree_dfs_bfs(int s)
{
    visited[s] = true;
    comp_id[s] = comp;

    int cur_comp = comp;
    
    queue<int> q;
    q.push(s);

    while(!q.empty())
    {
        s = q.front();
        q.pop();

        for(PII pr : edges[s])
        {
            int x = pr.X;
            int id = pr.Y;

            if(visited[x])    continue;

            if(bridge[id])
            {
        	comp++;
        	bridge_tree[cur_comp].push_back(comp);
        	bridge_tree[comp].push_back(cur_comp);
        	bridge_tree_dfs_bfs(x);
            }
            else
            {
        	q.push(x);
        	visited[x] = true;
        	comp_id[x] = cur_comp;
            }
        }
    }
}

int main()
{
    int x, y;

    scanf("%d %d", &n, &m);	// number of nodes and edges
    for(int i=0; i<m; i++)	// edges
    {
        scanf("%d %d", &x, &y);
        edges[x].push_back({y, i});
        edges[y].push_back({x, i});
    }

    for(int i=1; i<=n; i++)
    {
    	if(!visited[i])    mark_bridges_dfs(i, -1);
    }

    memset(visited, false, sizeof(visited));
    for(int i=1; i<=n; i++)
    {
    	if(!visited[i])
    	{
    	    comp++;
    	    bridge_tree_dfs_bfs(i);
    	}
    }

    puts("Node - Component Id");
    for(int i=1; i<=n; i++)	printf("%d - %d\n", i, comp_id[i]);

    puts("Bridge Tree edges:");
    for(int i=1; i<=comp; i++)
    {
        for(int x : bridge_tree[i])
        {
            if(x > i)	printf("%d %d\n", i, x);
        }
    }

    return 0;
}

/*
7 7

1 2
1 3
3 4
3 7
4 5
4 6
6 7


3 3

1 2
2 3
3 1
*/
