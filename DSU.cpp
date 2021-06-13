#include <bits/stdc++.h>

using namespace std;
typedef  long long ll;
const int N=2e5+6;

struct DSU
{
    int parent[N] , sz[N];
    void init(int n)
    {
        iota(parent,parent+n,0);
        fill(sz,sz+n,1);
    }

    int findParent(int u)
    {
        if(parent[u] == u) return u;
        return parent[u] = findParent(parent[u]);
    }

    bool makeParent(int u,int v)
    {
        u = findParent(u);
        v = findParent(v);
        if(u == v) return true;
        if(sz[u] < sz[v]) swap(u,v);
        parent[v] = u;
        sz[u] = sz[v];
        return false;
    }
}dsu;

int main()
{

    return 0;
}
