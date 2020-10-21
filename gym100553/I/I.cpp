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

const int N=200005;
int a[N];
struct BIT{
	int c[N];
	void add(int x,int C){for(;x<N;x+=lowbit(x))chmax(c[x],C);}
	int sum(int x){int ans=0;for(;x;x-=lowbit(x))chmax(ans,c[x]);return ans;}
}tr1,tr2;
int dp1[N],dp2[N];
int main()
{
	freopen("improvements.in","r",stdin);
	freopen("improvements.out","w",stdout);
	
	int n;read(n);
	int x;
	for(int i=1;i<=n;++i) read(x),a[x]=i;
	for(int i=1;i<=n;++i)
	{
		dp1[i]=tr1.sum(a[i])+1;
		tr1.add(a[i],dp1[i]);
		chmax(dp1[i],dp1[i-1]);
	}
	for(int i=n;i>=1;--i)
	{
		dp2[i]=tr2.sum(a[i])+1;
		tr2.add(a[i],dp2[i]);
		chmax(dp2[i],dp2[i+1]);
	}
	int ans=0;
	for(int i=1;i<=n;++i) chmax(ans,dp1[i]+dp2[i+1]);
	printf("%d\n",ans);
	return 0;
}

