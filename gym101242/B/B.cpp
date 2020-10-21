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

const int N=5005;
struct edge{
	int v,w;
};
std::vector<edge> e1[N],e2[N];
int dis1[N],dis2[N];
struct node{
	int u,d;
	inline bool operator < (const node &o)const
	{
		return d>o.d;
	}
};
std::priority_queue<node> q;
void dij(int *dis,std::vector<edge> *e,int s)
{
	dis[s]=0,q.push({s,0});
	while(!q.empty())
	{
		node x=q.top();q.pop();
		if(dis[x.u]!=x.d) continue;
		for(auto it:e[x.u])
		{
			int v=it.v,w=it.w;;
			if(dis[v]>dis[x.u]+w)
			{
				dis[v]=dis[x.u]+w;
				q.push({v,dis[v]});
			}
		}
	}
}
ll a[N],f[N],g[N];
void solve(int l,int r,int L,int R)
{
	if(l>r||L>R) return;
	int mid=(l+r)>>1;
	ll minn=1e18;int id=L;
	int _R=min(R,mid-1);
	for(int i=L;i<=_R;++i)
	{
		ll tmp=g[i]+(a[mid]-a[i])*(mid-i-1);
		if(tmp<minn) minn=tmp,id=i;
	}
	f[mid]=minn;
	solve(l,mid-1,L,id),solve(mid+1,r,id,R);
}
int main()
{
	memset(dis1,63,sizeof(dis1));
	memset(dis2,63,sizeof(dis2));
	int n,b,s,r;read(n,b,s,r);
	int x,y,z;
	for(int i=1;i<=r;++i)
	{
		read(x,y,z);
		e1[x].pb({y,z}),e2[y].pb({x,z});
	}
	dij(dis1,e1,b+1);
	dij(dis2,e2,b+1);
	for(int i=1;i<=b;++i) a[i]=dis1[i]+dis2[i];
	std::sort(a+1,a+b+1);
	for(int i=1;i<=b;++i) a[i]+=a[i-1];
	n=b;
	memset(g,63,sizeof(g)),g[0]=0;
	while(s--)
	{
		memset(f,63,sizeof(f));
		solve(0,b,0,b);
		memcpy(g,f,sizeof(f));
	}
	printf("%lld\n",g[b]);
	return 0;
}

