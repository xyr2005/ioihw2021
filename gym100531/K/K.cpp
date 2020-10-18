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

const int N=250005;
const int MAXN=1005;
const int mod=1000000007;
template<typename _Tp1,typename _Tp2>inline void add(_Tp1 &a,_Tp2 b){(a+=b)>=mod&&(a-=mod);}
template<typename _Tp1,typename _Tp2>inline void sub(_Tp1 &a,_Tp2 b){(a-=b)<0&&(a+=mod);}
int b[N],limit[N],end[N];
int dp[N][255];
int main()
{
	freopen("kebab.in","r",stdin);
	freopen("kebab.out","w",stdout);
	
	int n,t;read(n,t);
	int x,y,m=1;
	for(int i=1;i<=n;++i)
	{
		read(x,y);
		for(int j=0;j<x;++j) b[m+j]=i,limit[m+j]=x-y,end[m+j]=m+x;
		m+=x;
	}
	dp[0][0]=1,dp[1][0]=-1;
	for(int i=0;i<m;++i)
	{
		for(int j=0;j<=250;++j) add(dp[i+1][j],dp[i][j]);
		int k=!i?1:(i+t+1),fir=k;
		if(b[k]==b[i])
		{
			chmax(fir,end[k]);
			for(int j=0;j<limit[i];++j) add(dp[k][j+1],dp[i][j]),sub(dp[end[k]][j+1],dp[i][j]);
		}
		for(int j=0;j<=limit[i];++j) add(dp[fir][1],dp[i][j]);
	}
	int ans=0;
	for(int i=0;i<=m;++i) for(int j=0;j<=limit[i];++j) add(ans,dp[i][j]);
	printf("%d\n",ans);
	return 0;
}
