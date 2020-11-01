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

const int N=1005;
bool a[N][N],b[12][12];
int dp[N],cnt[1<<10];
std::vector<int> rest[N],e[N];
bool f[1<<10];
void dfs(int x,int fa)
{
	dp[x]=0,rest[x].clear();
	if(fa) e[x].erase(std::find(e[x].begin(),e[x].end(),fa));
	for(auto v:e[x]) dfs(v,x),dp[x]+=dp[v];
	memset(b,0,sizeof(b));
	for(int i=0;i<SZ(e[x]);++i)
	{
		for(int j=0;j<i;++j)
		{
			int v1=e[x][i],v2=e[x][j];
			for(auto A:rest[v1]) for(auto B:rest[v2]) b[i][j]|=a[A][B];
			b[j][i]=b[i][j];
		}
	}
	memset(f,0,1<<SZ(e[x]));
	f[0]=true;
	for(int st=0;st<1<<SZ(e[x]);++st) if(f[st]) for(int i=0;i<SZ(e[x]);++i) if(!((st>>i)&1)) for(int j=0;j<i;++j) if(!((st>>j)&1)&&b[i][j]) f[st|(1<<i)|(1<<j)]=true;
	int invalid=0,maxx=0;
	for(int st=0;st<1<<SZ(e[x]);++st)
	{
		if(!f[st]) continue;
		int tmp=cnt[st],cur=st;
		for(int i=0;i<SZ(e[x]);++i)
		{
			if((st>>i)&1) continue;
			bool flag=false;
			for(auto it:rest[e[x][i]]) flag|=a[it][x];
			if(flag) tmp+=2,cur|=1<<i;
		}
		if(tmp>maxx) maxx=tmp,invalid=cur;
		else if(tmp==maxx) invalid&=cur;
	}
	dp[x]+=maxx>>1;
	rest[x].pb(x);
	for(int i=0;i<SZ(e[x]);++i) if(!((invalid>>i)&1)) for(auto it:rest[e[x][i]]) rest[x].pb(it);
}
void MAIN()
{
	int n,x,y;read(n);
	for(int i=0;i<=n+1;++i) e[i].clear();
	for(int i=0;i<=n+1;++i) for(int j=0;j<=n+1;++j) a[i][j]=0;
	for(int i=1;i<n;++i) read(x,y),e[x].pb(y),e[y].pb(x);
	int m;read(m);
	while(m--) read(x,y),a[x][y]=a[y][x]=true;
	dfs(1,0);
	printf("%d\n",dp[1]);
}
int main()
{
	for(int i=0;i<1<<10;++i) cnt[i]=cnt[i>>1]+(i&1);
	int _;read(_);
	while(_--) MAIN();
	return 0;
}

