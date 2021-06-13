#include <bits/stdc++.h>

using namespace std;
typedef  long long ll;
const int N=2e5+6;

//graph data
int nxt[N],to[N],head[N],nodeVal[N],sortNodeVal[N],ne,n,q,un;

//lca tree
int lca[N],nodeToIndex[N],depth[N],dfn;

//node data
int stTime[N],enTime[N],path[N],curTime;

//sparce table
int sp[18][N],lg[N];

//MO's data
int freq[N],qs[N],qe[N],qi[N],qAns[N],IsOdd[N],qLca[N],sq,s,e,ans;

void DFS(int u,int par)
{
    lca[nodeToIndex[u] = dfn++] = u;
    path[stTime[u] = curTime++] = u;
    for(int e = head[u] ; ~e ; e = nxt[e])
    {
        int v = to[e];
        if(v == par) continue;
        depth[v] = depth[u] + 1;
        DFS(v,u);
        lca[dfn++] = u;
    }
    path[enTime[u] = curTime++] = u;
}

void addEdge(int f,int t)
{
    to[ne] = t;
    nxt[ne] = head[f];
    head[f] = ne++;
}

void addBiedge(int u,int v)
{
    addEdge(u,v);
    addEdge(v,u);
}

void BuildSp()
{
    lg[0] = -1;
    for(int i = 0; i < dfn ; ++i)
    {
        lg[i+1]= lg[i] + !(i & (i + 1 ));
        sp[0][i] = i;
    }

    for(int j = 1 ; (1 << j) <= dfn ; ++j)
    {
        for(int i = 0 ;i + (1 << j) <= dfn ; ++i)
        {
            int a = sp[j - 1][i],b = sp[j - 1][i + (1 << (j - 1) )];
            sp[j][i] = (depth[lca[a]] < depth[lca[b]] ? a : b);
        }
    }
}

int RMQ(int a,int b)
{
    int Log = lg[b - a + 1];
    a = sp[Log][a];
    b = sp[Log][b - (1 << Log) + 1];
    return (depth[lca[a]] < depth[lca[b]] ? a : b);
}

int LCA(int u,int v)
{
    u = nodeToIndex[u];
    v = nodeToIndex[v];
    if(u > v) swap(u,v);
    return lca[RMQ(u,v)];
}

void add(int val)
{
    ans += !freq[val]++;
}

void del(int val)
{
    ans -= !--freq[val];
}

void flip(int i)
{
    int u = path[i];
    if(IsOdd[u] ^= 1)
    {
        add(nodeVal[u]);
    }
    else
    {
        del(nodeVal[u]);
    }
}

void updateSE(int idx)
{
    while(e < qe[idx] + 1) flip(e++);
    while (s > qs[idx]) flip(--s);
    while (s < qs[idx]) flip(s++);
    while(e > qe[idx] + 1) flip(--e);
}

void init()
{
    ne=0;
    memset(head+1,-1,n*sizeof(head[0]));
}

void compress()
{
    sort(sortNodeVal+1,sortNodeVal+n+1);
    un = unique(sortNodeVal,sortNodeVal+n+1) - sortNodeVal;
    for(int i = 1 ;i <= n; ++i)
    {
       nodeVal[i] = lower_bound(sortNodeVal,sortNodeVal+un,nodeVal[i]) - sortNodeVal;
    }
}

int main()
{
    scanf("%d%d",&n,&q);
    for(int i = 1;i <= n; ++i)
    {
        scanf("%d",nodeVal+i);
        sortNodeVal[i] = nodeVal[i];
    }
    compress();
    init();
    for(int i=0 ; i < n - 1; ++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addBiedge(u,v);
    }
    DFS(1,1);
    BuildSp();
    for(int i = 0 ;i < q; ++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        if(stTime[u] > stTime[v]) swap(u,v);
        int Lca = LCA(u,v);
        qLca[i] = Lca;
        qi[i] = i;
        if(u == Lca)
        {
            qs[i] = stTime[u] + 1;
            qe[i] = stTime[v];
        }
        else
        {
            qs[i] = enTime[u];
            qe[i] = stTime[v];
        }
    }
    sq = sqrt(curTime);
    sort(qi , qi+q,[](int a,int b){
       return make_pair(qs[a]/sq,qe[a]) <  make_pair(qs[b]/sq,qe[b]);
    });
    for(int i=0 ; i < q ; ++i)
    {
        int cur = qi[i];
        updateSE(cur);
        add(nodeVal[qLca[cur]]);
        qAns[cur] = ans;
        del(nodeVal[qLca[cur]]);
    }
    for(int i = 0 ; i < q ; ++i)
    {
        printf("%d\n",qAns[i]);
    }
    return 0;
}
