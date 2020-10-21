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

const int N=100005;
const int MAX_DEP=12;
const int SIZE=1<<MAX_DEP;
int pw[35];
ll sum[SIZE+5][SIZE+5],s[SIZE+5][SIZE+5];
int seq[SIZE+5],pos,dep[SIZE+5];
void dfs(int x,int fa,int dep)
{
	::dep[x]=dep;
	if(++dep==MAX_DEP)
	{
		seq[pos++]=fa;
		return;
	}
	dfs(x<<1,x,dep),dfs(x<<1|1,x,dep);
	if(fa) seq[pos++]=fa;
}
void init()
{
	dfs(1,0,0);
	for(int i=1;i<=pos;++i) for(int j=0;j<pos;++j) sum[i][j%i]+=seq[j],s[i][j%i]+=1<<dep[seq[j]];
}
int k;
inline int calc(int sum,int a,int d)
{
	if(sum>a) return 1+(sum-a-1)/d;
	return 0;
}
ll ans;
void solve(int x,int dep,int a,int d,int m)
{
	if(m<=0) return;
	if(++dep==k) return;
	if(lowbit(x+1)==x+1)
	{
		int tmp=calc((1<<(k-dep))-1-1,a,d);
		solve(x<<1,dep,a,d,min(tmp,m));
		a-=(1<<(k-dep))-1-1;
		if(a<0)
		{
			a%=d;
			if(a) a+=d;
		}
		m-=min(tmp,m);
		if(m<=0) return;
		if(a==0) ans+=x,a=d-1,--m;else --a;
		if(m<=0) return;
		if(a==0) ans+=x<<1|1,a=d-1,--m;else --a;
		if(m<=0) return;
		tmp=calc((1<<(k-dep))-1-1,a,d);
		solve(x<<1|1,dep,a,d,min(tmp,m));
	}
	else
	{
		if(dep+MAX_DEP==k+1)
		{
			int tmp=calc(pos,a,d);
			if(d<=pos&&tmp<=m&&a<d)
			{
				ans+=1ll*(x-1)*s[d][a];
				ans+=sum[d][a];
			}
			else for(int cur=a;m--&&cur<pos;cur+=d) ans+=seq[cur]+1ll*(x-1)*(1<<::dep[seq[cur]]);
			return;
		}
		int tmp=calc(max(0,(1<<(k-dep))-1-1),a,d);
		solve(x<<1,dep,a,d,min(tmp,m));
		a-=(1<<(k-dep))-1-1;
		if(a<0)
		{
			a%=d;
			if(a) a+=d;
		}
		m-=min(tmp,m);
		if(m<=0) return;
		if(a==0) ans+=x,a=d-1,--m;else --a;
		if(m<=0) return;
		
		tmp=calc((1<<(k-dep))-1-1,a,d);
		solve(x<<1|1,dep,a,d,min(tmp,m));
		
		a-=(1<<(k-dep))-1-1;
		if(a<0)
		{
			a%=d;
			if(a) a+=d;
		}
		m-=min(tmp,m);
		if(m<=0) return;
		if(a==0) ans+=x,a=d-1,--m;else --a;
	}
}
void MAIN()
{
	int a,d,m;read(a,d,m);
	ans=0,solve(1,0,a-1,d,m);
	printf("%lld\n",ans);
}
int main()
{
	init();
	int q;read(k,q);
	while(q--) MAIN();
	return 0;
}

