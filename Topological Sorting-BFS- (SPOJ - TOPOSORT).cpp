#include <bits/stdc++.h>

using namespace std;
typedef  long long ll;
const int N=10006,M=1000005;
int head[N], nxt[M], to[M],Indeg[N] , res[N], resSz ,ne, n, m;

void addEdge(int f,int t){
    nxt[ne] = head[f];
    to[ne] = t;
    head[f] = ne++;
    Indeg[t]++;
}

void topo(){
    priority_queue<int> pq;
    for(int i = 0; i < n;++i){
        if(!Indeg[i]) pq.push(-i);
    }

    while(!pq.empty()){
        int u = -pq.top();
        pq.pop();
        res[resSz++] = u;
        for(int e = head[u]; ~e ;e = nxt[e]){
            int v = to[e];
            if(!--Indeg[v]) pq.push(-v);
        }
    }
}


void init(){
    memset(head, -1, n * sizeof(head[0]));
    ne = 0;
}

int main(){
    scanf("%d%d",&n,&m);
    init();
    for(int i = 0;i < m;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        --u,--v;
        addEdge(u,v);
    }
    topo();
    if(resSz != n) puts("Sandro fails.");
    else{
        for(int i = 0;i < n;++i){
            printf("%d%c",res[i] + 1," \n"[i == n - 1]);
        }
    }
    return 0;
}
