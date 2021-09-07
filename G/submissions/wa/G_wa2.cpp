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
vector<pll> convex(vector<pll> v){
    sort(v.begin(),v.end());
    vector<pll> ans;
    ans.pb(v[0]);
    int k=0;
    for(int tt=0;tt<2;tt++){
        for(int i = 1;i<v.size();i++){
            while(ans.size()-1!=k&&cross(ans.back(),v[i],ans[ans.size()-2])<=0)
                ans.pop_back();
            ans.pb(v[i]); 
        }
        k=ans.size()-1;
        reverse(v.begin(),v.end());
    }
    ans.pop_back();
    return ans;
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
    v=convex(v);
    m=v.size();
    for(int i = 0;i<n;i++){
        LL sum1=0,sum2=0;
        for(int j = 0;j<m;j++){
            sum1+=cross(v[j],v[(j+1)%m],p[i]);
            sum2+=abs(cross(v[j],v[(j+1)%m],p[i]));
        }
        if(abs(sum1)==abs(sum2)&&v.size()){
            for(int j =0;j<n;j++)d[i][j]=1e18;
            continue;
        }
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
            }
            else if(cross(p[j],v[Maxi],p[i])>0&&cross(p[j],v[Mini],p[i])>0){
                d[i][j]=dis(p[i],p[j]);
            }
            else{
                d[i][j]=1e18;
            }
        }
    }
    for(int i =0;i<n;i++){
        double ans=1e18;
        for(int j = 0;j<n;j++){
            if(d[i][j]<1e15){
                for(int k = 0;k<n;k++){
                    if(k==i||k==j||cross(p[j],p[k],p[i])>0){
                        ok[k]=1;
                    }
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
