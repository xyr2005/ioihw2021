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

const int N=405;
struct edge{
	int v,nxt;
}c[N*N];
int front[N],edge_cnt;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
int dfn[N],low[N],id,n;
int st[N],top,bel[N],col;
bool flag;
void tarjan(int x)
{
	dfn[x]=low[x]=++id;
	st[++top]=x;
	for(int i=front[x];i&&!flag;i=c[i].nxt)
	{
		int v=c[i].v;
		if(!dfn[v]) tarjan(v),chmin(low[x],low[v]);
		else if(!bel[v]) chmin(low[x],dfn[v]);
	}
	if(flag) return;
	if(dfn[x]==low[x])
	{
		bel[x]=++col,flag|=bel[x]==bel[x+(x<=n?n:-n)];
		while(st[top]!=x)
		{
			int tmp=st[top--];
			bel[tmp]=col;
			flag|=bel[tmp]==bel[tmp+(tmp<=n?n:-n)];
		}
		--top;
	}
}
int t[N*N],a[N][N];
bool check(int v1,int v2)
{
	memset(dfn,0,(n+n+3)<<2);
	memset(low,0,(n+n+3)<<2);
	memset(bel,0,(n+n+3)<<2);
	memset(front,0,(n+n+3)<<2);
	top=id=col=edge_cnt=0;
	for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) if(a[i][j]>v1) addedge(i,j+n),addedge(j,i+n);
	for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) if(a[i][j]>v2) addedge(i+n,j),addedge(j+n,i);
	flag=false;
	for(int i=1;i<=n+n;++i) if(!dfn[i]) tarjan(i);
	return !flag;
}
int main()
{
	read(n);
	int pos=0,x,ans=0;
	t[++pos]=0;
	for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) read(x),t[++pos]=x,chmax(ans,x),a[i][j]=x;
	std::sort(t+1,t+pos+1);
	pos=std::unique(t+1,t+pos+1)-t-1;
	t[++pos]=inf;
	int cur=pos;
	for(int i=1;i<=pos;++i)
	{
		if(t[i]+t[i]>=ans) continue;
		while(cur>=i&&check(t[i],t[cur-1])) --cur;
		chmin(ans,t[i]+t[cur]);
		if(cur<i) break;
	}
	printf("%d\n",ans);
	return 0;
}

