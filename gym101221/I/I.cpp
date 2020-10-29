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

const int N=105;
namespace flow
{
	struct edge{
		int v,nxt;
		int w;
	}c[N*N];
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
struct vec{
	int x,y;
	inline vec operator - (const vec &o)const
	{
		return (vec){x-o.x,y-o.y};
	}
}a[N];
double dis[N][N];
inline double getdis(const vec &a,const vec &b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline int cross(const vec &a,const vec &b)
{
	return a.x*b.y-a.y*b.x;
}
bool vis[N];
int main()
{
	int n,d;read(n,d);
	for(int i=1;i<=n;++i) read(a[i].x,a[i].y);
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) dis[i][j]=getdis(a[i],a[j]);
	std::vector<int> res={1};
	for(int a=1;a<=n;++a)
	{
		for(int b=a+1;b<=n;++b)
		{
			if(dis[a][b]>d) continue;
			std::vector<int> v1,v2;
			for(int i=1;i<=n;++i)
			{
				if(dis[i][a]<=dis[a][b]&&dis[i][b]<=dis[a][b])
				{
					if(cross(::a[b]-::a[a],::a[i]-::a[a])>=0) v1.pb(i);
					else v2.pb(i);
				}
			}
			init();
			S=SZ(v1)+SZ(v2)+1,T=S+1,node_cnt=T;
			for(int i=0;i<SZ(v1);++i)
			{
				addedge(S,i+1,1);
				for(int j=0;j<SZ(v2);++j) if(dis[v1[i]][v2[j]]>dis[a][b]) addedge(i+1,j+1+SZ(v1),1);
			}
			for(int i=0;i<SZ(v2);++i) addedge(i+1+SZ(v1),T,1);
			int f=dinic();
			memset(vis,0,sizeof(vis));
			_l=1,_r=0;
			for(int i=front[S];~i;i=c[i].nxt) if(c[i].w) _q[++_r]=c[i].v,vis[c[i].v]=true;
			while(_l!=_r+1)
			{
				int x=_q[_l++];
				for(int i=front[x];~i;i=c[i].nxt) if(!vis[c[i].v]&&c[i].w) _q[++_r]=c[i].v,vis[c[i].v]=true;
			}
			std::vector<int> v;
			for(int i=0;i<SZ(v1);++i) if(vis[i+1]) v.pb(v1[i]);
			for(int i=0;i<SZ(v2);++i) if(!vis[i+1+SZ(v1)]) v.pb(v2[i]);
			assert(SZ(v)==SZ(v1)+SZ(v2)-f);
			if(SZ(v)>SZ(res)) res=v;
		}
	}
	printf("%d\n",SZ(res));
	for(auto it:res) printf("%d ",it);
	printf("\n");
	return 0;
}

