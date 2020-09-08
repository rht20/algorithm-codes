#include<bits/stdc++.h>
using namespace std;

#define MXN 100005

vector<int> edges[MXN], rev_edges[MXN], scc_list[MXN];
stack<int> order;
bool visited[MXN];
int n, m, cnt;

void dfs1(int s)
{
    visited[s] = true;
    for(int x : edges[s])
    {
        if(!visited[x])    dfs1(x);
    }
    order.push(s);
}

void dfs2(int s)
{
    visited[s] = true;
    scc_list[cnt].push_back(s);

    for(int x : rev_edges[s])
    {
    	if(!visited[x])    dfs2(x);
    }
}

int main()
{
    int x, y;

    scanf("%d %d", &n, &m); // number of nodes and edges
    for(int i=0; i<m; i++)  // edges
    {
        scanf("%d %d", &x, &y);
        edges[x].push_back(y);
        rev_edges[y].push_back(x);
    }

    for(int i=1; i<=n; i++)
    {
        if(!visited[i])    dfs1(i);
    }

    memset(visited, false, sizeof(visited));
    while(!order.empty())
    {
    	x = order.top();
    	order.pop();

    	if(!visited[x])
    	{
    	    cnt++;
    	    dfs2(x);
    	}
    }

    printf("Number of SCC's: %d\n", cnt);
    for(int i=1; i<=cnt; i++)
    {
    	printf("%d:", i);
        for(int x : scc_list[i])    cout<<" "<<x;
        puts("");
    }
    return 0;
}

/*
7 8

1 2
2 3
3 4
3 1
5 6
7 5
4 5
6 7
*/
