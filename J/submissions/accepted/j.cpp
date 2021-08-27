#include<bits/stdc++.h>
#define pb push_back
#define MXN 200005
using namespace std;
struct Scc{
    int n, nScc, vst[MXN], bln[MXN];
    vector<int> E[MXN], rE[MXN], vec;
    void init(int _n){
        n = _n;
        for (int i=0; i<MXN; i++){
            E[i].clear();
            rE[i].clear();
        }
    }
    void add_edge(int u, int v){
        E[u].pb(v);
        rE[v].pb(u);
    }
    void DFS(int u){
        vst[u]=1;
        for (auto v : E[u])
        if (!vst[v]) DFS(v);
        vec.pb(u);
    }
    void rDFS(int u){
        vst[u] = 1;
        bln[u] = nScc;
        for (auto v : rE[u])
        if (!vst[v]) rDFS(v);
    }
    void solve(){
        nScc = 0;
        vec.clear();
        fill(vst,vst+n+1,0);
        for (int i=0; i<n; i++)
        if (!vst[i]) DFS(i);
        reverse(vec.begin(),vec.end());
        fill(vst,vst+n+1,0);
        for (auto v : vec){
            if (!vst[v]){
                rDFS(v);
                nScc++;
            }
        }
    }
}graph;
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    graph.init(2*n+5);
    for(int i = 0;i<m;i++){
        int x,y,t;
        scanf("%d %d %d",&x,&y,&t);
        if(t==1)
        graph.add_edge(x,y+n),graph.add_edge(y,x+n);
        if(t==2)
        graph.add_edge(x+n,y),graph.add_edge(y+n,x);
        if(t==3){
            graph.add_edge(x,y+n);
            graph.add_edge(y,x+n);
            graph.add_edge(y+n,x);
            graph.add_edge(x+n,y);
        }
        if(t==4){
            graph.add_edge(x+n,y+n);
            graph.add_edge(y+n,x+n);
            graph.add_edge(y,x);
            graph.add_edge(x,y);
        }
    }
    graph.solve();
    for(int i =1;i<=n;i++){
        if(graph.bln[i]==graph.bln[i+n]){
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    for(int i = 1;i<=n;i++){
        if(graph.bln[i]>graph.bln[i+n]){
            printf("0");
        }
        else{
            printf("1");
        }
    }
    printf("\n");
}