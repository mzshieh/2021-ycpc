#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;


int dp[100005];
int w[105];



int main()
{
    int cas;
    int n,u,m;

    scanf("%d",&cas);
    for(int T = 0; T < cas; T++){
        scanf("%d %d %d",&n,&u,&m);
        int sum = 0;
        memset(w,0,sizeof(w));
        for(int i = 0; i < n; i++){
            int tw;
            scanf("%d",&tw);
            w[tw]++;
            sum += tw;
        }
        if(sum > 100000) printf("sum is too big\n");
        memset(dp,0,sizeof(dp));
        for(int i = 1; i <= 100; i++){
            int aw = i;
            int nw = i * w[i];
            while(nw){
                nw -= aw;
                for(int j = sum; j - aw >= 0; j--){
                    if(dp[j - aw] >= 0){
                        dp[j] = max(dp[j], dp[j - aw] + aw);
                    }
                }
                aw += aw;
                if(aw > nw){
                    aw = nw;
                }
            }
        }
        int ans = 1000000007;
        for(int i = sum; i >= 0; i--){
            if(dp[i] >= 0){
                int opp = sum - dp[i];
                ans = min(ans,
                          max(dp[i] / u + ((dp[i] % u)? 1: 0),
                              opp / m + ((opp % m)? 1: 0)));
            }
        }
        printf("%d\n", ans);

    }
    return 0;
}
