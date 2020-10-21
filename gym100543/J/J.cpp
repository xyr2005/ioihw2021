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

const int N=110005;
struct seg_tr{
	int ls[N*40],rs[N*40],sum[N*40];
	int node_cnt;
	int build(int l,int r)
	{
		int cur=++node_cnt;
		ls[cur]=rs[cur]=sum[cur]=0;
		if(l==r) return cur;
		int mid=(l+r)>>1;
		ls[cur]=build(l,mid),rs[cur]=build(mid+1,r);
		return cur;
	}
	void Update(int &rt,int pos,int C,int l,int r)
	{
		int cur=++node_cnt;
		ls[cur]=ls[rt],rs[cur]=rs[rt],sum[cur]=sum[rt]+C,rt=cur;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(pos<=mid) Update(ls[cur],pos,C,l,mid);
		else Update(rs[cur],pos,C,mid+1,r);
	}
	int Query(int L,int R,int cur,int l,int r)
	{
		if(L<=l&&r<=R) return sum[cur];
		int mid=(l+r)>>1;
		return (L<=mid?Query(L,R,ls[cur],l,mid):0)+(R>mid?Query(L,R,rs[cur],mid+1,r):0);
	}
}tr;
int t[N];
struct edge{
	int x,y,w;
	inline bool operator < (const edge &o)const
	{
		return w<o.w;
	}
}a[N];
std::vector<edge> v[N];
int ch[N][2],fa[N];
edge w[N],val[N];
bool tag[N];
inline void pushup(int x){val[x]=max(w[x],max(val[ch[x][0]],val[ch[x][1]]));}
inline bool nroot(int x){return x==ch[fa[x]][0]||x==ch[fa[x]][1];}
inline void upd(int x){x&&(std::swap(ch[x][0],ch[x][1]),tag[x]^=1);}
inline void pushdown(int x){tag[x]&&(upd(ch[x][0]),upd(ch[x][1]),tag[x]=0);}
inline void rotate(int x)
{
	int y=fa[x],z=fa[y],k=x==ch[y][1],w=ch[x][!k];
	ch[y][k]=w,ch[x][!k]=y;nroot(y)&&(ch[z][y==ch[z][1]]=x);
	fa[y]=x,fa[x]=z,w&&(fa[w]=y);
	pushup(y),pushup(x);
}
void splay(int x)
{
	static int st[N];
	int y=x,top;st[top=1]=x;
	while(nroot(y)) st[++top]=y=fa[y];
	while(top) pushdown(st[top--]);
	for(int y=fa[x];nroot(x);rotate(x),y=fa[x]) nroot(y)&&(rotate(((x==ch[y][1])==(y==ch[fa[y]][1]))?y:x),0);
}
void access(int x){for(int y=0;x;x=fa[y=x]) splay(x),ch[x][1]=y,pushup(x);}
void mkrt(int x){access(x),splay(x),upd(x);}
void link(int x,int y){mkrt(x),fa[x]=y,splay(x);}
void cut(int x,int y){mkrt(x),access(y),splay(y),fa[x]=0,ch[y][0]=0,pushup(y);}
int split(int x,int y){return mkrt(x),access(y),splay(y),y;}
int Fa[N],bel[N],root[N];
int find(int x){return Fa[x]==x?x:Fa[x]=find(Fa[x]);}
void MAIN()
{
	int n,m;read(n,m);
	memset(tag,0,(n+m+3));
	memset(w,0,sizeof(edge)*(n+m+3));
	memset(val,0,sizeof(edge)*(n+m+3));
	memset(fa,0,(n+m+3)<<2);
	memset(ch,0,(n+m+3)<<3);
	for(int i=1;i<=m;++i) v[i].clear();
	int pos=0;
	for(int i=1;i<=m;++i)
	{
		read(a[i].x,a[i].y,a[i].w);
		t[++pos]=a[i].w;
	}
	std::sort(t+1,t+pos+1),pos=std::unique(t+1,t+pos+1)-t-1;
	tr.node_cnt=0,root[pos+1]=tr.build(1,pos);
	for(int i=1;i<=m;++i) a[i].w=std::lower_bound(t+1,t+pos+1,a[i].w)-t,v[a[i].w].pb(a[i]);
	for(int i=1;i<=n;++i) Fa[i]=i;
	int qwq=n+m;
	for(int i=pos;i>=1;--i)
	{
		root[i]=root[i+1];
		for(auto it:v[i])
		{
			w[qwq]={it.x,it.y,qwq},bel[qwq]=i;
			int x=it.x,y=it.y;
			int a=find(x),b=find(y);
			if(a==b)
			{
				edge tmp=::val[split(x,y)];
				cut(tmp.x,tmp.w),cut(tmp.y,tmp.w);
				tr.Update(root[i],bel[tmp.w],-t[bel[tmp.w]],1,pos);
			}
			else Fa[a]=b;
			link(x,qwq),link(y,qwq);
			tr.Update(root[i],i,t[i],1,pos);
			--qwq;
		}
	}
	int lastans=0,l,r,q;read(q);
	while(q--)
	{
		read(l,r),l-=lastans,r-=lastans;
		printf("%d\n",lastans=tr.Query(1,std::upper_bound(t+1,t+pos+1,r)-t-1,root[std::lower_bound(t+1,t+pos+1,l)-t],1,pos));
	}
}
int main()
{
	int _;read(_);
	while(_--) MAIN();
	return 0;
}

