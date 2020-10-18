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
int f[N][21],Log2[N],a[N];
inline int Query(int l,int r)
{
	int k=Log2[r-l+1];
	return f[l][k]&f[r-(1<<k)+1][k];
}
struct node{
	int val,opt;
};
std::vector<node> v[N];
std::map<int,int> mp;
int main()
{
	freopen("hack.in","r",stdin);
	freopen("hack.out","w",stdout);
	
	for(int i=2;i<N;++i) Log2[i]=Log2[i>>1]+1;
	int n;read(n);
	for(int i=1;i<=n;++i)
	{
		read(a[i]);
		f[i][0]=a[i];
	}
	for(int i=n;i>=1;--i) for(int j=1;j<=20&&(i+(1<<(j-1)))<=n;++j) f[i][j]=f[i][j-1]&f[i+(1<<(j-1))][j-1];
	for(int i=1;i<=n;++i) a[i]^=a[i-1];
	for(int i=1;i<=n;++i)
	{
		int cur=i;
		while(cur>=1)
		{
			int l=1,r=cur;
			int val=Query(cur,i);
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(Query(mid,i)==val) r=mid;
				else l=mid+1;
			}
			v[cur-1].pb({a[i]^val,1});
			if(l>1) v[l-2].pb({a[i]^val,-1});
			cur=l-1;
		}
	}
	ll ans=0;
	for(int i=0;i<=n;++i)
	{
		++mp[a[i]];
		for(auto it:v[i]) ans+=it.opt*mp[it.val];
	}
	printf("%lld\n",ans);
	return 0;
}

