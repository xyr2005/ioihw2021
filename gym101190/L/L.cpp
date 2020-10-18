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

const int N=845;
bool check(int x)
{
	for(int i=2;i*i<=x;++i) if(!(x%i)) return false;
	return true;
}
int a[N],pos,val[N];
const int MAXN=6505;
const ll LIMIT=1000000000000000001LL;
ll f[N][MAXN],g[N][MAXN];
int calc(int x){int ans=0;while(x)++ans,x/=10;return ans;}
void init()
{
	int qwq=0;
	for(int i=2;i<MAXN;++i) if(check(i)) a[++pos]=i,qwq+=i,val[pos]=calc(i)+2;
	f[pos+1][0]=1,g[pos+1][0]=0;
	for(int i=pos;i>=1;--i)
	{
		for(int j=0;j<MAXN;++j)
		{
			f[i][j]=f[i+1][j]+(j>=a[i]?f[i+1][j-a[i]]:0),g[i][j]=g[i+1][j]+(j>=a[i]?g[i+1][j-a[i]]+val[i]*f[i+1][j-a[i]]:0);
			chmin(f[i][j],LIMIT),chmin(g[i][j],LIMIT);
		}
	}
}
std::string ans;
std::string NtoS(int x)
{
	static int st[21];
	int top=0;std::string s;
	while(x) st[++top]=x%10,x/=10;
	while(top) s.pb(st[top--]+48);
	return s;
}
void print(std::vector<int> v,ll l,ll r)
{
	std::string s;
	s.pb('[');
	for(int i=0;i+1<SZ(v);++i) s+=NtoS(v[i]),s+=", ";
	s+=NtoS(v.back())+"], ";
	ans+=s.substr(l,r-l+1);
}
void solve(ll sum,int pos,ll l,ll r,ll pre,std::vector<int> res)
{
	if(l>r) return;
	if(pos==::pos+1)
	{
		if(!sum) print(res,l,r);
		return;
	}
	ll tmp=sum>=a[pos]?(g[pos+1][sum-a[pos]]+val[pos]*f[pos+1][sum-a[pos]]+pre*f[pos+1][sum-a[pos]]):0;
	if(tmp<=l) return solve(sum,pos+1,l-tmp,r-tmp,pre,res);
	std::vector<int> v(res);v.pb(a[pos]);
	solve(sum-a[pos],pos+1,l,min(r,tmp-1),pre+val[pos],v);
	solve(sum,pos+1,0,r-tmp,pre,res);
}
int main()
{
	freopen("list.in","r",stdin);
	freopen("list.out","w",stdout);
	
	init();
	ll a,b;read(a,b);
	ll sum=0;
	for(int i=1;i<MAXN;++i)
	{
		ll tmp=min(LIMIT,g[1][i]+2ll*f[1][i]);
		ll l=sum+1,r=sum+tmp;
		solve(i,1,max(0LL,a-l),min((ll)r-l,b-l),2,std::vector<int>());
		sum+=tmp;
		chmin(sum,LIMIT);
	}
	printf("%s\n",ans.c_str());
	return 0;
}

