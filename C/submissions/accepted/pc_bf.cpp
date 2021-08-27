#include <stdio.h>
#include <string.h>
#include <time.h>

#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

const ll M = 1000000007;

typedef pair<int,int> pii;

struct redge
{
    pii start,end;
    int avail;
    int prev,next;
};

redge RW[2000],WR[2000],R[2000],W[2000];
int RW_s, WR_s, R_s, W_s;

// 0 is forward, 1 is backward
// 0 is R, 1 is W
int edge[2][2][1005];
int vis[2][1005];

int go(int way, int color, int pos, pii *pe)
{
    pe->first = color;
    pe->second = pos;
    if(vis[color][pos] == 1) return -1;
    vis[color][pos] = 1;
    if(edge[way][color][pos] != 0){
        return go(way, 1 - color, edge[way][color][pos], pe);
    }
    return color;
}

void remove(redge link[], int pos)
{
    link[pos].avail = 0;
    link[link[pos].prev].next = link[pos].next;
    link[link[pos].next].prev = link[pos].prev;
}
void add(redge link[], int pos)
{
    link[pos].avail = 1;
    link[link[pos].prev].next = pos;
    link[link[pos].next].prev = pos;
}


ll bf(pii now);

// default to enumerate.
#define NOT_ENUMERATE

ll try_type(redge link[], int &link_s)
{
    pii start, end;
    ll ans = 0;
#ifndef NOT_ENUMERATE
    for(int i = 0; ; ){
        i = link[i].next;
        if(link[i].avail == 0) break;
#else
    { int i = 0;
        i = link[i].next;
#endif
        start = link[i].start;
        end = link[i].end;
        remove(link,i);
        link_s--;

        ans += bf(end);

        add(link, i);
        link_s++;
    }
#ifndef NOT_ENUMERATE
    return ans;
#else
    return ans * (link_s-1) % M;
#endif
}

ll bf(pii now)
{
    ll ans = 0;
    int touch = 0;
    if(now.first == 0){
        if(WR_s > 1){
            ans += try_type(WR,WR_s);
            touch = 1;
        }
        ans = ans % M;
        if(W_s > 1 && (R_s > 1 || WR_s == 1)){
            ans += try_type(W,W_s);
            touch = 1;
        }
        ans = ans % M;
    }else{
        if(RW_s > 1){
            ans += try_type(RW,RW_s);
            touch = 1;
        }
        ans = ans % M;
        if(R_s > 1 && (W_s > 1 || RW_s == 1)){
            ans += try_type(R,R_s);
            touch = 1;
        }
        ans = ans % M;
    }
    if(touch == 0) return 1;
    return ans;
}

int main()
{
    int cas;
    int n,m,u,v;
    char team[10];
    int ans;

    scanf("%d",&cas);
    int start_t = clock();
    for(int T = 0; T < cas; T++){
        //fprintf(stderr, "%d\n",T);
        scanf("%d %d", &n, &m);
        memset(edge, 0, sizeof(edge));
        for(int i = 0; i < m; i++){
            scanf("%s %d %d", team, &u, &v);
            edge[0][team[0] != 'R'][u] = v;
            edge[1][team[0] == 'R'][v] = u;
        }
        if(m == 2 * n){
            pii tmp;
            if(go(0,0,1, &tmp) == -1){
                printf("1\n");
            }else{
                printf("0\n");
            }
            continue;
        }
        memset(RW,0,sizeof(RW));
        memset(WR,0,sizeof(WR));
        memset(R,0,sizeof(R));
        memset(W,0,sizeof(W));
        RW_s = WR_s = R_s = W_s = 1;
        ans = 0;
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < 2; j++){
                if(vis[j][i] == 0){
                    pii pu,pv;
                    int tail = go(0,j,i, &pv);
                    if(tail == -1) ans = -1;
                    vis[j][i] = 0;
                    int head = go(1,j,i, &pu);
                    //printf("%d %d %d %d %d %d\n",j,i,pu.first, pu.second,pv.first,pv.second);
                    if(tail == 0){
                        if(tail == head){
                            R[R_s] = redge{pu,pv,1,R_s-1,R_s+1};
                            R_s++;
                        }else{
                            WR[WR_s] = redge{pu,pv,1,WR_s-1,WR_s+1};
                            WR_s++;
                        }
                    }else{
                        if(tail == head){
                            W[W_s] = redge{pu,pv,1,W_s-1,W_s+1};
                            W_s++;
                        }else{
                            RW[RW_s] = redge{pu,pv,1,RW_s-1,RW_s+1};
                            RW_s++;
                        }
                    }
                }
            }
        }
        R[0].next = 1;
        RW[0].next = 1;
        W[0].next = 1;
        WR[0].next = 1;
        if(ans == -1){
            printf("0\n");
            continue;
        }

        if(R_s != W_s){
            printf("something is wrong\n");
            continue;
        }

        if(R_s == 1 && RW_s > 1 && WR_s > 1){
            printf("0\n");
            continue;
        }
        pii start;
        if(RW_s != 1){
            start = RW[1].end;
            remove(RW, 1);
            RW_s--;

        }else if(WR_s != 1){
            start = WR[1].end;
            remove(WR, 1);
            WR_s--;
        }else{
            start = R[1].end;
            remove(R, 1);
            R_s--;
        }
        ll ans_ll = bf(start);
        printf("%I64d\n", ans_ll);
    }
    fprintf(stderr,"%f\n",(clock() - start_t)*1./CLOCKS_PER_SEC);
    return 0;
}
