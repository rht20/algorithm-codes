#include<bits/stdc++.h>
using namespace std;

#define MXN 100005
#define PII pair<int, int>
#define X   first
#define Y   second

vector<int> edges[MXN], bcc[MXN], block_cut_tree[MXN];
stack<PII> stk;
int discovery[MXN], low[MXN], tym;
bool articulation_point[MXN], visited[MXN], taken[MXN];
int id[MXN];
int n, m, comp, cnt;

void dfs(int s, int p)
{
    visited[s] = true;
    discovery[s] = low[s] = ++tym;
    int child = 0;

    for(int x : edges[s])
    {
        if(x == p)    continue;
        if(!visited[x])
        {
            child++;
            stk.push({s, x});
            dfs(x, s);
            low[s] = min(low[s], low[x]);

            if((p == -1 && child > 1) || (p != -1 && discovery[s] <= low[x]))
            {
                articulation_point[s] = true;
                comp++;
                while(!stk.empty())
                {
                    int a = stk.top().X;
                    int b = stk.top().Y;
                    stk.pop();

                    if(!taken[a])   bcc[comp].push_back(a);
                    if(!taken[b])   bcc[comp].push_back(b);
                    taken[a] = taken[b] = true;

                    if(a == s && b == x)    break;
                }

                for(int y : bcc[comp])  taken[y] = false;
            }
        }
        else if(discovery[x] < low[s])
        {
            stk.push({s, x});
            low[s] = min(low[s], discovery[x]);
        }
    }
}

void build_tree()
{
    for(int i=1; i<=n; i++)
    {
        if(articulation_point[i])   id[i] = ++cnt;
    }

    for(int i=1; i<=comp; i++)
    {
        cnt++;
        for(int x : bcc[i])
        {
            if(articulation_point[x])
            {
                block_cut_tree[id[x]].push_back(cnt);
                block_cut_tree[cnt].push_back(id[x]);
            }
            else    id[x] = cnt;
        }
    }
}

void print()
{
    printf("Articulation points:");
    int apc = 0;
    vector<int> apcs;
    for(int i=1; i<=n; i++)
    {
        if(articulation_point[i])
        {
            apc++;
            apcs.push_back(i);
            printf(" %d", i);
        }
    }
    puts("");

    printf("Number of Biconnected Components: %d\n", comp);
    for(int i=1; i<=comp; i++)
    {
        printf("(%d):", i);
        for(int x : bcc[i]) printf(" %d", x);
        puts("");
    }

    puts("Block Cut Tree edges:");
    for(int i=1; i<=apc; i++)
    {
        for(int x : block_cut_tree[i])  printf("%d(AP-%d) - %d(BCC-%d)\n", i, apcs[i-1], x, (x - apc));
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
        edges[y].push_back(x);
    }

    for(int i=1; i<=n; i++)
    {
        if(!visited[i])
        {
            dfs(i, -1);
            if(!stk.empty())
            {
                comp++;
                while(!stk.empty())
                {
                    int a = stk.top().X;
                    int b = stk.top().Y;
                    stk.pop();

                    if(!taken[a])   bcc[comp].push_back(a);
                    if(!taken[b])   bcc[comp].push_back(b);
                    taken[a] = taken[b] = true;
                }
                
                for(int y : bcc[comp])  taken[y] = false;
            }
        }
    }

    build_tree();

    print();

    return 0;
}

/**
12 14

1 2
2 3
2 4
3 4
3 5
4 5
2 6
1 7
6 7
6 8
6 9
8 9
9 10
11 12
*/