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
struct edge{
	int v,nxt;
}c[N<<1];
int front[N],edge_cnt;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
ll val[N];
struct node{
	ll a,b;
	inline bool operator < (const node &o)const
	{
		return a>o.a;
	}
};
std::priority_queue<node> q[N];
void print(std::priority_queue<node> q)
{
	while(!q.empty()) fprintf(stderr,"%lld %lld\n",q.top().a,q.top().b),q.pop();
	fprintf(stderr,"\n");
}
inline node merge(const node &x,const node &y)
{
	ll t=max(x.a,x.a+y.a-x.b);
	return (node){t,-x.a-y.a+t+x.b+y.b};
}
void dfs(int x,int fa)
{
	for(int i=front[x];i;i=c[i].nxt)
	{
		int v=c[i].v;
		if(v==fa) continue;
		dfs(v,x);
		if(SZ(q[x])<SZ(q[v])) std::swap(q[x],q[v]);
		while(!q[v].empty())
		{
			node a=q[v].top();q[v].pop();
			q[x].push(a);
		}
	}
	node tmp=val[x]>0?(node){0LL,val[x]}:(node){-val[x],0LL};
	while(!q[x].empty()&&(tmp.a>tmp.b||tmp.b>=q[x].top().a))
	{
		node a=q[x].top();q[x].pop();
		tmp=merge(tmp,a);
	}
	if(tmp.a<tmp.b) q[x].push(tmp);
}
void MAIN()
{
	int n,t;read(n,t);
	memset(front,0,(n+3)<<2);
	edge_cnt=0;
	for(int i=1;i<=n;++i) while(!q[i].empty()) q[i].pop();
	int x,y;
	for(int i=1;i<=n;++i) read(val[i]);
	for(int i=1;i<n;++i) read(x,y),addedge(x,y),addedge(y,x);
	val[n+1]=1e15;
	addedge(t,n+1);
	dfs(1,0);
	ll sum=0;
	std::vector<node> v;
	while(!q[1].empty())
	{
		node it=q[1].top();q[1].pop();
		if(sum<it.a) break;
		sum+=it.b-it.a;
	}
	if(sum>=1e15) puts("escaped");
	else puts("trapped");
}
int main()
{
	int _;read(_);
	while(_--) MAIN();
	return 0;
}
