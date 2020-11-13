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

const int N=30005;
struct edge{
	int v,nxt,w;
}c[N<<1];
int front[N],edge_cnt;
inline void addedge(int u,int v,int w)
{
	c[++edge_cnt]=(edge){v,front[u],w};
	front[u]=edge_cnt;
}
struct node{
	int x,y,z;
	inline bool operator < (const node &o)const
	{
		return z<o.z;
	}
}E[N];
int pool[1000005],*p=pool;
int *dp[N];
int Fa[N],len[N],dep[N],w[N];
void dfs1(int x,int fa)
{
	Fa[x]=fa,dep[x]=dep[fa]+1;
	for(int i=front[x];i;i=c[i].nxt)
	{
		int v=c[i].v;
		if(v==fa) continue;
		w[v]=1,dfs1(v,x);
		chmax(len[x],len[v]+1);
	}
	p+=len[x]+5,dp[x]=p,p+=len[x]+5;
	dp[x][0]=1;
	for(int i=front[x];i;i=c[i].nxt)
	{
		int v=c[i].v;
		if(v==fa) continue;
		for(int j=0;j<=len[v];++j) dp[x][j+1]+=dp[v][j];
	}
}
int main()
{
	freopen("hidden.in","r",stdin);
	freopen("hidden.out","w",stdout);
	
	int n;read(n);
	int x,y,z;
	for(int i=1;i<n;++i)
	{
		read(x,y,z),addedge(x,y,z),addedge(y,x,z);
		E[i]={x,y,z};
	}
	dfs1(1,0);
	for(int i=1;i<n;++i) if(dep[E[i].x]<dep[E[i].y]) std::swap(E[i].x,E[i].y);
	std::sort(E+1,E+n);
	p+=405;
	int *cnt=p;
	p+=405,p+=405;
	int *tmp=p;
	p+=405;
	ll ans=0;
	int _=0;
	for(int i=1;i<n;++i)
	{
		x=E[i].x,y=E[i].y,z=E[i].z;
		for(int j=-len[x];j<=len[x];++j) cnt[j]=dp[x][j];
		int cur=Fa[x],qwq=w[x];
		while(cur)
		{
			for(int j=-len[x];j<=len[x];++j) dp[cur][j+qwq]-=cnt[j];
			qwq+=w[cur],cur=Fa[cur];
		}
		w[x]=-1;
		cur=Fa[x],qwq=w[x];
		while(cur)
		{
			for(int j=-len[x];j<=len[x];++j) dp[cur][j+qwq]+=cnt[j];
			qwq+=w[cur],cur=Fa[cur];
		}
		qwq=w[x];
		for(int j=-400;j<=400;++j) tmp[j]=0;
		while(y)
		{
			for(int j=-len[y];j<=len[y];++j) tmp[j+qwq]+=dp[y][j];
			for(int j=-len[x];j<=len[x];++j) tmp[j+qwq+w[x]]-=dp[x][j];
			qwq+=w[y],x=Fa[x],y=Fa[y];
		}
		x=E[i].x;
		for(int j=-len[x];j<=len[x];++j) ans+=1LL*cnt[j]*tmp[-j-1]*z,_+=1LL*cnt[j]*tmp[-j-1];
	}
	printf("%.12lf\n",(double)ans/_);
	return 0;
}

