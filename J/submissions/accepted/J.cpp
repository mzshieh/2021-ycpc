#include<cstdio>
#include<algorithm>
using namespace std;
int a[100100][2];

int main()
{
	int n, ans=0;
	scanf("%d", &n);

	for(int i=0; i<n ; i++)
		scanf("%d%d", &a[i][0], &a[i][1]);

	for(int p=0; p<n; ans++)
	{
		int np=p, q, r;

		for(int i=0; i<2; i++)
		{
			for(q=p; q<n && (a[q][0]==a[p][i] || a[q][1]==a[p][i]); q++);

			for(int j=0; j<2; j++)
			{
				for(r=q; r<n && (a[r][0]==a[p][i] || a[r][1]==a[p][i] || a[r][0]==a[q][j] || a[r][1]==a[q][j]); r++);
				np=max(np, r);
			}
		}

		p=np;
	}

	printf("%d\n", ans);
}
