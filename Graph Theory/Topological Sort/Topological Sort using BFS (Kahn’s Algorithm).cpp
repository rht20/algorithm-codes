#include<bits/stdc++.h>
using namespace std;

#define MXN 100005

vector<int> edges[MXN];
queue<int> order;
int indegree[MXN];
int n, m;

void topological_sort()
{
    queue<int> q;

    for(int i=1; i<=n; i++)
    {
    	if(!indegree[i])    q.push(i);
    }

    while(!q.empty())
    {
    	int s = q.front();
    	q.pop();

    	order.push(s);

        for(int x : edges[s])
        {
            indegree[x]--;
            if(!indegree[x])	q.push(x);
        }
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
        indegree[y]++;
    }

    topological_sort();

    if(order.size() != n)	puts("No topological order.");
    else
    {
    	printf("Topological order:");
        while(!order.empty())
        {
            printf(" %d", order.front());
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
