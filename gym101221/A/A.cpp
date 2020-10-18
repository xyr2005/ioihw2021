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

const int N=115;
void out(int a,int b){printf("%d to %d\n",a,b);}
int tag;
void solve(int l,int r)
{
	if(r-l+1<=14)
	{
		int len=(r-l+1)>>1;
		tag=len;
		if(len==4)
		{
			out(r-2,l-2);
			out(l+2,r-2);
			out(l-1,l+2);
			out(r-1,l-1);
		}
		else if(len==5)
		{
			out(r-2,l-2);
			out(l+2,r-2);
			out(l+5,l+2);
			out(l-1,l+5);
			out(r-1,l-1);
		}
		else if(len==6)
		{
			out(l+9,l-2);
			out(l+6,l+9);
			out(l+1,l+6);
			out(l+5,l+1);
			out(l-1,l+5);
			out(l+10,l-1);
		}
		else if(len==7)
		{
			out(l+7,l-2);
			out(l+4,l+7);
			out(l+11,l+4);
			out(l+2,l+11);
			out(l+8,l+2);
			out(l-1,l+8);
			out(l+12,l-1);
		}
		return;
	}
	out(r-2,l-2);
	out(l+2,r-2);
	solve(l+4,r-4);
}
int main()
{
	int n;read(n);
	if(n==3)
	{
		int l=-2;
		out(l+4,l+1);
		out(l+7,l+4);
		out(l+5,l-1);
		return 0;
	}
	solve(1,n*2);
	int cur=-1+(n+tag);
	int l=0,r=cur+4;
	int cnt=(n-tag)/4;
	while(cnt--)
	{
		out(l,cur);
		cur=l,l+=4;
		out(r,cur);
		cur=r,r+=4;
	}
	return 0;
}
