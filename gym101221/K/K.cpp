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

const int N=2000005;
int nxt[N],f[N][21];
int main()
{
	int n,k;read(n,k);
	int x,y;
	for(int i=1;i<=n+n;++i) nxt[i]=i;
	for(int i=1;i<=k;++i)
	{
		read(x,y);
		if(y<x) y+=n;
		chmax(nxt[x],y+1);
		x+=n,y+=n,chmin(y,n+n);
		chmax(nxt[x],y+1);
	}
	for(int i=1;i<=n+n;++i) chmax(nxt[i],nxt[i-1]);
	nxt[n+n+1]=n+n+1;
	for(int i=n+n+1;i>=1;--i)
	{
		f[i][0]=nxt[i];
		for(int j=1;j<=20&&i+(1<<(j-1))<=n+n+1;++j) f[i][j]=f[f[i][j-1]][j-1];
	}
	int res=inf;
	for(int i=1;i<=n;++i)
	{
		int cur=i,ans=0;
		for(int j=20;j>=0;--j) if(f[cur][j]&&f[cur][j]<i+n) cur=f[cur][j],ans|=1<<j;
		if(nxt[cur]>=i+n) chmin(res,ans+1);
	}
	if(res>=inf) puts("impossible");
	else printf("%d\n",res);
	return 0;
}
