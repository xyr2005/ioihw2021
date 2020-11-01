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

const int N=10015;
namespace flow
{
	struct edge{
		int v,nxt;
		int w;
	}c[N<<3];
	int front[N],edge_cnt;
	int cur[N],dep[N],S,T;
	int _q[N],_l,_r;
	int node_cnt;
	inline void addedge(int u,int v,int w)
	{
		c[++edge_cnt]=(edge){v,front[u],w},front[u]=edge_cnt;
		c[++edge_cnt]=(edge){u,front[v],0},front[v]=edge_cnt;
	}
	inline void init(){memset(front,255,sizeof(front)),edge_cnt=-1;}
	bool bfs()
	{
		memset(dep,255,(node_cnt+3)<<2);
		memcpy(cur,front,(node_cnt+3)<<2);
		dep[S]=0;
		_q[_l=_r=1]=S;
		while(_l!=_r+1)
		{
			int x=_q[_l++];
			for(int i=front[x];~i;i=c[i].nxt)
			{
				if(c[i].w&&!~dep[c[i].v])
				{
					dep[c[i].v]=dep[x]+1;
					_q[++_r]=c[i].v;
				}
			}
		}
		return ~dep[T];
	}
	int dfs(int x,int flow)
	{
		if(x==T||!flow) return flow;
		int f=0,rf;
		for(int &i=cur[x];~i;i=c[i].nxt)
		{
			if(dep[c[i].v]==dep[x]+1&&(rf=dfs(c[i].v,min(flow,c[i].w))))
			{
				flow-=rf,f+=rf;
				c[i].w-=rf,c[i^1].w+=rf;
				if(!flow) return f;
			}
		}
		return f;
	}
	int dinic()
	{
		int ans=0;
		while(bfs()) ans+=dfs(S,inf);
		return ans;
	}
}
using namespace flow;
struct node{
	std::string s;
	int type;
	inline bool operator == (const node &o)const
	{
		return s==o.s&&type==o.type;
	}
	inline bool operator < (const node &o)const
	{
		return type==o.type?s<o.s:type<o.type;
	}
}mp[N];
int pos,id1[N],id2[N];
std::string s[N];
bool vis[N],mark[N];
std::vector<int> v[N];
int main()
{
	freopen("heavy.in","r",stdin);
	freopen("heavy.out","w",stdout);
	
	init();
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int n,k;std::cin>>n>>k;
	for(int i=1;i<=n;++i)
	{
		std::cin>>s[i];
		mp[++pos]={s[i].substr(0,k),0},mp[++pos]={s[i].substr(SZ(s[i])-k,k),1};
	}
	std::sort(mp+1,mp+pos+1),pos=std::unique(mp+1,mp+pos+1)-mp-1;
	S=pos+1,T=S+1,node_cnt=T;
	for(int i=1;i<=pos;++i)
	{
		if(!mp[i].type) addedge(S,i,1);
		else addedge(i,T,1);
	}
	for(int i=1;i<=n;++i) id1[i]=std::lower_bound(mp+1,mp+pos+1,(node){s[i].substr(0,k),0})-mp,id2[i]=std::lower_bound(mp+1,mp+pos+1,(node){s[i].substr(SZ(s[i])-k,k),1})-mp,addedge(id1[i],id2[i],1);
	int ans=dinic();printf("%d\n",ans);
	vis[S]=true,_q[_l=_r=1]=S;
	while(_l!=_r+1)
	{
		int x=_q[_l++];
		for(int i=front[x];~i;i=c[i].nxt)
		{
			int v=c[i].v;
			if(c[i].w&&!vis[v]) vis[v]=true,_q[++_r]=v;
		}
	}
	for(int i=front[S];~i;i=c[i].nxt) if(vis[c[i].v]!=vis[S]) mark[c[i].v]=true;
	for(int i=front[T];~i;i=c[i].nxt) if(vis[c[i].v]!=vis[T]) mark[c[i].v]=true;
	for(int i=1;i<=n;++i)
	{
		if(mark[id1[i]]) v[id1[i]].pb(i);
		else v[id2[i]].pb(i);
	}
	for(int i=1;i<=pos;++i)
	{
		if(mark[i])
		{
			printf("%d ",SZ(v[i]));
			for(auto it:v[i]) printf("%d ",it);
			printf("\n");
		}
	}
	return 0;
}

