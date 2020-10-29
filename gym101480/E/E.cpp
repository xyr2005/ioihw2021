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

const int N=300005;
struct edge{
	int x,y,w;
	inline bool operator < (const edge &o)const
	{
		return w<o.w;
	}
}a[N];
struct node{
	int val,id;
	inline bool operator < (const node &o)const
	{
		return val<o.val;
	}
}b[N];
int fa[N],maxx[N],siz[N],sum[N],ans1[N],ans2[N],dg[N];
int cnt,c1,c2;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline bool check(int x){return maxx[x]==2&&sum[x]==siz[x]+siz[x];}
void merge(int x,int y)
{
	int a=find(x),b=find(y);
	cnt-=check(a);
	if(a!=b) cnt-=check(b);
	if(!dg[x]) ++c1;
	if(!dg[y]) ++c1;
	if(dg[x]==1) ++c2;
	else if(dg[x]==2) --c2;
	if(dg[y]==1) ++c2;
	else if(dg[y]==2) --c2;
	++dg[x],++dg[y];
	chmax(maxx[a],dg[x]),chmax(maxx[b],dg[y]),++sum[a],++sum[b];
	if((x=a)==(y=b))
	{
		cnt+=check(y);
		return;
	}
	fa[x]=y,siz[y]+=siz[x],chmax(maxx[y],maxx[x]),sum[y]+=sum[x];
	cnt+=check(y);
}
int main()
{
	int n,m;read(n,m);
	int x,y,z;
	for(int i=1;i<=m;++i)
	{
		read(x,y,z);
		a[i]={x,y,-z};
	}
	std::sort(a+1,a+m+1);
	int q;read(q);
	for(int i=1;i<=q;++i) read(b[i].val),b[i].id=i,b[i].val*=-1;
	std::sort(b+1,b+q+1);
	for(int i=1;i<=n;++i) fa[i]=i,siz[i]=1;
	int cur=0;
	for(int i=1;i<=q;++i)
	{
		while(cur<m&&a[cur+1].w<=b[i].val) ++cur,merge(a[cur].x,a[cur].y);
		ans1[b[i].id]=c1-c2+cnt,ans2[b[i].id]=cur-c2+cnt;
	}
	for(int i=1;i<=q;++i) printf("%d %d\n",ans1[i],ans2[i]);
	return 0;
}

