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

const int N=500005;
struct node{
	int x,y;
}a[N],b[N],c[N],d[N];
ll ans;
int Y[N];
void solve(int L,int R,int l,int r)
{
	if(L>R||l>r) return;
	int mid=(l+r)>>1;
	ll maxx=0,pos=0;
	for(int i=std::upper_bound(Y+L,Y+R+1,-d[mid].y)-Y;i<=R;++i)
	{
		if(c[i].x>=d[mid].x) break;
		ll tmp=1ll*(d[mid].x-c[i].x)*max(0,d[mid].y-c[i].y);
		if(tmp>maxx) maxx=tmp,pos=i;
	}
	chmax(ans,maxx);
	if(!pos)
	{
		if(d[mid].y>c[R].y&&d[mid].x<=c[R].x) solve(L,R,mid+1,r);
		if(d[mid].x>c[L].x&&d[mid].y<=c[L].y) solve(L,R,l,mid-1);
	}
	else
	{
		solve(L,pos,l,mid-1);
		solve(pos,R,mid+1,r);
	}
}
int main()
{
	int n,m;read(n,m);
	for(int i=1;i<=n;++i) read(a[i].x,a[i].y);
	for(int i=1;i<=m;++i) read(b[i].x,b[i].y);
	std::sort(a+1,a+n+1,[&](const node &a,const node &b)->bool{return a.x==b.x?a.y<b.y:a.x<b.x;});
	std::sort(b+1,b+m+1,[&](const node &a,const node &b)->bool{return a.x==b.x?a.y>b.y:a.x>b.x;});
	int p1=0,p2=0;
	int last=inf;
	for(int i=1;i<=n;++i) if(a[i].y<last) c[++p1]=a[i],last=a[i].y;
	last=0;for(int i=1;i<=m;++i) if(b[i].y>last) d[++p2]=b[i],last=b[i].y;
	std::reverse(d+1,d+p2+1);
	for(int i=1;i<=p1;++i) Y[i]=-c[i].y;
	solve(1,p1,1,p2);
	printf("%lld\n",ans);
	return 0;
}
