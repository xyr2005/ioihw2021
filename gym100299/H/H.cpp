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

const int N=1000005;
struct seg{
	int l,r;
	inline bool operator == (const seg &o)const
	{
		return r==o.r;
	}
	inline bool operator < (const seg &o)const
	{
		return r<o.r;
	}
	inline bool check(){return l==r;}
	inline void merge(const seg &o)
	{
		chmin(l,o.l),chmax(r,o.r);
	}
};
struct node{
	seg x,y,z;
	inline void get()
	{
		read(x.l,y.l,z.l,x.r,y.r,z.r);
		if(x.l>x.r) std::swap(x.l,x.r);
		if(y.l>y.r) std::swap(y.l,y.r);
		if(z.l>z.r) std::swap(z.l,z.r);
	}
};
std::vector<node> v[3];
bool check(const std::vector<node> &a,const std::vector<node> &b)
{
	seg x={inf,-inf};
	for(auto it:a) x.merge(it.x);
	for(auto it:b) if(!(it.x.l<x.l&&it.x.r>x.r)) return false;
	x={inf,-inf};
	for(auto it:b) x.merge(it.y);
	for(auto it:a) if(!(it.y.l<x.l&&it.y.r>x.r)) return false;
	int maxl=-inf,minr=inf;
	for(auto it:a) chmin(minr,it.z.r),chmax(maxl,it.z.l);
	for(auto it:b) if(it.z.r<maxl||it.z.l>minr) return false;
	maxl=-inf,minr=inf;
	for(auto it:b) chmin(minr,it.z.r),chmax(maxl,it.z.l);
	for(auto it:a) if(it.z.r<maxl||it.z.l>minr) return false;
	std::vector<std::pair<seg,int>> v;
	for(auto it:a) v.pb({it.z,0});
	for(auto it:b) v.pb({it.z,1});
	std::sort(v.begin(),v.end());
	int max0=-inf,max1=-inf;
	for(auto it:v)
	{
		if(it.second==0)
		{
			if(max1>it.first.l) return false;
			chmax(max0,it.first.l);
		}
		else
		{
			if(max0>it.first.l) return false;
			chmax(max1,it.first.l);
		}
	}
	return true;
}
void MAIN()
{
	v[0].clear(),v[1].clear(),v[2].clear();
	int n;read(n);
	node x;
	for(int i=1;i<=n;++i)
	{
		x.get();
		v[x.x.check()?0:x.y.check()?1:2].pb(x);
	}
	int tag1=check(v[0],v[1]);
	for(auto &&it:v[0]) std::swap(it.y,it.z);
	for(auto &&it:v[2]) std::swap(it.y,it.z);
	int tag2=check(v[0],v[2]);
	for(auto &&it:v[2]) std::swap(it.y,it.z);
	
	for(auto &&it:v[1]) std::swap(it.x,it.z),std::swap(it.x,it.y);
	for(auto &&it:v[2]) std::swap(it.x,it.z),std::swap(it.x,it.y);
	int tag3=check(v[1],v[2]);
	if((int)v[0].empty()+(int)v[1].empty()+(int)v[2].empty()>=2) puts("NO");
	else
	{
		if(v[0].empty())
		{
			if(tag3) puts("YES");
			else puts("NO");
		}
		else if(v[1].empty())
		{
			if(tag2) puts("YES");
			else puts("NO");
		}
		else if(v[2].empty())
		{
			if(tag1) puts("YES");
			else puts("NO");
		}
		else
		{
			if(tag1+tag2+tag3>=2) puts("YES");
			else puts("NO");
		}
	}
}
int main()
{
	int _;read(_);
	while(_--) MAIN();
	return 0;
}

