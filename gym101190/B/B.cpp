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

const int N=5001005;
const int MAXN=500005;
struct edge{
	int v,nxt;
}c[N*3];
int front[N],edge_cnt;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
int dfn[N],low[N],bel[N],id,col;
int st[N],top;
void tarjan(int x)
{
	dfn[x]=low[x]=++id;
	st[++top]=x;
	for(int i=front[x];i;i=c[i].nxt)
	{
		int v=c[i].v;
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
int ch[MAXN<<1][2],node_cnt,Fa[MAXN<<1];
std::vector<int> v[MAXN<<1];
char s[MAXN],t[MAXN<<1];
int l1[MAXN];
void insert(char *s,int len,int id)
{
	int cur=0;
	for(int i=1;i<=len;++i)
	{
		int tmp=s[i]-48;
		if(!ch[cur][tmp]) ch[cur][tmp]=++node_cnt;
		cur=ch[cur][tmp];
	}
	v[cur].pb(id);
	addedge(cur,id);
	addedge(cur+MAXN*2,id);
}
int main()
{
	freopen("binary.in","r",stdin);
	freopen("binary.out","w",stdout);
	
	int n;read(n);
	int cur=0;
	for(int i=1;i<=n;++i)
	{
		int l=read_str(s+1);
		l1[i]=l;
		for(int j=1;j<=l;++j) t[++cur]=s[j];
		int p=std::find(s+1,s+l+1,'?')-s;
		if(p>l)
		{
			insert(s,l,MAXN*4+i);
			addedge(MAXN*4+i,MAXN*5+i);
		}
		else
		{
			s[p]='0';insert(s,l,MAXN*4+i);
			s[p]='1';insert(s,l,MAXN*5+i);
		}
	}
	memset(Fa,255,sizeof(Fa));
	for(int i=0;i<=node_cnt;++i)
	{
		for(int j=0;j<2;++j)
		{
			if(ch[i][j])
			{
				Fa[ch[i][j]]=i;
				addedge(i,ch[i][j]);
				addedge(ch[i][j]+MAXN*2,i+MAXN*2);
			}
		}
	}
	int tmp=0;
	for(int i=0;i<=node_cnt;++i)
	{
		bool fir=true;
		for(auto it:v[i])
		{
			int t=it>MAXN*5?it-MAXN:it+MAXN;
			if(!fir) addedge(t,tmp+MAXN*6),addedge(tmp+MAXN*6+1,tmp+MAXN*6);
			fir=false,++tmp;
			addedge(tmp+MAXN*6,it);
			if(~Fa[i]) addedge(t,Fa[i]+MAXN*2);
			for(int j=0;j<2;++j) if(ch[i][j]) addedge(t,ch[i][j]);
		}
		fir=true;
		std::reverse(v[i].begin(),v[i].end());
		for(auto it:v[i])
		{
			int t=it>MAXN*5?it-MAXN:it+MAXN;
			if(!fir) addedge(t,tmp+MAXN*6),addedge(tmp+MAXN*6+1,tmp+MAXN*6);
			fir=false,++tmp;
			addedge(tmp+MAXN*6,it);
		}
	}
	for(int i=0;i<N;++i) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;++i) if(bel[i+MAXN*4]==bel[i+MAXN*5]) return puts("NO"),0;
	puts("YES");
	cur=1;
	for(int i=1;i<=n;++i)
	{
		char *p=std::find(t+cur,t+cur+l1[i],'?');
		if(p!=t+cur+l1[i]) *p=bel[i+MAXN*4]<bel[i+MAXN*5]?'1':'0';
		for(int j=0;j<l1[i];++j) putchar(t[j+cur]);
		putchar('\n');
		cur+=l1[i];
	}
	return 0;
}
