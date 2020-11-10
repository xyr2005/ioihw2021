// Author -- xyr2005

#include<bits/stdc++.h>
#include "I.h"
namespace memset0blessme
{
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

const int N=25;
std::vector<int> e[N];
int n,m;
int pos[N],cur,ST[N];
bool a[N][N];
int cnt;
int go(int st,int dir,int pa)
{
	int to=e[cur][(pos[cur]+pa)%m];
	fprintf(stderr,"cur = %d  %d %d %d  to = %d\n",cur,st,dir,pa,to);
	pos[cur]=(pos[cur]+st)%m;
	ST[cur]=dir+1;
	if(!a[cur][pos[cur]]) ++cnt;
	a[cur][pos[cur]]=true;
	cur=to;
	if(cnt==n*m)
	{
		puts("AC");
		exit(0);
	}
	return ST[cur];
}
int main()
{
	read(n,m);
	for(int i=1;i<=n;++i)
	{
		e[i].resize(m);
		for(auto &&it:e[i]) read(it);
	}
	cur=1;
	solve(m);
	return 0;
}
}
int go(int st,int dir,int pa)
{
	return memset0blessme::go(st,dir,pa);
}
int main()
{
	return memset0blessme::main();
}
