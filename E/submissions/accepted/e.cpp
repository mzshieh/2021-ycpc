#include<bits/stdc++.h>
#define LL long long
using namespace std;
int f[205];
void KMP(char *c){
    int j = -1;
    f[0]=j;
    for(int i = 1;c[i]!=0;i++){
        while(c[i]!=c[j+1]&&j!=-1)j=f[j];
        if(c[i]==c[j+1]){
            j++;
        }
        f[i]=j;
    }
}
struct matrix{
    int a[205][205];
    int n;
    matrix(){
        memset(a,0,sizeof(a));
    }
};
int mod=998244353;
matrix operator*(const matrix &a,const matrix &b){
    matrix c;
    c.n=a.n;
    int n=a.n;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            for(int k=0;k<n;k++){
                c.a[i][j]+=a.a[i][k]*1ll*b.a[k][j]%mod;
                c.a[i][j]%=mod;
            }
        }
    }
    return c;
}
matrix f_pow(matrix a,int b){
    matrix temp=a,res;
    res.n=a.n;
    for(int i = 0;i<a.n;i++){
        res.a[i][i]=1;
    }
    while(b){
        if(b&1)res=res*temp;
        temp=temp*temp;
        b>>=1;
    }
    return res;
}
LL f_pow(int a,int b){
    LL res=1,tmp=a;
    while(b){
        if(b&1)res=res*tmp%mod;
        tmp=tmp*tmp%mod;
        b>>=1;
    }
    return res;
}
int main(){
    char c[205];
    int x;
    scanf("%s %d",c,&x);
    KMP(c);
    matrix a;
    a.n=strlen(c);
    int n=strlen(c);
    for(int i = 0;c[i]!=0;i++){
        for(int j=0;j<26;j++){
            int tmp=i-1;
            while(c[tmp+1]!=j+'a'&&tmp!=-1)tmp=f[tmp];
            if(c[tmp+1]==j+'a')tmp++;
            if(tmp!=n-1)
            a.a[tmp+1][i]++;
        }
    }
    matrix ans=f_pow(a,x);
    LL sum=0;
    for(int i = 0;i<n;i++)sum+=ans.a[i][0];
    printf("%lld\n",((f_pow(26,x)-sum)%mod+mod)%mod);
}
