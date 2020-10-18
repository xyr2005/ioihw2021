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
int a[N],b[N],c[N],d[N];
std::vector<int> e[N];
int _q[N],_l,_r;
bool vis[N];
int pos[N],ans[N];
int main()
{
	freopen("insider.in","r",stdin);
	freopen("insider.out","w",stdout);
	
	int n,m;read(n,m);
	for(int i=1;i<=m;++i)
	{
		read(a[i],b[i],c[i]);
		e[a[i]].pb(i),e[b[i]].pb(i),e[c[i]].pb(i);
		++d[b[i]];
	}
	_l=1,_r=0;
	for(int i=1;i<=n;++i) if(!d[i]) _q[++_r]=i;
	while(_l!=_r+1)
	{
		int x=_q[_l++];
		for(auto v:e[x]) if(!vis[v]&&!--d[b[v]]) _q[++_r]=b[v],vis[v]=true;
	}
	memset(vis,0,sizeof(vis));
	int l=0,r=1;
	for(int i=n;i>=1;--i)
	{
		int x=_q[i];
		vis[x]=true;
		int c1=0,c2=0;
		for(auto v:e[x])
		{
			if(!vis[a[v]]||!vis[b[v]]||!vis[c[v]]) continue;
			if(pos[a[v]^x^c[v]]<pos[b[v]]) ++c2;
			else ++c1;
		}
		if(c1>=c2) pos[x]=l--;
		else pos[x]=r++;
	}
	for(int i=1;i<=n;++i) ans[pos[i]-l]=i;
	for(int i=1;i<=n;++i) printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
