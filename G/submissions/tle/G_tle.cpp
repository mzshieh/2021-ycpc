#include<bits/stdc++.h>
#define pll pair<LL,LL>
#define LL long long
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define sqr(x) ((x)*(x))
#define pi acosl(-1)
using namespace std;
LL cross(pll p,pll q,pll r){
    p.x-=r.x;
    p.y-=r.y;
    q.x-=r.x;
    q.y-=r.y;
    return p.x*q.y-p.y*q.x;
}
double dis(pll p,pll q){
    return sqrt(sqr(p.x-q.x)+sqr(p.y-q.y));
}
double d[105][105];
int ok[105];
double mindis(int i,int j,int n){
    double mydis[105];
    int vis[105];
    fill(mydis,mydis+105,1e18);
    fill(vis,vis+105,0);
    mydis[j]=0;
    while(true){
        double Min=1e18;
        int Mini=-1;
        for(int k=0;k<n;k++){
            if(mydis[k]<Min&&!vis[k]&&ok[k]){
                Min=mydis[k];
                Mini=k;
            }
        }
        if(Mini==-1)break;
        vis[Mini]=1;
        for(int k = 0;k<n;k++){
            if(ok[k])
            mydis[k]=min(mydis[k],mydis[Mini]+d[Mini][k]);
        }
    }
    return mydis[i];
}
int main(){
    int n;
    scanf("%d",&n);
    pll p[505];
    for(int i = 0;i<n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        p[i]=mp(x,y);
    }
    vector<pll> v;
    int m;
    scanf("%d",&m);
    for(int i = 0;i<m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        v.pb(mp(x,y));
    }
    for(int i = 0;i<n;i++){
        long double tmp=atan2l(v[0].y-p[i].y,v[0].x-p[i].x);
        long double l=tmp-pi,r=tmp+pi;
        long double Max=tmp,Min=tmp;
        int Maxi=0,Mini=0;
        
        for(int j =0;j<m;j++){
            long double val=atan2l(v[j].y-p[i].y,v[j].x-p[i].x);
            if(val>r)val-=2*pi;
            if(val<l)val+=2*pi;
            if(val<Min)Min=val,Mini=j;
            if(val>Max)Max=val,Maxi=j;
        }
        for(int j = 0;j<n;j++){
            if(i==j){
                d[i][j]=1e18;
                continue;
            }
            int ok=1;
            for(auto it:v){
                if(cross(p[j],it,p[i])<=0)ok=0;
            }
            if(!ok)d[i][j]=1e18;
            else d[i][j]=dis(p[i],p[j]);
        }
    }
    for(int i =0;i<n;i++){
        double ans=1e18;
        for(int j = 0;j<n;j++){
            if(d[i][j]<1e15){
                for(int k = 0;k<n;k++){
                    if(k==i||k==j||cross(p[j],p[k],p[i])>0)ok[k]=1;
                    else ok[k]=0;
                }
                ans=min(ans,mindis(i,j,n)+d[i][j]);
            }
        }
        if(ans>1e15)printf("-1");
        else printf("%.12lf",ans);
        if(i==n-1)printf("\n");
        else printf(" ");
    }
}
