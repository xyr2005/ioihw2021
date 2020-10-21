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
struct node{
	ll x,y;
}a[N];
inline node operator - (const node &a,const node &b)
{
	return (node){a.x-b.x,a.y-b.y};
}
inline ll cross(const node &a,const node &b)
{
	return a.x*b.y-a.y*b.x;
}
int n;
ll calc()
{
	ll ans=0;
	for(int i=2;i<n;++i) ans+=cross(a[i]-a[1],a[i+1]-a[1]);
	return ans;
}
ll sum[N];
ll cnt[2][2][2];
int main()
{
	freopen("integral.in","r",stdin);
	freopen("integral.out","w",stdout);
	
	read(n);
	for(int i=1;i<=n;++i)
	{
		read(a[i].x,a[i].y);
		a[i].x=(a[i].x%2+2)%2;
		a[i].y=(a[i].y%2+2)%2;
	}
	ll qwq=calc();
	if(qwq%2)
	{
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;++i)
	{
		sum[i]=cross(a[i-1],a[i])+sum[i-1];
		sum[i]=(sum[i]%2+2)%2;
	}
	ll ans=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<2;++j) for(int k=0;k<2;++k) for(int t=0;t<2;++t) if(!((sum[i]^j)^(k&&a[i].x)^(t&&a[i].y))) ans+=cnt[j][k][t];
		++cnt[sum[i]][a[i].y][a[i].x];
	}
	printf("%lld\n",ans-n);
	return 0;
}

