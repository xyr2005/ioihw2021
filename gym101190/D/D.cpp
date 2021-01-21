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

const int N=1005;
struct edge{
	int v,nxt;
	int w;
	ll cost;
}c[N<<5];
int front[N],edge_cnt;
inline void addedge(int u,int v,int w,ll cost)
{
	c[++edge_cnt]=(edge){v,front[u],w,cost},front[u]=edge_cnt;
	c[++edge_cnt]=(edge){u,front[v],0,-cost},front[v]=edge_cnt;
}
ll dep[N];
int cur[N],S,T,node_cnt;
bool inq[N];
int _q[N*N],_l,_r;
inline void init(){memset(front,255,sizeof(front)),edge_cnt=-1;}
bool bfs()
{
	memset(dep,-63,(node_cnt+2)*sizeof(ll));
	memcpy(cur,front,(node_cnt+2)<<2);
	memset(inq,0,node_cnt+2);
	_q[_l=_r=1]=S,dep[S]=0;
	while(_l!=_r+1)
	{
		int x=_q[_l++];
		inq[x]=false;
		for(int i=front[x];~i;i=c[i].nxt)
		{
			int v=c[i].v;
			if(c[i].w&&dep[v]<dep[x]+c[i].cost)
			{
				dep[v]=dep[x]+c[i].cost;
				if(!inq[v]) inq[v]=true,_q[++_r]=v;
			}
		}
	}
	return dep[T]>=-1e17;
}
int dfs(int x,int flow)
{
	if(x==T||!flow) return flow;
	inq[x]=true;
	int f=0,rf;
	for(int &i=cur[x];~i;i=c[i].nxt)
	{
		int v=c[i].v;
		if(!inq[v]&&dep[v]==dep[x]+c[i].cost&&(rf=dfs(v,min(flow,c[i].w))))
		{
			flow-=rf,f+=rf;
			c[i].w-=rf,c[i^1].w+=rf;
			if(!flow) return f;
		}
	}
	return f;
}
ll dinic()
{
	ll ans=0;
	while(bfs()) ans+=dep[T]*dfs(S,inf);
	return ans;
}
int val[N],id[N];
int main()
{
	freopen("delight.in","r",stdin);
	freopen("delight.out","w",stdout);
	init();
	int n,k,L,R;read(n,k,L,R),R=k-R;
	ll ans=0;
	for(int i=1;i<=n;++i) read(val[i]);
	int x;
	for(int i=1;i<=n;++i) read(x),ans+=x,val[i]-=x;
	S=n-k+3,T=S+1,node_cnt=T;
	addedge(S,1,R,0),addedge(n-k+2,T,R,0);
	for(int i=1;i<=n;++i) addedge(max(1,i-k+1),min(n-k+2,i+1),1,val[i]),id[i]=edge_cnt;
	for(int i=1;i<=n-k+1;++i) addedge(i,i+1,R-L,0);
	printf("%lld\n",ans+dinic());
 	for(int i=1;i<=n;++i) putchar(c[id[i]].w?'S':'E');
	putchar('\n');
	return 0;
}

