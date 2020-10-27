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
}c[N<<1];
int front[N],edge_cnt;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
int siz[N],Fa[N],dfn[N],tree_id,top[N],son[N],dep[N],anc[N][21];
void dfs1(int x,int fa)
{
	siz[x]=1,Fa[x]=fa,dep[x]=dep[fa]+1;
	anc[x][0]=fa;
	for(int i=1;i<=20;++i) anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=front[x];i;i=c[i].nxt)
	{
		int v=c[i].v;
		if(v==fa) continue;
		dfs1(v,x),siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]) son[x]=v;
	}
}
void dfs2(int x,int topf)
{
	dfn[x]=++tree_id,top[x]=topf;
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
struct BIT{
	int c[N];
	void add(int x,int C){for(;x<N;x+=lowbit(x))c[x]+=C;}
	int sum(int x){int ans=0;for(;x;x-=lowbit(x))ans+=c[x];return ans;}
}tr;
struct node{
	int x,y;
	inline bool operator == (const node &o)const{return x==o.x&&y==o.y;}
};
std::vector<node> v[N];
inline bool ischain(const node &a)
{
	return dfn[a.y]<dfn[a.x]+siz[a.x];
}
int jump(int x,int k)
{
	for(int i=20;i>=0;--i) if((k>>i)&1) x=anc[x][i];
	return x;
}
int t1[N],t2[N];
void dfs(int x,int fa)
{
	for(auto it:v[x])
	{
		int tmp=tr.sum(dfn[x]+siz[x]-1)-tr.sum(dfn[x]-1);
		if(ischain(it)) tmp-=(tr.sum(dfn[it.y]+siz[it.y]-1)-tr.sum(dfn[it.y]-1));
		if(tmp) puts("No"),exit(0);
	}
	for(auto it:v[x]) tr.add(dfn[it.x],1),tr.add(dfn[it.y],1);
	if(!v[x].empty())
	{
		int A=-1,B=-1;
		int _=0;
		for(auto it:v[x])
		{
			if(it.x!=x)
			{
				int tmp=jump(it.x,dep[it.x]-dep[x]-1);
				t1[_]=tmp;
				if(A==-1) A=tmp;
				else if(A!=tmp&&B==-1) B=tmp;
			}
			if(it.y!=x)
			{
				int tmp=jump(it.y,dep[it.y]-dep[x]-1);
				t2[_]=tmp;
				if(A==-1) A=tmp;
				else if(A!=tmp&&B==-1) B=tmp;
			}
			++_;
		}
		for(int i=0;i<SZ(v[x]);++i)
		{
			node it=v[x][i];
			if(x!=it.x&&t1[i]!=A&&t1[i]!=B) puts("No"),exit(0);
			if(t2[i]!=A&&t2[i]!=B) puts("No"),exit(0);
			if(t2[i]==A) std::swap(v[x][i].x,v[x][i].y);
		}
		std::vector<int> v1,v2;
		std::vector<pi> qwq;
		for(auto it:v[x])
		{
			if(it.x!=x) v1.pb(it.x);
			if(it.y!=x) v2.pb(it.y);
			qwq.pb({dep[it.x],dep[it.y]});
		}
		std::sort(v1.begin(),v1.end(),[&](int A,int B)->bool{return dfn[A]<dfn[B];});
		std::sort(v2.begin(),v2.end(),[&](int A,int B)->bool{return dfn[A]<dfn[B];});
		std::sort(qwq.begin(),qwq.end());
		for(int i=0;i+1<SZ(v1);++i) if(!ischain({v1[i],v1[i+1]})) puts("No"),exit(0);
		for(int i=0;i+1<SZ(v2);++i) if(!ischain({v2[i],v2[i+1]})) puts("No"),exit(0);
		for(int i=0;i+1<SZ(qwq);++i) if(qwq[i+1].second<qwq[i].second) puts("No"),exit(0);
	}
	for(int i=front[x];i;i=c[i].nxt)
	{
		int v=c[i].v;
		if(v==fa) continue;
		dfs(v,x);
	}
	for(auto it:v[x]) tr.add(dfn[it.x],-1),tr.add(dfn[it.y],-1);
}
int main()
{
	int n,m;read(n,m);
	int x,y;
	for(int i=1;i<n;++i) read(x,y),addedge(x,y),addedge(y,x);
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=m;++i)
	{
		read(x,y);
		if(x==y)
		{
			--i,--m;
			continue;
		}
		if(dfn[x]>dfn[y]) std::swap(x,y);
		v[lca(x,y)].pb({x,y});
	}
	dfs(1,0);
	puts("Yes");
	return 0;
}

