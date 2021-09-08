#include<algorithm>
#include<stdio.h>
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
    long long dis=9e18;
    for(int xx = x[n/2]-1;xx<=x[n/2]+1;xx++){
        for(int yy = y[n/2]-1;yy<=y[n/2]+1;yy++){
            if(abs(xx%2)!=abs(yy%2))continue;
 	    long long sum=0;
            for(int i = 0;i<n;i++){
                sum+=abs(xx-x[i]);
                sum+=abs(yy-y[i]);
            }
            dis=min(dis, sum);
        }
    }
    printf("%lld\n",dis/2);
}
