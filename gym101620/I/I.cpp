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

const int N=200005;
int a[N],n;
struct seg_tr{
	struct Node{
		int ls,rs;
		int val,tag;
	}f[N<<1];
	int node_cnt;
	inline void pushup(int x)
	{
		f[x].val=min(f[f[x].ls].val,f[f[x].rs].val);
	}
	int build(int l,int r)
	{
		int cur=++node_cnt;
		if(l==r)
		{
			f[cur].val=l;
			return cur;
		}
		int mid=(l+r)>>1;f[cur].ls=build(l,mid),f[cur].rs=build(mid+1,r);
		return pushup(cur),cur;
	}
	inline void upd(int cur,int C){f[cur].val+=C,f[cur].tag+=C;}
	inline void pushdown(int cur){f[cur].tag&&(upd(f[cur].ls,f[cur].tag),upd(f[cur].rs,f[cur].tag),f[cur].tag=0);}
	void Update(int L,int R,int C,int l,int r,int cur)
	{
		if(L<=l&&r<=R)
		{
			upd(cur,C);
			return;
		}
		pushdown(cur);
		int mid=(l+r)>>1;
		if(L<=mid) Update(L,R,C,l,mid,f[cur].ls);
		if(R>mid) Update(L,R,C,mid+1,r,f[cur].rs);
		pushup(cur);
	}
	int Query(int pos,int l,int r,int cur)
	{
		if(l==r) return f[cur].val;
		pushdown(cur);
		int mid=(l+r)>>1;
		return pos<=mid?Query(pos,l,mid,f[cur].ls):Query(pos,mid+1,r,f[cur].rs);
	}
	int Query(int l,int r,int cur)
	{
		if(l==r) return l;
		pushdown(cur);
		int mid=(l+r)>>1;
		if(!f[f[cur].ls].val) return Query(l,mid,f[cur].ls);
		return Query(mid+1,r,f[cur].rs);
	}
}tr;
struct edge{
	int v,nxt;
}c[N<<1];
int front[N],edge_cnt;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
int st1[N],top1,st2[N],top2,st[N],top;
int L[N],R[N],M[N],type[N],id[N],node_cnt;
int build()
{
	tr.build(1,n);
	for(int i=1;i<=n;++i)
	{
		tr.Update(1,n,-1,1,n,1);
		while(top1&&a[i]>a[st1[top1]]) tr.Update(st1[top1-1]+1,st1[top1],-a[st1[top1]],1,n,1),--top1;
		while(top2&&a[i]<a[st2[top2]]) tr.Update(st2[top2-1]+1,st2[top2],a[st2[top2]],1,n,1),--top2;
		tr.Update(st1[top1]+1,i,a[i],1,n,1);
		tr.Update(st2[top2]+1,i,-a[i],1,n,1);
		st1[++top1]=i,st2[++top2]=i;
		int limit=tr.Query(1,n,1),cur=++node_cnt;
		L[cur]=R[cur]=i,id[i]=cur;
		while(top&&L[st[top]]>=limit)
		{
			int tmp=st[top];
			if(type[tmp]&&!tr.Query(M[tmp],1,n,1))
			{
				M[tmp]=L[cur],R[tmp]=i;
				addedge(tmp,cur);
				cur=tmp,--top;
			}
			else if(!tr.Query(L[tmp],1,n,1))
			{
				int nd=++node_cnt;
				addedge(nd,tmp),addedge(nd,cur);
				L[nd]=L[tmp],R[nd]=i,M[nd]=L[cur],type[nd]=1;
				cur=nd,--top;
			}
			else
			{
				int nd=++node_cnt;
				addedge(nd,cur);
				do{
					addedge(nd,st[top--]);
				}while(top&&tr.Query(L[st[top]],1,n,1));
				L[nd]=L[st[top]],R[nd]=i,addedge(nd,st[top--]);
				cur=nd;
			}
		}
		st[++top]=cur;
	}
	return st[1];
}
int anc[N][21],dep[N];
void dfs(int x,int fa)
{
	anc[x][0]=fa,dep[x]=dep[fa]+1;
	for(int i=1;i<=20;++i) anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=front[x];i;i=c[i].nxt) dfs(c[i].v,x);
}
int jump(int x,int k)
{
	for(int i=20;i>=0;--i) if((k>>i)&1) x=anc[x][i];
	return x;
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) std::swap(x,y);
	for(int i=20;i>=0;--i) if(dep[anc[x][i]]>=dep[y]) x=anc[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;--i) if(anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}
int main()
{
	read(n);
	for(int i=1;i<=n;++i) read(a[i]);
	int root=build();
	dfs(root,0);
	int m;read(m);
	int x,y;
	while(m--)
	{
		read(x,y);
		if(x==y)
		{
			printf("%d %d\n",x,y);
			continue;
		}
		x=id[x],y=id[y];
		int nd=lca(x,y);
		if(type[nd]) printf("%d %d\n",L[jump(x,dep[x]-dep[nd]-1)],R[jump(y,dep[y]-dep[nd]-1)]);
		else printf("%d %d\n",L[nd],R[nd]);
	}
	return 0;
}
