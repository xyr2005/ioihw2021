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
struct edge{
	int v,nxt;
}c[N];
int front[N],edge_cnt;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
int B,bel[N];
int siz[N],dep[N],son[N],Fa[N],top[N],val[N],dfn[N],tree_id;
void dfs(int x)
{
	bel[x]=B;
	if(!front[x]) val[x]=1;
	for(int i=front[x];i;i=c[i].nxt)
	{
		int v=c[i].v;
		dfs(v);
		val[x]+=val[v];
	}
}
void dfs1(int x,int fa)
{
	Fa[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
	for(int i=front[x];i;i=c[i].nxt)
	{
		int v=c[i].v;
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]) son[x]=v;
	}
}
void dfs2(int x,int topf)
{
	top[x]=topf,dfn[x]=++tree_id;
	if(!son[x]) return;
	dfs2(son[x],topf);
	for(int i=front[x];i;i=c[i].nxt) if(!top[c[i].v]) dfs2(c[i].v,c[i].v);
}
int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]>dep[top[y]]) x=Fa[top[x]];
		else y=Fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}
bool mark[N];
struct node{
	int x;
	inline bool operator < (const node &o)const
	{
		return dfn[x]<dfn[o.x];
	}
};
std::set<node> S[N];
int main()
{
	freopen("gangsters.in","r",stdin);
	freopen("gangsters.out","w",stdout);
	
	int n,q;read(n,q);
	int x;
	for(int i=2;i<=n;++i) read(x),addedge(x,i);
	for(int i=front[1];i;i=c[i].nxt)
	{
		++B;
		dfs(c[i].v);
	}
	dfs1(1,0),dfs2(1,1);
	int sum1=0,sum2=0,cnt=0;
	while(q--)
	{
		read(x);
		x=abs(x);
		if(!mark[x])
		{
			++cnt;
			if(S[bel[x]].empty()) ++sum1;
			else sum2-=val[lca(S[bel[x]].begin()->x,S[bel[x]].rbegin()->x)];
			S[bel[x]].insert({x});
			sum2+=val[lca(S[bel[x]].begin()->x,S[bel[x]].rbegin()->x)];
		}
		else
		{
			--cnt;
			sum2-=val[lca(S[bel[x]].begin()->x,S[bel[x]].rbegin()->x)];
			S[bel[x]].erase({x});
			if(S[bel[x]].empty()) --sum1;
			else sum2+=val[lca(S[bel[x]].begin()->x,S[bel[x]].rbegin()->x)];
		}
		printf("%d %d\n",sum1,sum2-cnt);
		mark[x]^=1;
	}
	return 0;
}
