#include<bits/stdc++.h>
using namespace std;

#define MXN         100005
#define VISITED     1
#define FINISHED    2

vector<int> edges[MXN];
stack<int> order;
int visited[MXN];
bool cycle;
int n, m;

void dfs(int s)
{
    visited[s] = VISITED;
    for(int x : edges[s])
    {
        if(cycle)   return;
        if(!visited[x]) dfs(x);
        else if(visited[x] != FINISHED) cycle = true;
    }
    visited[s] = FINISHED;
    order.push(s);
}

int main()
{
    int x, y;

    scanf("%d %d", &n, &m); // number of nodes and edges
    for(int i=0; i<m; i++)  // edges
    {
        scanf("%d %d", &x, &y);
        edges[x].push_back(y);
    }

    for(int i=1; i<=n; i++)
    {
        if(!visited[i])
        {
            dfs(i);
            if(cycle)   break;
        }
    }

    if(cycle)   puts("No topological order.");
    else
    {
        printf("Topological order:");
        while(!order.empty())
        {
            printf(" %d", order.top());
            order.pop();
        }
        puts("");
    }
    return 0;
}

/*
6 6

6 3
6 1
5 1
5 2
3 4
4 2


3 3

1 2
2 3
3 1
*/
