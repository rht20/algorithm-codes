#include<bits/stdc++.h>
using namespace std;

#define MXN         30
#define UNVISITED   0
#define VISITED     1
#define FINISHED    2

vector<int> edges[MXN], alphabets, order;
int indegree[MXN], visited[MXN];
bool cycle;
int n;

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
}

void bfs_and_permutation()
{
    if(order.size() == n)
    {
        bool flag = false;
        for(int x : order)
        {
            if(flag)    printf(" ");
            printf("%c", (x + 'A'));
            flag = true;
        }
        puts("");
    }

    for(int ch : alphabets)
    {
        if(!indegree[ch] && !visited[ch])
        {
            for(int x : edges[ch])  indegree[x]--;
            visited[ch] = VISITED;
            order.push_back(ch);

            bfs_and_permutation();

            for(int x : edges[ch])  indegree[x]++;
            visited[ch] = UNVISITED;
            order.pop_back();
        }
    }
}

void input()
{
    string str;

    getchar();

    getline(cin, str);
    for(char ch : str)
    {
        if(isalpha(ch)) alphabets.push_back(ch - 'A');
    }
    n = alphabets.size();

    getline(cin, str);
    for(int i=0; i<str.size(); i+=4)
    {
        edges[str[i] - 'A'].push_back(str[i + 2] - 'A');
        indegree[str[i + 2] - 'A']++;
    }
}

void clr()
{
    cycle = false;
    order.clear();
    alphabets.clear();
    memset(visited, 0, sizeof(visited));
    memset(indegree, 0, sizeof(indegree));
    for(int i=0; i<MXN; i++)    edges[i].clear();
}

int main()
{
    int t;
    cin >> t;
    getchar();
    while(t--)
    {
        clr();
        input();

        for(int ch : alphabets)
        {
            if(!visited[ch])    dfs(ch);
            if(cycle)   break;
        }

        if(cycle)   puts("NO");
        else
        {
            memset(visited, 0, sizeof(visited));
            bfs_and_permutation();
        }

        if(t)   puts("");
    }
    return  0;
}

/*
Problem: UVA => 872 - Ordering
*/
