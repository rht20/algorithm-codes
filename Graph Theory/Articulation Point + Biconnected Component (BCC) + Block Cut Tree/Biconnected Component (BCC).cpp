#include<bits/stdc++.h>
using namespace std;

#define MXN 100005
#define PII pair<int, int>
#define X   first
#define Y   second

vector<int> edges[MXN], bcc[MXN];
stack<PII> stk;
int discovery[MXN], low[MXN], tym;
bool visited[MXN], taken[MXN];
int n, m, cnt;

void get_biconnected_components(int s, int p)
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
            get_biconnected_components(x, s);
            low[s] = min(low[s], low[x]);

            if((p == -1 && child > 1) || (p != -1 && discovery[s] <= low[x]))
            {
                cnt++;
                while(!stk.empty())
                {
                    int a = stk.top().X;
                    int b = stk.top().Y;
                    stk.pop();

                    if(!taken[a])   bcc[cnt].push_back(a);
                    if(!taken[b])   bcc[cnt].push_back(b);
                    taken[a] = taken[b] = true;

                    if(a == s && b == x)    break;
                }

                for(int y : bcc[cnt])   taken[y] = false;
            }
        }
        else if(discovery[x] < low[s])
        {
            stk.push({s, x});
            low[s] = min(low[s], discovery[x]);
        }
    }
}

int main()
{
    int x, y;

    scanf("%d %d", &n, &m);    // number of nodes and edges
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
            get_biconnected_components(i, -1);
            if(!stk.empty())
            {
                cnt++;
                while(!stk.empty())
                {
                    int a = stk.top().X;
                    int b = stk.top().Y;
                    stk.pop();

                    if(!taken[a])   bcc[cnt].push_back(a);
                    if(!taken[b])   bcc[cnt].push_back(b);
                    taken[a] = taken[b] = true;
                }
                
                for(int y : bcc[cnt])   taken[y] = false;
            }
        }
    }

    printf("Number of Biconnected Components: %d\n", cnt);
    for(int i=1; i<=cnt; i++)
    {
        printf("(%d):", i);
        for(int x : bcc[i]) printf(" %d", x);
        puts("");
    }

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
