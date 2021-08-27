#include<bits/stdc++.h>
#define LL long long
#define x first
#define y second
using namespace std;
int root=3,MAXNUM=1<<23;
int mod=998244353;
int bigmod(long long a,int b){
	if(b==0)return 1;
	return (bigmod((a*a)%mod,b/2)*(b%2?a:1ll))%mod;
}
int inv(int a,int b){
	if(a==1)return 1;
	return (((long long)(a-inv(b%a,a))*b+1)/a)%b;
}
std::vector<long long> ps(MAXNUM);
std::vector<int> rev(MAXNUM);
LL f_pow(unsigned int a,LL b){
    LL res=1,temp=a;
    while(b){
        if(b&1)res=res*temp%mod;
        temp=temp*temp%mod;
        b>>=1;
    }
    return res;
}
struct poly{
	std::vector<unsigned int> co;
	int n;//polynomial degree = n
	poly(int d){n=d;co.resize(n+1,0);}
	void ntt(int NN){
		int r=0,st,N;
		unsigned int a,b;
		r=0;
        for(N=NN;N>1;N>>=1,r++){
			for(st=0;st<NN;st+=N){
				int i,ss=st+(N>>1);
				for(i=(N>>1)-1;i>=0;--i){
					a=co[st+i]; b=co[ss+i];
					co[st+i]=a+b; if(co[st+i]>=mod)co[st+i]-=mod;
                    co[ss+i]=((a+mod-b)*ps[i<<r])%mod;
				}
			}
		}
	}
	void ntt_inv(int NN){
        int r=0,st,N;
		unsigned int a,b;
		while((1<<r)<(NN>>1))++r;
		for(N=2;N<=NN;N<<=1,--r){
			for(st=0;st<NN;st+=N){
				int i,ss=st+(N>>1);
				for(i=(N>>1)-1;i>=0;--i){
					a=co[st+i]; b=(ps[i<<r]*co[ss+i])%mod;;
					co[st+i]=a+b; if(co[st+i]>=mod)co[st+i]-=mod;
					co[ss+i]=a+mod-b; if(co[ss+i]>=mod)co[ss+i]-=mod;
				}
			}
		}
	}
    poly operator*(const poly& _b)const{
		poly a=*this,b=_b;
		int k=n+b.n,i,N=1;
		while(N<=k)N*=2;
		a.co.resize(N,0); b.co.resize(N,0);
		int r=bigmod(root,(mod-1)/N),Ni=inv(N,mod);
		ps[0]=1;
		for(i=1;i<N;++i)ps[i]=(ps[i-1]*r)%mod;
		a.ntt(N);b.ntt(N);
		for(i=0;i<N;++i)a.co[i]=((long long)a.co[i]*b.co[i])%mod;
		r=inv(r,mod);
		for(i=1;i<N/2;++i)std::swap(ps[i],ps[N-i]);
		a.ntt_inv(N);
		for(i=0;i<N;++i)a.co[i]=((long long)a.co[i]*Ni)%mod;
		a.n=n+_b.n; return a;
	}
};
bool operator<(const poly &a,const poly &b){
    return a.n<b.n;
}
bool operator>(const poly &a,const poly &b){
    return a.n>b.n;
}
int dp[455][100005];
int w[100005];
int main(){
    int n;
    scanf("%d",&n);
    priority_queue<poly,vector<poly>,greater<poly> >pq;
    map<int,int> m;
    for(int i = 1;i<=n;i++){
        scanf("%d",&w[i]);
        poly p(w[i]);
        p.co[w[i]]=1;
        p.co[0]=1;
        pq.push(p);
        m[w[i]];
    }
    while(pq.size()>1){
        poly p = pq.top();
        pq.pop();
        poly q = pq.top();
        pq.pop();
        pq.push(p*q);
    }

    poly p = pq.top();
    //for(int i = 0;i<=p.n;i++)dp[i]=p.co[i];
    int Index=0;
    for(auto &it:m)it.y=++Index;
    for(auto it:m){
        for(int i=0;i<=p.n;i++){
            dp[it.y][i]=p.co[i];
        }
        for(int i=0;i+it.x<=p.n;i++){
            dp[it.y][i+it.x]-=dp[it.y][i];
            dp[it.y][i+it.x]=(dp[it.y][i+it.x]+mod)%mod;
        }
    }
    int q;
    scanf("%d",&q);
    while(q--){
        int x,W;
        scanf("%d %d",&x,&W);
        if (W>100000) puts("0"); else printf("%d\n",dp[m[w[x]]][W]);
    }
}
