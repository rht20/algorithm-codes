#include<bits/stdc++.h>
using namespace std;

#define MXN 100005

vector<int> edges[MXN];
bool articulation_point[MXN], visited[MXN];
int discovery[MXN], low[MXN], tym;
int n, m;

void dfs(int s, int p)
{
    visited[s] = true;
    discovery[s] = low[s] = ++tym;
    int child = 0;

    for(int x : edges[s])
    {
	if(x == p)    continue;
	if(visited[x])	low[s] = min(low[s], discovery[x]);
	else
	{
	    child++;
	    dfs(x, s);
	    low[s] = min(low[s], low[x]);

	    if(p != -1 && discovery[s] <= low[x])    articulation_point[s] = true;
	}
    }

    if(p == -1 && child > 1)	articulation_point[s] = true;
}

int main()
{
    int x, y;

    scanf("%d %d", &n, &m);    // number of nodes and edges
    for(int i=0; i<m; i++)	// edges
    {
        scanf("%d %d", &x, &y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    for(int i=1; i<=n; i++)
    {
    	if(!visited[i])    dfs(i, -1);
    }

    printf("Articulation points:");
    for(int i=1; i<=n; i++)
    {
    	if(articulation_point[i])    printf(" %d", i);
    }
    puts("");

    return 0;
}

/**
7 7

1 2
1 3
3 4
3 7
4 5
4 6
6 7


6 7

1 3
1 4
1 6
3 2
2 4
3 5
5 6


6 7

1 2
2 3
2 4
3 4
3 5
3 6
5 6
*/
