#include<bits/stdc++.h>
using namespace std;

#define MXN 100005
#define PII pair<int, int>
#define X   first
#define Y   second

vector<int> edges[MXN];
vector<PII> bridges;
int discovery[MXN], low[MXN], tym;
bool visited[MXN];
int n, m;

void get_bridges(int s, int p)
{
    visited[s] = true;
    discovery[s] = low[s] = ++tym;

    for(int x : edges[s])
    {
	if(x == p)    continue;
	if(visited[x])	low[s] = min(low[s], discovery[x]);
	else
	{
	    get_bridges(x, s);
	    low[s] = min(low[s], low[x]);
	    
	    if(discovery[s] < low[x])	bridges.push_back({s, x});
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
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    for(int i=1; i<=n; i++)
    {
    	if(!visited[i])    get_bridges(i, -1);
    }

    puts("Bridges:");
    for(PII pr : bridges)    printf("%d %d\n", pr.X, pr.Y);

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
1 3
2 3
*/
