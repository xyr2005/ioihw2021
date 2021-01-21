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

const int N=50005;
struct node{
	int l,r;
	inline bool operator < (const node &o)const{return l==o.l?r<o.r:l<o.l;}
}a[N];
inline int _min(int A,int B){return a[A].r<a[B].r?A:B;}
int n,t[N];
struct seg_tr{
	struct Node{
		int ls,rs;
		pi v1;
		int v2,tag;
	}f[N<<1];
	int node_cnt;
	inline void pushup(int x)
	{
		f[x].v1=min(f[f[x].ls].v1,f[f[x].rs].v1);
		f[x].v2=_min(f[f[x].ls].v2,f[f[x].rs].v2);
	}
	int build(int l,int r)
	{
		int cur=++node_cnt;
		f[cur]={0,0,{0,0},0,0};
		if(l==r) return f[cur].v1={n-l+1,l},f[cur].v2=l,cur;
		int mid=(l+r)>>1;
		f[cur].ls=build(l,mid),f[cur].rs=build(mid+1,r);
		return pushup(cur),cur;
	}
	inline void upd(int cur,int C){f[cur].v1.first+=C,f[cur].tag+=C;}
	inline void pushdown(int cur){if(f[cur].tag)upd(f[cur].ls,f[cur].tag),upd(f[cur].rs,f[cur].tag),f[cur].tag=0;}
	void Update(int L,int R,int C,int l,int r,int cur)
	{
		if(L<=l&&r<=R) return upd(cur,C);
		pushdown(cur);int mid=(l+r)>>1;
		if(L<=mid) Update(L,R,C,l,mid,f[cur].ls);
		if(R>mid) Update(L,R,C,mid+1,r,f[cur].rs);
		pushup(cur);
	}
	void Modify(int pos,int l,int r,int cur)
	{
		if(l==r) return (void)(f[cur].v1.first=inf,f[cur].v2=0);
		pushdown(cur);int mid=(l+r)>>1;
		if(pos<=mid) Modify(pos,l,mid,f[cur].ls);
		else Modify(pos,mid+1,r,f[cur].rs);
		pushup(cur);
	}
	int Query(int L,int R,int l,int r,int cur)
	{
		if(L<=l&&r<=R) return f[cur].v2;
		pushdown(cur);int mid=(l+r)>>1;
		if(L<=mid&&R>mid) return _min(Query(L,R,l,mid,f[cur].ls),Query(L,R,mid+1,r,f[cur].rs));
		return L<=mid?Query(L,R,l,mid,f[cur].ls):Query(L,R,mid+1,r,f[cur].rs);
	}
}tr;
bool check(int mid)
{
	tr.node_cnt=0,tr.build(1,n);
	for(int i=1;i<=n;++i) t[i]=n;
	int cur=1;
	for(int i=1;i<=n;++i)
	{
		pi tmp=tr.f[1].v1;
		if(tmp.first<i) return false;
		int p=tr.Query(1,tmp.first==i?tmp.second:n,1,n,1);
		tr.Modify(p,1,n,1),t[p]=-1;
		if(p<n) tr.Update(p+1,n,1,1,n,1);
		while(cur<=n&&a[cur].l<=a[p].r)
		{
			if(~t[cur]) tr.Update(cur,cur,i+mid-t[cur],1,n,1),t[cur]=i+mid;
			++cur;
		}
	}
	return true;
}
std::vector<int> construct(int mid)
{
	tr.node_cnt=0,tr.build(1,n);
	for(int i=1;i<=n;++i) t[i]=n;
	int cur=1;
	std::vector<int> v;
	for(int i=1;i<=n;++i)
	{
		pi tmp=tr.f[1].v1;
		int p=tr.Query(1,tmp.first==i?tmp.second:n,1,n,1);
		tr.Modify(p,1,n,1),t[p]=-1,v.pb(p);
		if(p<n) tr.Update(p+1,n,1,1,n,1);
		while(cur<=n&&a[cur].l<=a[p].r)
		{
			if(~t[cur]) tr.Update(cur,cur,i+mid-t[cur],1,n,1),t[cur]=i+mid;
			++cur;
		}
	}
	return v;
}
void MAIN()
{
	read(n);
	for(int i=1;i<=n;++i) read(a[i].l,a[i].r);
	std::sort(a+1,a+n+1);a[0].r=inf;
	int l=0,r=n-1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	std::vector<int> ans(construct(l));
	for(auto it:ans) printf("%d %d\n",a[it].l,a[it].r);
}
int main()
{
	int _;read(_);
	while(_--) MAIN();
	return 0;
}

