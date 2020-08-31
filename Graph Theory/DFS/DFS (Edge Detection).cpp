#include<bits/stdc++.h>
using namespace std;

#define MXN         100005
#define PII         pair<int, int>
#define X           first
#define Y           second
#define VISITED     1
#define FINISHED    2

vector<int> edges[MXN];
vector<PII> tree_edges, forward_edges, back_edges, cross_edges;
int visited[MXN];
int start_time[MXN], end_time[MXN], tym;
int n, m;

void dfs(int s)
{
    visited[s] = VISITED;
    start_time[s] = ++tym;

    for(int x : edges[s])
    {
        if(!visited[x])
        {
            tree_edges.push_back({s, x});
            dfs(x);
        }
        else if(start_time[s] < start_time[x] && visited[x] == FINISHED)    forward_edges.push_back({s, x});
        else if(start_time[s] > start_time[x] && visited[x] != FINISHED)    back_edges.push_back({s, x});
        else    cross_edges.push_back({s, x});
    }

    visited[s] = FINISHED;
    end_time[s] = ++tym;
}

void print_edges()
{
    puts("Tree edges:");
    for(PII pr : tree_edges)    cout<<"("<<pr.X<<" "<<pr.Y<<") ";
    puts("");

    puts("Forward edges:");
    for(PII pr : forward_edges) cout<<"("<<pr.X<<" "<<pr.Y<<") ";
    puts("");

    puts("Back edges:");
    for(PII pr : back_edges)    cout<<"("<<pr.X<<" "<<pr.Y<<") ";
    puts("");

    puts("Cross edges:");
    for(PII pr : cross_edges)   cout<<"("<<pr.X<<" "<<pr.Y<<") ";
    puts("");
}

int main()
{
    int x, y;

    scanf("%d %d", &n, &m); /// number of nodes and edges
    for(int i=0; i<m; i++)  /// edges
    {
        scanf("%d %d", &x, &y);
        edges[x].push_back(y);
    }

    dfs(1);
    print_edges();

    return 0;
}

/*
13 20

1 2
2 3
3 4
3 5
5 4
5 2
1 6
6 7
7 8
8 6
8 9
9 5
9 10
7 11
8 12
12 11
12 13
13 8
13 9
7 13
*/
