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
typedef std::bitset<205> big;
big operator + (const big &a,const big &b)
{
	big c;
	int last=0;
	for(int i=0;i<=200;++i)
	{
		int tmp=last+(int)a[i]+(int)b[i];
		c[i]=tmp&1,last=tmp>>1;
	}
	return c;
}
int main()
{
	freopen("binary.in","r",stdin);
	freopen("binary.out","w",stdout);
	
	int n;read(n);
	std::vector<big> q;
	q.pb(big());
	big a;
	a[0]=1;
	for(int i=0;;++i)
	{
		std::vector<big> v;
		for(const auto &it:q) if(it[i]==0) v.pb(it);
		for(auto it:q)
		{
			if(it[i]) continue;
			v.pb(it=it+a);
			if(!--n)
			{
				for(int j=i;j>=0;--j) printf("%d",(int)it[j]);
				printf("\n");
				return 0;
			}
		}
		a=(a<<3)+(a<<1),q=v;
	}
	return 0;
}

