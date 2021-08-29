#include <stdio.h>
#include <string.h>

typedef long long ll;

const ll M = 1000000007;

int RW, WR, R, W;

// 0 is forward, 1 is backward
// 0 is R, 1 is W
int edge[2][2][1005];
int vis[2][1005];

int go(int way, int color, int pos)
{
    if(vis[color][pos] == 1) return -1;
    vis[color][pos] = 1;
    if(edge[way][color][pos] != 0){
        return go(way, 1 - color, edge[way][color][pos]);
    }
    return color;
}

ll power(ll a, ll p)
{
    ll ret = 1;
    while(p){
        if(p&1)
            ret = ret * a % M;
        a = a * a % M;
        p >>= 1;
    }
    return ret;
}

ll inv(ll a)
{
    return power(a, M-2);
}

ll fac(ll f)
{
    return f == 0 ? 1: f * fac(f-1) % M;
}

ll com(ll a, ll b)
{
    return fac(a) * inv(fac(a-b)) % M * inv(fac(b)) % M;
}

int min3(int a, int b, int c)
{
    int ret = a < b ? a: b;
    return c < ret ? c: ret;
}

int main()
{
    int cas;
    int n,m,u,v;
    char team[10];
    int ans;

    scanf("%d",&cas);
    for(int T = 0; T < cas; T++){
        scanf("%d %d", &n, &m);
        memset(edge, 0, sizeof(edge));
        for(int i = 0; i < m; i++){
            scanf("%s %d %d", team, &u, &v);
            edge[0][team[0] != 'R'][u] = v;
            edge[1][team[0] == 'R'][v] = u;
        }
        if(m == 2 * n){
            if(go(0,0,1) == -1){
                printf("1\n");
            }else{
                printf("0\n");
            }
            continue;
        }
        RW = WR = R = W = 0;
        ans = 0;
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < 2; j++){
                if(vis[j][i] == 0){
                    int tail = go(0,j,i);
                    if(tail == -1) ans = -1;
                    vis[j][i] = 0;
                    int head = go(1,j,i);
                    if(tail == 0){
                        if(tail == head) R++;
                        else WR++;
                    }else{
                        if(tail == head) W++;
                        else RW++;
                    }
                }
            }
        }
        if(ans == -1){
            printf("0\n");
            continue;
        }
        if(R != W){
            printf("something is wrong\n");
            printf("%d %d %d %d\n",RW, WR, R, W);
            continue;
        }
        if(R == 0 && RW > 0 && WR > 0){
            printf("0\n");
            continue;
        }
        if(RW == 0 && WR == 0){
            printf("%d\n", int( fac(W) * fac(R-1) % M));
        }else{
            if(RW == 0){
                RW = WR;
                WR = 0;
            }
            if(R == 0){
                ans = 1;
            }else if(WR == 0){
                ans = com(RW-1+R,R);
            }else{
                ans = 0;
                for(int i = min3(RW, WR, R); i >= 1; i--){
                    ll temp = com(RW, i) * com(WR-1,i-1) % M;
                    temp = temp * com(WR+RW-1+R-i,R-i) % M;
                    ans = (ans + temp) % M;
                }
            }
            //printf("%d\n", int(ans));
            ans = ans * fac(R) % M;
            ans = ans * fac(R) % M;
            ans = ans * fac(WR) % M;
            ans = ans * fac(RW-1) % M;
            printf("%d\n", int(ans));
        }

    }
    return 0;
}
