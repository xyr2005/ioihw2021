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

const int N=100005;
int n,a[N],L[N],R[N],st[N],top,val[N];
ll k,sum[N];
inline ll f(int x){return 1ll*x*(x+1)>>1;}
bool check(int MID)
{
	for(int i=1;i<=n;++i) if(a[i]>=MID) return true;
	st[top=0]=0;
	for(int i=1;i<=n;++i)
	{
		int l=0,r=top;
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			if(val[st[mid]]>=MID-i) l=mid;
			else r=mid-1;
		}
		L[i]=st[l],val[i]=a[i]-i;
		while(top&&val[i]>=val[st[top]]) --top;
		st[++top]=i;
	}
	st[top=0]=n+1;
	for(int i=n;i>=1;--i)
	{
		int l=0,r=top;
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			if(val[st[mid]]>=MID+i) l=mid;
			else r=mid-1;
		}
		R[i]=st[l],val[i]=a[i]+i;
		while(top&&val[i]>=val[st[top]]) --top;
		st[++top]=i;
	}
	for(int i=1;i<=n;++i)
	{
		if((L[i]==0&&MID>a[1]+i-1)||(R[i]==n+1&&MID>a[n]+n-i)) continue;
		ll cost=1ll*MID*(R[i]-L[i]-1)-f(i-L[i]-1)-f(R[i]-i-1)-(sum[R[i]-1]-sum[L[i]]);
		if(cost<=k) return true;
	}
	return false;
}
int main()
{
	freopen("landscape.in","r",stdin);
	freopen("landscape.out","w",stdout);
	
	read(n,k);
	for(int i=1;i<=n;++i) read(a[i]),sum[i]=sum[i-1]+a[i];
	int l=1,r=1001000000;
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	printf("%d\n",l);
	return 0;
}

