#include<bits/stdc++.h>
#define y second
using namespace std;
int dp[500005][5][5][2];
int a[150005];
int cnt[500005];
int main(){
    int n;
    scanf("%d",&n);
    map<int,int> m;
    for(int i = 0;i<3*n+2;i++){
        scanf("%d",&a[i]);
        m[a[i]];
        m[a[i]+1];
        m[a[i]-1];
    }
    int Index=0;
    for(auto &it:m){
        it.y=++Index;
    }
    for(int i = 0;i<3*n+2;i++){
        cnt[m[a[i]]]++;
    }

    dp[0][0][0][0]=1;
    for(int i = 1;i<=Index;i++){
        for(int j = 0;j<5&&j<=cnt[i];j++){
            for(int k = 0;k<5;k++){
                int less=cnt[i]-j;
                for(int t=0;t<2;t++){
                    /*if(dp[i-1][j][k][t]){
                        printf("%d %d %d %d %d\n",i-1,j,k,t,less);
                    }*/
                    if(j==cnt[i]){
                        dp[i][k][0][t]|=dp[i-1][j][k][t];
                    }
                    else{
                    
                        if(less==1){
                            if(k+1<=4){
                                dp[i][k+1][1][t]|=dp[i-1][j][k][t];
                            }
                        }
                        else if(less==2){
                            if(k+2<=4){
                                dp[i][k+2][2][t]|=dp[i-1][j][k][t];
                            }
                        }
                        else if(less==3){
                            if(k+3<=4){
                                dp[i][k+3][3][t]|=dp[i-1][j][k][t];
                            }
                            dp[i][k][0][t]|=dp[i-1][j][k][t];
                        }
                        else{
                            if(k+4<=4){
                                dp[i][k+3][3][t]|=dp[i-1][j][k][t];
                            }
                            if(k+1<=4){
                                dp[i][k+1][1][t]|=dp[i-1][j][k][t];
                            }
                        }
                    }
                }
                if(less==2){
                    dp[i][k][0][1]|=dp[i-1][j][k][0];
                }
                else if(less==3){
                    if(k+1<=4){
                        dp[i][k+1][1][1]|=dp[i-1][j][k][0];
                    }
                }
                else if(less==4){
                    if(k+2<=4){
                        dp[i][k+2][2][1]|=dp[i-1][j][k][0];
                    }
                }
            }
        }
    }
    if(dp[Index][0][0][1])printf("YES\n");
    else printf("NO\n");
}
