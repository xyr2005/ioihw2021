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

const int N=25;
bool e[N][N],a[N][N];
int mp[127],dfn[N],low[N],id,st[N],top,bel[N],col,n;
void tarjan(int x)
{
	dfn[x]=low[x]=++id,st[++top]=x;
	for(int v=1;v<=n;++v)
	{
		if(!e[x][v]) continue;
		if(!dfn[v]) tarjan(v),chmin(low[x],low[v]);
		else if(!bel[v]) chmin(low[x],dfn[v]);
	}
	if(dfn[x]==low[x])
	{
		bel[x]=++col;
		while(st[top]!=x) bel[st[top--]]=col;
		--top;
	}
}
ll dp[1<<22];
int out[1<<22];
int main()
{
	freopen("fygon20.in","r",stdin);
	freopen("fygon20.out","w",stdout);
	
	int m;read(m);
	mp['1']=++n,mp['n']=++n;
	while(m--)
	{
		char ch=getchar();
		while(ch!='f'&&ch!='l') ch=getchar();
		if(ch=='l') break;
		char a,b,c;
		scanf("or %c in range(%c, %c):",&a,&b,&c);
		if(!mp[a]) mp[a]=++n;
		if(!mp[b]) mp[b]=++n;
		if(!mp[c]) mp[c]=++n;
		e[mp[b]][mp[a]]=true,e[mp[a]][mp[c]]=true;
	}
	for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;++i) for(int v=1;v<=n;++v) if(e[i][v]&&bel[i]!=bel[v]) a[bel[i]][bel[v]]=true;
	n=col;
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) out[1<<(i-1)]|=a[i][j]<<(j-1);
	for(int st=0;st<1<<n;++st) out[st]=out[st^lowbit(st)]|out[lowbit(st)];
	dp[0]=1;
	for(int st=0;st<1<<n;++st) for(int i=0;i<n;++i) if(!((st>>i)&1)&&!((out[(1<<n)-1-st]>>i)&1)) dp[st|(1<<i)]+=dp[st];
	ll mul=1;for(int i=1;i<=n-2;++i) mul*=(ll)i;
	ll g=gcd(mul,dp[(1<<n)-1]);
	printf("%d %lld/%lld\n",n-2,dp[(1<<n)-1]/g,mul/g);
	return 0;
}

