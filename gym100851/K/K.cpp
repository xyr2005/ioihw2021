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

const int N=100025;
std::vector<int> nd[N],e[N],_[N];
int in[N],out[N],rev[N],fa[N],E[N][2],bel[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
bool vis[N];
int cnt,dfn[N],id;
std::vector<int> path;
void $(int x)
{
	if(vis[x]) return;
	vis[x]=true,dfn[x]=++id;
	for(auto v:e[x]) $(v);
}
void dfs(int x)
{
	if(vis[x])
	{
		if(x==1&&SZ(path)==cnt)
		{
			for(auto it:path) for(auto $:nd[it]) printf("%d ",$);
			printf("1\n");
			exit(0);
		}
		return;
	}
	vis[x]=true,path.pb(x);
	for(auto v:_[x]) dfs(v);
	vis[x]=false,path.pop_back();
}
int __[N];
int ____(int x){return __[x]==x?x:__[x]=____(__[x]);}
int main()
{
	freopen("king.in","r",stdin);
	freopen("king.out","w",stdout);
	
	int n,m;read(n,m);
	int x,y;
	for(int i=1;i<=n;++i) fa[i]=__[i]=i;
	for(int i=1;i<=m;++i) read(x,y),e[x].pb(y),++in[y],++out[x],rev[y]=x,E[i][0]=x,E[i][1]=y,__[____(x)]=____(y);
	int ___=0;for(int i=1;i<=n;++i) if(__[i]==i) ++___;
	if(___!=1)return puts("There is no route, Karl!"),0;
	for(int i=2;i<=n;++i) if(in[i]==1&&out[i]<=1&&in[rev[i]]==1&&out[rev[i]]==1) fa[find(i)]=find(rev[i]);
	for(int i=1;i<=n;++i) if(!bel[find(i)]) bel[find(i)]=++cnt;
	for(int i=1;i<=n;++i) bel[i]=bel[find(i)],nd[bel[i]].pb(i);
	for(int i=1;i<=n;++i) if(!vis[i]) $(i);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=m;++i)
	{
		x=E[i][0],y=E[i][1];
		if(bel[x]!=bel[y]) _[bel[x]].pb(bel[y]);
	}
	for(int i=1;i<=cnt;++i)
	{
		std::sort(nd[i].begin(),nd[i].end(),[&](int a,int b)->bool{return dfn[a]<dfn[b];});
		std::sort(_[i].begin(),_[i].end()),_[i].erase(std::unique(_[i].begin(),_[i].end()),_[i].end());
	}
	if(cnt==1)
	{
		for(auto $:nd[1]) printf("%d ",$);
		printf("1\n");
		return 0;
	}
	dfs(1);
	puts("There is no route, Karl!");
	return 0;
}

