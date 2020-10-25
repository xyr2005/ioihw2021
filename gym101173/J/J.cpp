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
std::map<int,std::vector<int>> mp[N];
std::map<int,int> c1[N],c2[N];
typedef std::pair<int,std::vector<int>> info;
inline ll getdis(int x,int y)
{
	auto it=c1[x].find(y);
	if(it==c1[x].end()) return INF;
	else return it->second;
}
inline ll GETDIS(int x,int y)
{
	auto it=c2[x].find(y);
	if(it==c2[x].end()) return INF;
	else return it->second;
}
int st[N],top;
info solve(const std::vector<int> o,int a,int b)
{
	int cnt=0;
	top=0;
	for(auto it:o)
	{
		if(it==b)
		{
			if(top&&st[top]==a) --top,++cnt;
			else st[++top]=it;
		}
		else st[++top]=it;
	}
	return mkpr(cnt,std::vector<int>{st+1,st+top+1});
}
ll calc(int s,int t,std::vector<int> o)
{
	ll cost0=getdis(s,t),cost1=getdis(t,s);
	ll cost01=GETDIS(s,t),cost10=GETDIS(t,s);
	auto $=[&](const std::vector<int> &v)->ll
	{
		int c1=std::accumulate(v.begin(),v.end(),0),c0=SZ(v)-c1;
		if((cost0>=INF&&c0)||(cost1>=INF&&c1)) return INF;
		return 1ll*cost0*c0+1ll*cost1*c1;
	};
	info a=solve(o,0,1);
	info b=solve(o,1,0);
	info c=solve(a.second,1,0);
	info d=solve(b.second,0,1);
	return min({
				$(o),
				a.first&&cost01==INF?INF:1ll*a.first*cost01+$(a.second),
				b.first&&cost10==INF?INF:1ll*b.first*cost10+$(b.second),
				(a.first&&cost01==INF)||(c.first&&cost10==INF)?INF:1ll*a.first*cost01+1ll*c.first*cost10+$(c.second),
				(b.first&&cost10==INF)||(d.first&&cost01==INF)?INF:1ll*b.first*cost10+1ll*d.first*cost01+$(d.second)
	});
}
int a[N];
int main()
{
	int n,m,d;read(n,d);
	for(int i=1;i<=d;++i)
	{
		read(a[i]);
		if(i>1)
		{
			int x=a[i-1],y=a[i];
			mp[min(x,y)][max(x,y)].pb(x>y);
		}
	}
	read(m);
	int x,y,p;char ch;
	while(m--)
	{
		read(x,y);
		ch=getchar();while(ch!='O'&&ch!='R') ch=getchar();
		read(p);
		if(ch=='O')
		{
			if(c1[x].find(y)==c1[x].end()) c1[x][y]=p;
			else chmin(c1[x][y],p);
		}
		else
		{
			if(c1[x].find(y)==c1[x].end()) c1[x][y]=p;
			else chmin(c1[x][y],p);
			if(c2[x].find(y)==c2[x].end()) c2[x][y]=p;
			else chmin(c2[x][y],p);
		}
	}
	ll ans=0;
	for(int __=1;__<=n;++__) for(auto ___:mp[__]) ans+=calc(__,___.first,___.second);
	printf("%lld\n",ans);
	return 0;
}

