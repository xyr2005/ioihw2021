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
int front[N],edge_cnt,dg[N];
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
std::priority_queue<int> q1;
std::priority_queue<int,std::vector<int>,std::greater<int>> q2;
int main()
{
//	freopen("graph.in","r",stdin);
//	freopen("graph.out","w",stdout);
	
	int n,m,k;read(n,m,k);
	int x,y,last=0;std::vector<pi> ans;
	for(int i=1;i<=m;++i) read(x,y),addedge(x,y),++dg[y];
	for(int i=1;i<=n;++i) if(!dg[i]) q2.push(i);
	while(!q1.empty()||!q2.empty())
	{
		while(k&&!q2.empty()&&(SZ(q2)>1||(!q1.empty()&&q1.top()>q2.top()))) --k,q1.push(q2.top()),q2.pop();
		if(q2.empty()) q2.push(x=q1.top()),ans.pb({last,x}),q1.pop();
		printf("%d ",last=x=q2.top()),q2.pop();
		for(int i=front[x];i;i=c[i].nxt) if(!--dg[c[i].v]) q2.push(c[i].v);
	}
	printf("\n");
	printf("%d\n",SZ(ans));
	for(auto it:ans) printf("%d %d\n",it.first,it.second);
	return 0;
}

