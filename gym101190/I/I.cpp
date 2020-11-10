// Author -- xyr2005

#include<bits/stdc++.h>
#include "I.h"

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
int node_cnt,m;
/*
int go(int st,int dir,int pa)
{
	printf("%d ",st);
	if(!dir) printf("left ");
	else printf("right ");
	printf("%d\n",pa);
	fflush(stdout);
	std::string s;std::cin>>s;
	return s=="center"?0:s=="left"?1:2;
}
*/ 
int low[N],dfn[N],id,st[N],top;
int dfs()
{
	int cur=++node_cnt;
	dfn[cur]=low[cur]=++id,st[++top]=cur;
	int nd=0;
	auto solve=[&](int t,int tag)
	{
		int c1=0,c2=0;
		if(t==1)
		{
			while(true)
			{
				int tmp=go(0,0,0);
				++c1;
				if(tmp==2) break;
			}
		}
		while(true)
		{
			int tmp=go(0,0,0);
			++c2;
			if(tmp==1) break;
		}
		--c2,c2-=tag;
		for(int j=1;j<=c1;++j) go(0,0,0);
		for(int j=1;j<=c2;++j) go(0,1,0);
		return st[top-c1-c2];
	};
	fprintf(stderr,"begin %d\n",cur);
	for(int i=0;i<m;++i)
	{
		fprintf(stderr,"at %d %d\n",cur,i);
		int t=go(1,1,1);
		if(t==0)
		{
			DEBUG;
			int v=dfs();
			if(low[v]<low[cur]) low[cur]=low[v],nd=i;
		}
		else
		{
			int v=solve(t,0);
			if(low[v]<low[cur]) low[cur]=low[v],nd=i;
		}
	}
	fprintf(stderr,"finish %d lowv=%d\n",cur,nd);
	--top;
	if(cur==1) return cur;
	nd=(nd+1)%m;
	solve(go(nd,1,nd),1);
	return cur;
}
/*
int main()
{
	read(m);
	dfs();
	return 0;
}
*/
void solve(int _m)
{
	m=_m;
	dfs();
}
