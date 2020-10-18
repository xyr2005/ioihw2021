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

const int N=105;
int a[N][N],n,m;
std::vector<pi> ans;
inline int getid(int x,int y)
{
	return (x-1)*m+y;
}
void R(int x)
{
	ans.pb({x,0});
	std::reverse(a[x]+1,a[x]+m+1);
}
void C(int x)
{
	static int tmp[N];
	ans.pb({x,1});
	for(int i=1;i<=n;++i) tmp[i]=a[i][x];
	for(int i=1;i<=n;++i) a[i][x]=tmp[n-i+1];
}
void f(int x,int a,int b)
{
	R(x),C(a),C(b);
	R(x),C(a),C(b);
}
void g(int y,int a,int b)
{
	C(y),R(a),R(b);
	C(y),R(a),R(b);
}
void rot(int x1,int y1)
{
	int x2=n-x1+1,y2=m-y1+1;
	R(x2),C(y2),R(x2),C(y2);
}
bool sol1(int x1,int y1)
{
	int x2=n-x1+1,y2=m-y1+1;
	if(x1<x2&&y1<y2)
	{
		if(a[x1][y2]==getid(x1,y1)) f(x1,y1,y2);
		else if(a[x2][y1]==getid(x1,y1)) g(y1,x1,x2);
		else if(a[x2][y2]==getid(x1,y1)) f(x1,y1,y2),g(y1,x1,x2);
		while(a[x1][y2]!=getid(x1,y2)) rot(x1,y1);
	}
	return a[x2][y1]==getid(x2,y1);
}
bool sol2(int x1,int y1)
{
	int x2=n-x1+1,y2=m-y1+1;
	if(x1<x2&&y1<y2)
	{
		if(a[x1][y2]==getid(x1,y1)) f(x1,y1,y2);
		else if(a[x2][y1]==getid(x1,y1)) g(y1,x1,x2);
		else if(a[x2][y2]==getid(x1,y1)) f(x1,y1,y2),g(y1,x1,x2);
		while(a[x2][y1]!=getid(x2,y1)) rot(x1,y1);
	}
	return a[x1][y2]==getid(x1,y2);
}
bool check()
{
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) if(a[i][j]!=getid(i,j)) return false;
	return true;
}
void MAIN()
{
	ans.clear();
	read(m,n);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) read(a[i][j]);
	if(n==1||m==1)
	{
		if(check()) printf("POSSIBLE 0\n");
		else
		{
			if(n==1)
			{
				R(1);
				if(!check()) return (void)puts("IMPOSSIBLE");
				printf("POSSIBLE %d ",SZ(ans));
				for(auto it:ans)
				{
					if(!it.second) printf("R%d ",it.first);
					else printf("C%d ",it.first);
				}
				printf("\n");
			}
			else
			{
				C(1);
				if(!check()) return (void)puts("IMPOSSIBLE");
				printf("POSSIBLE %d ",SZ(ans));
				for(auto it:ans)
				{
					if(!it.second) printf("R%d ",it.first);
					else printf("C%d ",it.first);
				}
				printf("\n");
			}
			return;
		}
		return;
	}
	int id=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			++id;
			if(a[i][j]!=id&&a[n-i+1][j]!=id&&a[n-i+1][m-j+1]!=id&&a[i][m-j+1]!=id) return (void)puts("IMPOSSIBLE");
		}
	}
	if(!sol1(1,1)) R(n);
//	assert(a[1][1]==getid(1,1)&&a[1][m]==getid(1,m)&&a[n][1]==getid(n,1)&&a[n][m]==getid(n,m));
	for(int i=2;i<m;++i) if(!sol2(1,i)) C(m-i+1);
	for(int i=2;i<n;++i) if(!sol1(i,1)) R(n-i+1);
	for(int i=2;i<n;++i) for(int j=2;j<m;++j) if(!sol1(i,j)) return (void)puts("IMPOSSIBLE");
//	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) assert(a[i][j]==getid(i,j));
	printf("POSSIBLE %d ",SZ(ans));
	for(auto it:ans)
	{
		if(!it.second) printf("R%d ",it.first);
		else printf("C%d ",it.first);
	}
	printf("\n");
}
int main()
{

	int _;read(_);
	while(_--) MAIN();
	return 0;
}
