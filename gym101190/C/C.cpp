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
int dfn[N],id;
bool tag[N];
inline bool cmp(int a,int b){return dfn[a]<dfn[b];}
struct answer{
	char ch;
	int a,b,c;
};
std::vector<answer> ans;
int col[N];
void dfs(int x,int fa)
{
	dfn[x]=++id;
	std::vector<int> t,qwq;
	bool __=false;
	for(int i=0;i<SZ(e[x]);++i)
	{
		int v=e[x][i];
		if(v==fa) continue;
		if(!dfn[v]) t.pb(v),dfs(v,x);
		else if(dfn[v]>dfn[x]) qwq.pb(v);
		else __=true;
	}
	memset(tag,0,SZ(t));
	for(auto it:qwq) tag[std::upper_bound(t.begin(),t.end(),it,cmp)-t.begin()-1]=true;
	ans.pb({'r',x,1,4});
	for(int i=0;i<SZ(t);++i) if(tag[i]) ans.pb({'j',t[i],x,0});
	ans.pb({'c',x,3,4});
	ans.pb({'r',x,3,2});
	for(int i=0;i<SZ(t);++i) if(!tag[i]&&col[t[i]]==3) ans.pb({'j',t[i],x,0});
	ans.pb({'c',x,3,4});
	for(int i=0;i<SZ(t);++i) if(!tag[i]&&col[t[i]]!=3) ans.pb({'j',t[i],x,0});
	ans.pb({'c',x,1,4});
	ans.pb({'r',x,1,2});
	if(__) ans.pb({'r',x,4,3}),col[x]=3;
	else ans.pb({'r',x,4,1}),col[x]=1;
}
int main()
{
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
	
	int n,m;read(n,m);
	int x,y;
	for(int i=1;i<=m;++i)
	{
		read(x);
		int last;read(last);
		for(int j=1;j<x;++j) read(y),e[y].pb(last),e[last].pb(y),last=y;
	}
	dfs(1,0);
	printf("%d\n",SZ(ans));
	for(auto it:ans)
	{
		if(it.ch=='j') printf("%c %d %d\n",it.ch,it.a,it.b);
		else printf("%c %d %d %d\n",it.ch,it.a,it.b,it.c);
	}
	return 0;
}

