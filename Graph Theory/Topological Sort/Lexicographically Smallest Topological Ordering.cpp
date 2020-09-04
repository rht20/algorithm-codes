#include<bits/stdc++.h>
using namespace std;

#define MXN 105

vector<int> edges[MXN];
queue<int> order;
map<string, int> string_to_int;
map<int, string> int_to_string;
set<int> st;
set<int>::iterator it;
int indegree[MXN];
int n, m;

void topological_sort()
{
    for(int i=0; i<n; i++)
    {
        if(!indegree[i])    st.insert(i);
    }

    while(!st.empty())
    {
        it = st.begin();
        int s = *it;
        st.erase(it);

        order.push(s);

        for(int x : edges[s])
        {
            indegree[x]--;
            if(!indegree[x])    st.insert(x);
        }
    }
}

void input()
{
    string s1, s2;

    for(int i=0; i<n; i++)
    {
        cin >> s1;
        string_to_int[s1] = i;
        int_to_string[i] = s1;
    }

    scanf("%d", &m);
    for(int i=0; i<m; i++)
    {
        cin >> s1 >> s2;
        edges[string_to_int[s1]].push_back(string_to_int[s2]);
        indegree[string_to_int[s2]]++;
    }
}

void clr()
{
    st.clear();
    string_to_int.clear();
    int_to_string.clear();
    memset(indegree, 0, sizeof(indegree));
    for(int i=0; i<n; i++)  edges[i].clear();
}

int main()
{
    int cs = 0;

    while(scanf("%d", &n) != EOF)
    {
        cs++;
        
        clr();
        input();
        topological_sort();

        printf("Case #%d: Dilbert should drink beverages in this order:", cs);
        while(!order.empty())
        {
            cout<<" "<<int_to_string[order.front()];
            order.pop();
        }
        puts(".");
        puts("");
    }
    return 0;
}


/*
Problem: UVA => 11060 - Beverages
*/
