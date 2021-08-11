#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef  long long ll;
const int N = 2e2+10,M = N * N;
int lw[N], compId[N] , dfsTime[N], stk[N] , stkSz , vis[N] , vid , ncp , curTime , n;
int notSrc[N] , notSnk[N];
struct ADJ {
    int head[N], nxt[M], to[M], ne;

    void init(int n) {
        memset(head, -1, n * sizeof(head[0]));
        ne = 0;
    }

    void addEdge(int f, int t) {
        to[ne] = t;
        nxt[ne] = head[f];
        head[f] = ne++;
    }

}adj, Cgraph;

void tarjanDFS(int u){
    vis[u] = vid;
    stk[stkSz++] = u;
    lw[u] = dfsTime[u] = curTime++;
    compId[u] = -1;

    for(int e = adj.head[u] ; ~e ; e = adj.nxt[e]){
        int v = adj.to[e];
        if(vis[v] != vid){
            tarjanDFS(v);
            lw[u] = min(lw[u] , lw[v]);
        }
        else if(compId[v] == -1){
            lw[u] = min(lw[u] , lw[v]);
        }
    }

    if(lw[u] == dfsTime[u]){
        do{
            compId[stk[--stkSz]] = ncp;
        }while(stk[stkSz] != u);
        ncp++;
    }
}

void T(){
    ++vid;
    ncp = 0;
    curTime = 0;
    for(int i = 0;i < n;++i){
        if(vis[i] != vid){
            tarjanDFS(i);
        }
    }

    Cgraph.init(ncp);
    for(int u = 0 ; u < n; ++u){
        for(int e = adj.head[u] ; ~e ; e = adj.nxt[e]){
            int v = adj.to[e];
            if(compId[u] == compId[v]) continue;
            Cgraph.addEdge(u , v);
            notSnk[compId[u]] = vid;
            notSrc[compId[v]] = vid;
        }
    }
}

int main(){
    scanf("%d",&n);
    adj.init(n);
    for(int u = 0;u < n;++u){
        int v;
        while(scanf("%d",&v), v){
            v--;
            adj.addEdge(u,v);
        }
    }
    T();
    int nSrc = 0,nSnk = 0;
    for(int i = 0;i < ncp; ++i){
        nSrc += (notSrc[i] != vid);
        nSnk += (notSnk[i] != vid);
    }
    printf("%d\n%d\n",nSrc ,ncp == 1 ? 0 : max(nSrc,nSnk));
    return 0;
}