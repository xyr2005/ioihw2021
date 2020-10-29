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

const int N=305;
int _[N][N],a[N][N],b[N][N];
int n,m;
bool solve()
{
	if(n<=2||m<=2) return false;
	for(int i=0;i<=n+1;++i) for(int j=0;j<=m+1;++j) _[i][j]=a[i][j];
	for(int i=2;i<n;++i) for(int j=2;j<m;++j) if(a[i-1][j-1]) for(int dx=-1;dx<=1;++dx) for(int dy=-1;dy<=1;++dy) a[i+dx][j+dy]^=1;
	int p1=0;
	for(int i=1;i<=n&&!p1;++i) for(int j=1;j<=m;++j) if(a[i][j]){p1=i;break;}
	if(p1)
	{
		for(int i=0;i<=n+1;++i) for(int j=0;j<=m+1;++j) a[j][i]=_[i][j];
		for(int i=2;i<m;++i) for(int j=2;j<n;++j) if(a[i-1][j-1]) for(int dx=-1;dx<=1;++dx) for(int dy=-1;dy<=1;++dy) a[i+dx][j+dy]^=1;
		int p2=0;
		for(int i=1;i<=m&&!p2;++i) for(int j=1;j<=n;++j) if(a[i][j]){p2=i;break;}
		for(int i=0;i<=n+1;++i) for(int j=0;j<=m+1;++j) a[i][j]=_[i][j];
		a[p1][p2]^=1;
	}
	else for(int i=0;i<=n+1;++i) for(int j=0;j<=m+1;++j) a[i][j]=_[i][j];
	for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) b[i][j]=0;
	for(int i=2;i<n;++i) for(int j=2;j<m;++j) if(a[i-1][j-1]){b[i-1][j-1]=1;for(int dx=-1;dx<=1;++dx) for(int dy=-1;dy<=1;++dy) a[i+dx][j+dy]^=1;}
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) if(a[i][j]){for(int i=0;i<=n+1;++i) for(int j=0;j<=m+1;++j) a[i][j]=_[i][j];return false;}
	n-=2,m-=2;
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) a[i][j]=b[i][j];
	while(true)
	{
		bool flag=true;
		for(int i=1;i<=m;++i) flag&=a[1][i]==0;
		if(!flag) break;
		--n;
		for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) a[i][j]=a[i+1][j];
	}
	while(true)
	{
		bool flag=true;
		for(int i=1;i<=m;++i) flag&=a[n][i]==0;
		if(!flag) break;
		--n;
	}
	while(true)
	{
		bool flag=true;
		for(int i=1;i<=n;++i) flag&=a[i][1]==0;
		if(!flag) break;
		--m;
		for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) a[i][j]=a[i][j+1];
	}
	while(true)
	{
		bool flag=true;
		for(int i=1;i<=n;++i) flag&=a[i][m]==0;
		if(!flag) break;
		--m;
	}
	return true;
}
int main()
{
	read(m,n);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			char ch=getchar();
			while(ch!='.'&&ch!='#') ch=getchar();
			a[i][j]=ch=='#';
		}
	}
	while(solve());
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j) printf("%c",a[i][j]?'#':'.');
		printf("\n");
	}
	return 0;
}

