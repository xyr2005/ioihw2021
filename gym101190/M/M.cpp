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
template <typename _Tp>inline void chmax(_Tp &a,const _Tp &b){(a<b)&&((a=b),0);}
template <typename _Tp>inline void chmin(_Tp &a,const _Tp &b){(b<a)&&((a=b),0);}
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
struct info{
	int val,id;
	inline bool operator < (const info &o)const{return val<o.val;}
	inline info operator + (const int &o)const{return (info){val+o,id};}
}dep[N],val[N];
int tag[N][2];
inline void pushup(int x)
{
	val[x]=min(dep[x],min(val[x<<1],val[x<<1|1]))+tag[x][1];
}
int rest[N];
void Update(int x)
{
	dep[x]={inf,0};
	while(x) pushup(x),x>>=1;
}
void Update(int x,int p,int C)
{
	tag[x][p]+=C;
	if(p==1) while(x) pushup(x),x>>=1;
}
int cnt[N][2];
int lca(int x,int y)
{
	while(x!=y) x>y?x>>=1:y>>=1;
	return x;
}
int main()
{
	freopen("mole.in","r",stdin);
	freopen("mole.out","w",stdout);
	
	for(int i=0;i<N;++i) dep[i]={inf,0},val[i]={inf,0};
	int n,m;read(n,m);
	for(int i=1;i<=n;++i)
	{
		read(rest[i]);
		if(rest[i]) dep[i]={0,i};
	}
	for(int i=2;i<=n;++i) tag[i][0]=tag[i][1]=1;
	for(int i=n;i>=1;--i) pushup(i);
	int x,sum=0;
	for(int i=1;i<=m;++i)
	{
		read(x);
		int dep0=0,cur=x;
		info ans={inf,0};
		chmin(ans,val[x<<1]),chmin(ans,val[x<<1|1]),chmin(ans,dep[x]);
		while(x>1)
		{
			dep0+=tag[x][0];
			int last=x;
			x>>=1;
			chmin(ans,min(dep[x],val[last^1])+dep0);
		}
		if(!--rest[ans.id]) Update(ans.id);
		int L=lca(cur,ans.id);
		int a=cur,b=ans.id;
		while(a!=L)
		{
			if(cnt[a][0]) (!--cnt[a][0])&&(Update(a,0,2),0);
			else (++cnt[a][1]==1)&&(Update(a,1,-2),0);
			a>>=1;
		}
		while(b!=L)
		{
			if(cnt[b][1]) (!--cnt[b][1])&&(Update(b,1,2),0);
			else (++cnt[b][0]==1)&&(Update(b,0,-2),0);
			b>>=1;
		}
		printf("%d%c",sum+=ans.val," \n"[i==m]);
	}
	return 0;
}

