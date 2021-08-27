#include<bits/stdc++.h>
using namespace std;
long long x[2000005],y[2000005];
int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        x[i]=a+b;
        y[i]=a-b;
    }
    sort(x,x+n);
    sort(y,y+n);
    long long dis=0;
    for(int i = 0;i<n;i++){
        dis+=abs(x[n/2]-x[i]);
        dis+=abs(y[n/2]-y[i]);
    }
    printf("%lld\n",dis/2);
}