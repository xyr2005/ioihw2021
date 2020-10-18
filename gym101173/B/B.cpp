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

const int N=25;
int v1[1<<20],v2[1<<20];
int w1[1<<20],w2[1<<20];
int cnt[1<<20],a[1<<20],b[1<<20];
int main()
{
	for(int i=1;i<1<<20;++i) cnt[i]=cnt[i>>1]+(i&1);
	int n,m;read(n,m);
	char ch;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)
		{
			ch=getchar();
			while(ch!='0'&&ch!='1') ch=getchar();
			if(ch=='1') v1[1<<i]|=1<<j,v2[1<<j]|=1<<i;
		}
	}
	int x;
	for(int i=0;i<n;++i) read(x),w1[1<<i]=x;
	for(int i=0;i<m;++i) read(x),w2[1<<i]=x;
	int p1=0,p2=0;
	for(int st=0;st<1<<n;++st)
	{
		v1[st]=v1[lowbit(st)]|v1[st^lowbit(st)],w1[st]=w1[lowbit(st)]+w1[st^lowbit(st)];
		for(int i=0;i<n;++i) if(((st>>i)&1)&&w1[st^(1<<i)]<0) w1[st]=-inf;
		if(cnt[v1[st]]>=cnt[st]&&w1[st]>=0) a[p1++]=w1[st];
		else w1[st]=-inf;
	}
	for(int st=0;st<1<<m;++st)
	{
		v2[st]=v2[lowbit(st)]|v2[st^lowbit(st)],w2[st]=w2[lowbit(st)]+w2[st^lowbit(st)];
		for(int i=0;i<m;++i) if(((st>>i)&1)&&w2[st^(1<<i)]<0) w2[st]=-inf;
		if(cnt[v2[st]]>=cnt[st]&&w2[st]>=0) b[p2++]=w2[st];
		else w2[st]=-inf;
	}
	std::sort(a,a+p1),std::sort(b,b+p2,std::greater<int>());
	ll ans=0;
	int pos=0;
	int t;read(t);
	for(int i=0;i<p1;++i)
	{
		while(pos<p2&&a[i]+b[pos]>=t) ++pos;
		ans+=pos;
	}
	printf("%lld\n",ans);
	return 0;
}
