#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1024;

struct SOL
{
	vector<vector<bool>> win, a, b;

	SOL() : win(N, vector<bool>(N, false)), a(win), b(win)
	{
		for(int L4=0; L4<=6; L4++)
			for(int L3=0; L3<=6-L4; L3++)
				for(int R4=0; R4<=4; R4++)
					for(int R3=0; R3<=4-R4; R3++)
						for(int R2=0; R2<=4-R4-R3; R2++)
						{
							int L2=6-L4-L3;
							int Lm=4*(L4+L3+L2)+R3+R2+R2;
							int Rm=4*(R4+R3+R2)+L3+L2+L2;
							win[Lm][Rm]=true;

							if( L2 || R2 )
								a[Lm][Rm]=true;

							if( R4+R3+R2==4 )
								b[Lm][Rm]=true;
						}

		for(int i=0; i<=1000; i++)
			for(int j=0; j<=1000; j++)
			{
				if( !win[i][j] )
					continue;

				if( a[i][j] )
				{
					win[i+1][j+1]=true;
					a[i+1][j+1]=true;
				}

				if( b[i][j] )
				{
					for(int l=0; l<=2; l++)
						for(int r=0; r<=2; r++)
						{
							win[i+l+4][j+r+4]=true;
							b[i+l+4][j+r+4]=true;

							if( a[i][j] || l==2 || r==2 )
								a[i+l+4][j+r+4]=true;
						}
				}
			}
	}

	bool operator()(int l, int r) const
	{
		return win[l][r];
	}
} solve;

int main()
{
	int n;

	for(scanf("%d", &n); n>0; n--)
	{
		int l, r;
		scanf("%d-%d", &l, &r);
		printf(solve(l, r) ? "YES\n" : "NO\n");
	}
}
