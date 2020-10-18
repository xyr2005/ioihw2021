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

const int N=300005;
const int mod=1000000007;
template<typename _Tp1,typename _Tp2>inline void add(_Tp1 &a,_Tp2 b){(a+=b)>=mod&&(a-=mod);}
template<typename _Tp1,typename _Tp2>inline void sub(_Tp1 &a,_Tp2 b){(a-=b)<0&&(a+=mod);}
struct edge{
	int v,nxt;
}c[N<<1];
int front[N],edge_cnt;
inline void add_edge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
std::vector<int> e[N];
void dfs0(int x,int fa)
{
	for(int i=front[x];i;i=c[i].nxt)
	{
		if(c[i].v!=fa)
		{
			dfs0(c[i].v,x);
			e[x].pb(c[i].v);
		}
	}
	if(SZ(e[x])>2)
	{
		printf("0\n");
		exit(0);
	}
}
bool isch[N];
int len[N];
int dfn[N],id,rev[N];
int nd[N];
int dis[N];
void dfs1(int x)
{
	dfn[x]=++id;
	rev[id]=x;
	for(auto it:e[x]) dfs1(it);
	len[x]=1;
	if(SZ(e[x])==1)
	{
		isch[x]=isch[e[x][0]];
		len[x]=len[e[x][0]]+1;
		nd[x]=nd[e[x][0]];
		dis[x]=dis[e[x][0]]+1;
	}
	if(SZ(e[x])==0) isch[x]=1;
	if(SZ(e[x])==2) nd[x]=x,dis[x]=1;
}
int dp[N];
inline int getson(int x,int k)
{
	return rev[dfn[x]+k];
}
int dfs(int x);
void solve(int &dp,int x,int k1,int k2)
{
	int v=nd[x];
	if(!v) return;
	int s=e[v][!k1];
	if(SZ(e[s])!=2) return;
	if(!isch[e[s][!k2]]||len[e[s][!k2]]+1!=dis[x]) return;
	if(isch[e[s][k2]]&&isch[e[v][k1]]&&len[e[s][k2]]==len[e[v][k1]]) add(dp,1);
	if(len[e[s][k2]]!=len[e[v][k1]])
	{
		if(isch[e[v][k1]]&&len[e[s][k2]]>len[e[v][k1]]) add(dp,dfs(getson(e[s][k2],len[e[v][k1]])));
		else if(isch[e[s][k2]]&&len[e[s][k2]]<len[e[v][k1]]) add(dp,dfs(getson(e[v][k1],len[e[s][k2]])));
	}
}
void _solve(int &dp,int x)
{
	int a=e[x][0];
	int b=e[x][1];
	if(SZ(e[b])==0) add(dp,dfs(a));
	if(SZ(e[a])==0) add(dp,dfs(b));
	if(SZ(e[a])==1)
	{
		int v=e[a][0];
		if(isch[b]&&isch[v]&&len[b]==len[v]) add(dp,1);
		else if(len[b]!=len[v])
		{
			if(isch[b]&&len[b]<len[v]) add(dp,dfs(getson(v,len[b])));
			else if(isch[v]&&len[v]<len[b]) add(dp,dfs(getson(b,len[v])));
		}
	}
	if(SZ(e[b])==1)
	{
		int v=e[b][0];
		if(isch[a]&&isch[v]&&len[a]==len[v]) add(dp,1);
		else if(len[a]!=len[v])
		{
			if(isch[a]&&len[a]<len[v]) add(dp,dfs(getson(v,len[a])));
			else if(isch[v]&&len[v]<len[a]) add(dp,dfs(getson(a,len[v])));
		}
	}
}
int dfs(int x)
{
	if(dp[x]!=-1) return dp[x];
	if(e[x].empty()) return dp[x]=1;
	dp[x]=0;
	if(SZ(e[x])==1)
	{
		int v=e[x][0];
		if(e[v].empty()) add(dp[x],1);
		else if(SZ(e[v])==1) add(dp[x],dfs(e[v][0]));
		add(dp[x],dfs(v));
		if(isch[x]&&len[x]>=4&&!(len[x]&1)) add(dp[x],1);
		if(SZ(e[v])==2)
		{
			if(isch[e[v][0]]&&len[e[v][0]]==2) add(dp[x],dfs(e[v][1]));
			if(isch[e[v][1]]&&len[e[v][1]]==2) add(dp[x],dfs(e[v][0]));
		}
		if(SZ(e[v])==1)
		{
			int qwq=nd[x];
			if(qwq)
			{
				if(isch[e[qwq][0]]&&len[e[qwq][0]]==dis[x]) add(dp[x],dfs(e[qwq][1]));
				if(isch[e[qwq][1]]&&len[e[qwq][1]]==dis[x]) add(dp[x],dfs(e[qwq][0]));
				if(isch[e[qwq][0]]&&len[e[qwq][0]]+1==dis[x]-1) add(dp[x],dfs(e[qwq][1]));
				if(isch[e[qwq][1]]&&len[e[qwq][1]]+1==dis[x]-1) add(dp[x],dfs(e[qwq][0]));
			}
		}
		solve(dp[x],x,0,0);
		solve(dp[x],x,0,1);
		solve(dp[x],x,1,0);
		solve(dp[x],x,1,1);
		return dp[x];
	}
	else
	{
		_solve(dp[x],x);
		return dp[x];
	}
}
int main()
{
	memset(dp,255,sizeof(dp));
	int n;
	read(n);
	int x,y;
	for(int i=1;i<n;++i)
	{
		read(x,y);
		add_edge(x,y),add_edge(y,x);
	}
	dfs0(1,0);
	dfs1(1);
	printf("%d\n",dfs(1));
	return 0;
}
