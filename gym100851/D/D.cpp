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
std::vector<int> e[N];
inline void addedge(int u,int v)
{
	e[u].pb(v),e[v].pb(u);
}
struct node{
	int x,y,id;
}q[N],t[N];
int ans[N];
bool valid[N],tag[N];
int rev[N];
int dis1[N],dis2[N];
int _q[N],_l,_r;
void bfs(int S,int *dis)
{
	_q[_l=_r=1]=S,dis[S]=0;
	while(_l!=_r+1)
	{
		int x=_q[_l++];
		for(auto v:e[x])
		{
			if(!valid[v]||dis[v]<inf) continue;
			dis[v]=dis[x]+1,_q[++_r]=v;
		}
	}
}
void solve(std::vector<int> nd,int L,int R)
{
	if(nd.empty()||L>R) return;
	if(SZ(nd)<=3)
	{
		for(int i=L;i<=R;++i) chmin(ans[q[i].id],q[i].x==q[i].y?0:1);
		return;
	}
	for(auto it:nd) valid[it]=true;
	for(int i=0;i<SZ(nd);++i) rev[nd[i]]=i;
	int minn=inf,X=0,Y=0;
	for(auto x:nd)
	{
		dis1[x]=dis2[x]=inf;
		for(auto v:e[x])
		{
			if(valid[v])
			{
				int A=rev[x],B=rev[v];
				if(A>B) std::swap(A,B);
				int tmp=max(B-A,SZ(nd)-(B-A));
				if(tmp<minn) X=A,Y=B,minn=tmp;
			}
		}
	}
	bfs(nd[X],dis1),bfs(nd[Y],dis2);
	for(int i=X+1;i<Y;++i) tag[nd[i]]=true;
	int p1=L,p2=R;
	for(int i=L;i<=R;++i)
	{
		int x=q[i].x,y=q[i].y;
		chmin(ans[q[i].id],dis1[x]+dis1[y]);
		chmin(ans[q[i].id],dis2[x]+dis2[y]);
		if(tag[x]!=tag[y]) continue;
		if(tag[x]) t[p1++]=q[i];
		else t[p2--]=q[i];
	}
	for(int i=X+1;i<Y;++i) tag[nd[i]]=false;
	for(int i=L;i<=R;++i) q[i]=t[i];
	for(auto it:nd) valid[it]=false;
	std::vector<int> v;for(int i=X;i<=Y;++i) v.pb(nd[i]);
	solve(v,L,p1-1);
	v.clear();
	for(int i=0;i<SZ(nd);++i) if(!(i>X&&i<Y)) v.pb(nd[i]);
	solve(v,p2+1,R);
}
int main()
{
	freopen("distance.in","r",stdin);
	freopen("distance.out","w",stdout);
	
	int n;read(n);
	int x,y;
	for(int i=1;i<n;++i) addedge(i,i+1),addedge(i+1,i);
	addedge(1,n),addedge(n,1);
	for(int i=1;i<=n-3;++i) read(x,y),addedge(x,y),addedge(y,x);
	int Q;read(Q);
	for(int i=1;i<=Q;++i) read(q[i].x,q[i].y),q[i].id=i,ans[i]=inf;
	std::vector<int> v(n);std::iota(v.begin(),v.end(),1);
	solve(v,1,Q);
	for(int i=1;i<=Q;++i) printf("%d\n",ans[i]);
	return 0;
}

