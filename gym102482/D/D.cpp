// Author -- xyr2005

#include<bits/stdc++.h>

#define lowbit(x) ((x)&(-(x)))
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
#define SZ(x) ((int)x.size())
#define mkpr std::make_pair
#define pb push_back

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pi;
typedef std::pair<ll,ll> pl;
using std::min;
using std::max;

const int inf=0x3f3f3f3f,Inf=0x7fffffff;
const ll INF=0x3f3f3f3f3f3f3f3f;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template <typename _Tp>_Tp gcd(const _Tp &a,const _Tp &b){return (!b)?a:gcd(b,a%b);}
template <typename _Tp>inline _Tp abs(const _Tp &a){return a>=0?a:-a;}
template <typename _Tp>inline void chmax(_Tp &a,const _Tp &b){(a<b)&&(a=b);}
template <typename _Tp>inline void chmin(_Tp &a,const _Tp &b){(b<a)&&(a=b);}
template <typename _Tp>inline void read(_Tp &x)
{
	char ch(getchar());bool f(false);while(!isdigit(ch)) f|=ch==45,ch=getchar();
	x=ch&15,ch=getchar();while(isdigit(ch)) x=(((x<<2)+x)<<1)+(ch&15),ch=getchar();
	f&&(x=-x);
}
template <typename _Tp,typename... Args>inline void read(_Tp &t,Args &...args){read(t);read(args...);}
inline int read_str(char *s)
{
	char ch(getchar());while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
	char *tar=s;*tar=ch,ch=getchar();while(ch!=' '&&ch!='\r'&&ch!='\n'&&ch!=EOF) *(++tar)=ch,ch=getchar();
	return tar-s+1;
}

const int N=505;
long double C[N][N],F[N][N],dp[N][N];
int main()
{
	for(int i=0;i<N;++i) for(int j=C[i][0]=1;j<=i;++j) C[i][j]=C[i-1][j-1]+C[i-1][j];
	int n,d,r;read(n,d,r);
	F[0][0]=1;
	for(int i=1;i<=n;++i)
	{
		for(int e=1;e*i<=d;++e)
		{
			int tmp=e*i;
			for(int j=tmp;j<=d;++j)
			{
				for(int k=0;k<i;++k)
				{
					dp[i][j]+=C[i][k]*(dp[k][j-tmp]+e*min(r,i)*F[k][j-tmp]);
					F[i][j]+=C[i][k]*F[k][j-tmp];
				}
			}
		}
	}
	long double A=0,B=0;
	for(int i=1;i<=n;++i) A+=C[n][i]*dp[i][d],B+=C[n][i]*F[i][d];
	printf("%.8Lf\n",A/B+r);
	return 0;
}
