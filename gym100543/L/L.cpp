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

const int N=605;
int a[N],b[N],d[N];
int t[N];
int dp[N][N];
void MAIN()
{
	int n;read(n);
	int pos=0;
	for(int i=1;i<=n;++i) read(a[i],b[i],d[i]),t[++pos]=a[i],t[++pos]=b[i];
	std::sort(t+1,t+pos+1),std::unique(t+1,t+pos+1);
	for(int i=1;i<=n;++i) a[i]=std::lower_bound(t+1,t+pos+1,a[i])-t,b[i]=std::lower_bound(t+1,t+pos+1,b[i])-t;
	for(int len=1;len<=pos;++len)
	{
		for(int i=1,j=len;j<=pos;++i,++j)
		{
			dp[i][j]=inf;
			int t=0;
			for(int k=1;k<=n;++k) if(a[k]>=i&&b[k]<=j&&d[k]>d[t]) t=k;
			if(!t) dp[i][j]=0;
			else for(int k=a[t];k<=b[t];++k) chmin(dp[i][j],dp[i][k-1]+d[t]+dp[k+1][j]);
		}
	}
	printf("%d\n",dp[1][pos]);
}
int main()
{
	int _;read(_);
	while(_--) MAIN();
	return 0;
}
