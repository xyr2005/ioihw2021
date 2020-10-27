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

const int N=30005;
int a[N],b[N],c[N],n,r;
ll sb[N],sc[N],A[N],B[N],t[N];
struct BIT{
	int c[N];
	void add(int x,int C){for(;x<N;x+=lowbit(x))c[x]+=C;}
	int sum(int x){int ans=0;for(;x;x-=lowbit(x))ans+=c[x];return ans;}
}tr;
ll calc(ll mid)
{
	memset(tr.c,0,sizeof(tr.c));
	ll ans=0;int pos=0;
	for(int i=r;i<=n;++i) A[i]=sb[i]-sb[i-r];
	for(int i=1;i<=n-r+1;++i) B[i]=sb[i+r-1]-sb[i-1],t[++pos]=B[i];
	std::sort(t+1,t+pos+1),pos=std::unique(t+1,t+pos+1)-t-1;
	for(int i=n-r+1;i>=r;--i)
	{
		ans+=tr.sum(std::upper_bound(t+1,t+pos+1,mid-A[i])-t-1);
		tr.add(std::lower_bound(t+1,t+pos+1,B[i])-t,1);
	}
	memset(tr.c,0,sizeof(tr.c));
	pos=0;
	for(int i=1;i<=n-r+1;++i) A[i]=sc[i+r-1]-sb[i-1],B[i]=sb[i+r-1]-sc[i-1],t[++pos]=B[i];
	std::sort(t+1,t+pos+1),pos=std::unique(t+1,t+pos+1)-t-1;
	for(int i=1;i<=n-r+1;++i) B[i]=std::lower_bound(t+1,t+pos+1,B[i])-t;
	for(int i=1;i<r;++i) if(i<=n-r+1) tr.add(B[i],1);
	for(int i=1;i<=n-r+1;++i)
	{
		tr.add(B[i],-1);
		if(i+r-1<=n-r+1) tr.add(B[i+r-1],1);
		ans+=tr.sum(std::upper_bound(t+1,t+pos+1,mid-A[i])-t-1);
	}
	return ans;
}
int main()
{
	ll k;read(n,r,k);
	ll sum=0;
	for(int i=1;i<=n;++i) read(a[i]),sum+=a[i];
	for(int i=1;i<=n;++i) read(b[i]);
	for(int i=1;i<=n;++i) read(c[i]);
	for(int i=1;i<=n;++i) c[i]-=b[i],b[i]-=a[i];
	for(int i=1;i<=n;++i) sb[i]=sb[i-1]+b[i],sc[i]=sc[i-1]+c[i];
	ll l=0,r=1e11;
	while(l<r)
	{
		ll mid=(l+r)>>1;
		if(calc(mid)>=k) r=mid;
		else l=mid+1;
	}
	printf("%lld\n",l+sum);
	return 0;
}

