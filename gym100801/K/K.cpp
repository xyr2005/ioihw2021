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

const int N=2005;
const double PI=acos(-1.0);
struct node{
	int x,y;
}a[N];
inline double getdis(const node &a,const node &b)
{
	return sqrt(1ll*(a.x-b.x)*(a.x-b.x)+1ll*(a.y-b.y)*(a.y-b.y));
}
struct seg{
	double l,r;
	inline bool check(const double &o)
	{
		return l<=o&&o<=r;
	}
	inline void merge(const seg &o)
	{
		chmax(l,o.l),chmin(r,o.r);
	}
};
struct info{
	seg a,b;
	void merge(const info &o)
	{
		a.merge(o.a),b.merge(o.b);
	}
};
int dp[N],d;
info calc(const node &a,const node &b,double cur)
{
	double dis=getdis(a,b);
	if(dis<=d) return {{0.0,PI},{-PI,0.0}};
	double ang=asin((double)d/dis);
	double l=cur-ang,r=cur+ang;
	if(l>=PI) l-=2.0*PI;
	if(r>=PI) r-=2.0*PI;
	if(l<=-PI) l+=2.0*PI;
	if(r<=-PI) r+=2.0*PI;
	if(l<=0&&r>=0) return {{0.0,r},{l,0.0}};
	if(l>=0&&r<=0) return {{l,PI},{-PI,r}};
	if(l>=0&&r>=0) return {{min(l,r),max(l,r)},{0.0,-PI}};
	if(l<=0&&r<=0) return {{PI,0.0},{min(l,r),max(l,r)}};
	assert(0);
}
bool trans[N][N];
int main()
{
	freopen("kingdom.in","r",stdin);
	freopen("kingdom.out","w",stdout);
	
	int n;read(n,d);
	for(int i=1;i<=n;++i) read(a[i].x,a[i].y),dp[i]=i;
	for(int i=1;i<=n;++i)
	{
		info cur={{0.0,PI},{-PI,0.0}};
		for(int j=i+1;j<=n;++j)
		{
			double ang=atan2(a[j].y-a[i].y,a[j].x-a[i].x);
			if(cur.a.check(ang)||cur.b.check(ang)) trans[i][j]=true;
			cur.merge(calc(a[i],a[j],ang));
		}
	}
	for(int i=2;i<=n;++i)
	{
		info cur={{0.0,PI},{-PI,0.0}};
		for(int j=i-1;j>=1;--j)
		{
			double ang=atan2(a[j].y-a[i].y,a[j].x-a[i].x);
			if(trans[j][i]&&(cur.a.check(ang)||cur.b.check(ang))) chmin(dp[i],dp[j]+1);
			cur.merge(calc(a[i],a[j],ang));
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}

