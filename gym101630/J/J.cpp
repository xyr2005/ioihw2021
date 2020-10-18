// Author -- Frame

#include<bits/stdc++.h>

#define lowbit(x) ((x)&(-(x)))
#define Finline __inline__ __attribute__ ((always_inline))
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
#define SZ(x) ((int)x.size())
#define mkpr std::make_pair
#define pb push_back

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pi;
typedef std::pair<ll,ll> pl;

const int inf=0x3f3f3f3f,Inf=0x7fffffff;
const ll INF=0x3f3f3f3f3f3f3f3f;

Finline uint rnd()
{
	static uint seed=416;
	return seed^=seed>>5,seed^=seed<<17,seed^=seed>>13;
}
template <typename _Tp>_Tp gcd(const _Tp &a,const _Tp &b){return (!b)?a:gcd(b,a%b);}
template <typename _Tp>Finline _Tp abs(const _Tp &a){return a>=0?a:-a;}
template <typename _Tp>Finline _Tp max(const _Tp &a,const _Tp &b){return a<b?b:a;}
template <typename _Tp>Finline _Tp min(const _Tp &a,const _Tp &b){return a<b?a:b;}
template <typename _Tp>Finline void chmax(_Tp &a,const _Tp &b){(a<b)&&(a=b);}
template <typename _Tp>Finline void chmin(_Tp &a,const _Tp &b){(b<a)&&(a=b);}
template <typename _Tp>Finline void read(_Tp &x)
{
	char ch(getchar());
	bool f(false);
	while(ch<48||ch>57) f|=ch==45,ch=getchar();
	x=ch&15,ch=getchar();
	while(ch>=48&&ch<=57) x=(((x<<2)+x)<<1)+(ch&15),ch=getchar();
	if(f) x=-x;
}
template <typename _Tp,typename... Args>Finline void read(_Tp &t,Args &...args){read(t);read(args...);}
template <typename _Tp,typename... Args>Finline _Tp min(const _Tp &a,const _Tp &b,const Args &...args){return a<b?min(a,args...):min(b,args...);}
template <typename _Tp,typename... Args>Finline _Tp max(const _Tp &a,const _Tp &b,const Args &...args){return a<b?max(b,args...):max(a,args...);}
Finline int read_str(char *s)
{
	char ch(getchar());
	while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
	char *tar=s;
	*tar=ch,ch=getchar();
	while(ch!=' '&&ch!='\r'&&ch!='\n'&&ch!=EOF) *(++tar)=ch,ch=getchar();
	return tar-s+1;
}

const int N=3005;
int n,m,k;
struct edge{
	int v,nxt,w;
}c[N<<1];
int front[N],edge_cnt;
Finline void addedge(int u,int v,int w)
{
	c[++edge_cnt]=(edge){v,front[u],w};
	front[u]=edge_cnt;
	
	c[++edge_cnt]=(edge){u,front[v],w};
	front[v]=edge_cnt;
}
int E[N][3];
int t[N],pos;
struct node{
	int u;ll d;
	Finline bool operator < (const node &o)const
	{
		return d>o.d;
	}
};
ll dis[N];
std::priority_queue<node> q;
ll dij()
{
	memset(dis,63,sizeof(dis));
	dis[1]=0;
	q.push((node){1,0});
	while(!q.empty())
	{
		node x=q.top();q.pop();
		if(dis[x.u]!=x.d) continue;
		for(int i=front[x.u];i;i=c[i].nxt)
		{
			int v=c[i].v;
			if(dis[v]>dis[x.u]+c[i].w)
			{
				dis[v]=dis[x.u]+c[i].w;
				q.push((node){v,dis[v]});
			}
		}
	}
	return dis[n];
}
ll solve(int x)
{
	edge_cnt=0;memset(front,0,sizeof(front));
	for(int i=1;i<=m;++i) addedge(E[i][0],E[i][1],max(0,E[i][2]-x));
	return dij()+1ll*k*x;
}
int main()
{
	read(n,m,k);
	for(int i=1;i<=m;++i) read(E[i][0],E[i][1],E[i][2]),t[++pos]=E[i][2];
	std::sort(t+1,t+pos+1);
	int last=-1;
	ll ans=solve(0);
	for(int i=1;i<=pos;++i)
	{
		if(t[i]!=last)
		{
			chmin(ans,solve(t[i]));
			last=t[i];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
