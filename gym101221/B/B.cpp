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

const int N=255;
struct node{
	int t,dt;
}b[N];
std::vector<node> a[10005];
struct Node{
	int val,id;
	inline bool operator < (const Node &o)const
	{
		return val<o.val;
	}
};
std::priority_queue<Node> q;
int n,m,_;
std::pair<double,double> calc(double mid)
{
	double A=0,B=0;
	int maxx=-1e9;
	for(int i=1;i<=m;++i)
	{
		if(b[i].t>=mid)
		{
			if(b[i].dt!=0)
			{
				double tmp=(double)(b[i].t-mid)/b[i].dt;
				A+=tmp,B+=tmp*b[i].t-b[i].dt*tmp*tmp/2.0;
			}
			else chmax(maxx,b[i].t);
		}
	}
	if(maxx>=0) B+=(_-A)*maxx,A=_;
	return {A,B};
}
ll dp[10005],t[10005];
int main()
{
	int d,w;read(d,w);
	int x,y,z;
	char opt;
	for(int i=1;i<=d;++i)
	{
		do{opt=getchar();}while(opt!='C'&&opt!='D');
		if(opt=='D') read(x,y,z),a[x].pb({y,z});
		else read(x,y),b[++m]={x,y};
	}
	memset(dp,-63,sizeof(dp)),dp[0]=0;
	for(int i=1;i<=w;++i)
	{
		if(a[i].empty()) continue;
		while(!q.empty()) q.pop();
		for(int j=0;j<SZ(a[i]);++j) q.push({a[i][j].t,j});
		int limit=w/i;
		ll qwq=0;
		memcpy(t,dp,(w+1)<<3);
		for(int j=1;j<=limit&&!q.empty();++j)
		{
			Node x=q.top();q.pop();
			qwq+=x.val;
			for(int k=0;k+i*j<=w;++k) chmax(t[k+i*j],dp[k]+qwq);
			q.push({x.val-a[i][x.id].dt,x.id});
		}
		memcpy(dp,t,(w+1)<<3);
	}
	double ans=-1e18;
	for(int i=0;i<=w;++i)
	{
		if(dp[i]<-1e15) continue;
		double l=-1e8,r=1e8;
		int T=80;
		_=w-i;
		while(T--)
		{
			double mid=(l+r)/2.0;
			if(calc(mid).first>=w-i) l=mid;
			else r=mid;
		}
		std::pair<double,double> tmp=calc(l);
		if(abs(tmp.first+i-w)<=1e-6) chmax(ans,calc(l).second+(double)dp[i]);
	}
	if(ans<-1e15) puts("impossible");
	else printf("%.8lf\n",ans);
	return 0;
}

