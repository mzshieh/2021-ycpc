#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    int ans=0,now=80;
    for(int i = 0;i<n;i++){
        char c[105];
        scanf("%s",c);
        int len=strlen(c);
        if(now+len+1>80)now=len,ans++;
        else now+=len+1;
    }
    printf("%d\n",ans);
}