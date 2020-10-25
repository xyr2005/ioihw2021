// Author -- xyr2005

#include<bits/stdc++.h>
#include "sort.h"
namespace __grader__
{
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

const int N=10005;
int a[N],b[N],A,B;
int cnt;
char Query(int x,int y)
{
	assert(1<=x&&x<=A);
	assert(1<=y&&y<=B);
	++cnt;
	return a[x]>b[y]?'>':'<';
}
int main()
{
	int n;read(n);
	A=n>>1,B=n-A;
	for(int i=1;i<=A;++i) read(a[i]);
	for(int i=1;i<=B;++i) read(b[i]);
	cnt=0;
	std::vector<int> ans=MAIN(n);
	for(auto it:ans) printf("%d ",it);
	printf("\n");
	fprintf(stderr,"%d attempts\n",cnt);
	return 0;
}
}
char query(int x,int y){return __grader__::Query(x,y);}
int main(){return __grader__::main();}
