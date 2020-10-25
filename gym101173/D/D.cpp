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

const int N=9;
int f[N][N];
pi bel[40005];
void solve(int a,int b,std::vector<int> v)
{
	if(v.empty()) return;
	if(a==6&&b==6) return;
	if(a==5&&b==6)
	{
		if(SZ(v)==1) printf("5 6 D 1\n");
		else
		{
			if(v[0]>v[1]) printf("5 6 D 2\n");
			else printf("5 6 D 1\n5 6 D 1\n");
		}
		return;
	}
	if(a==6&&b==5)
	{
		if(SZ(v)==1) printf("6 5 R 1\n");
		else
		{
			if(v[0]>v[1]) printf("6 5 R 2\n");
			else printf("6 5 R 1\n6 5 R 1\n");
		}
		return;
	}
	std::vector<int> vals[7][7];
	std::vector<int> t(v);std::sort(t.begin(),t.end());
	for(auto &&it:v) it=std::lower_bound(t.begin(),t.end(),it)-t.begin();
	int cnt=SZ(v)-1;
	for(int i=6;i>=a;--i) for(int j=6;j>=b;--j)
	{
		if(i==a&&j==b) continue;
		int val=f[6-i+1][6-j+1];
		while(val--) if(cnt>=0) bel[cnt--]={i,j};
	}
	for(int i=SZ(v)-1;i>=0;--i)
	{
		vals[bel[v[i]].first][bel[v[i]].second].pb(v[i]);
		int x=a,y=b;
		while(x<bel[v[i]].first) printf("%d %d D 1\n",x++,y);
		while(y<bel[v[i]].second) printf("%d %d R 1\n",x,y++);
	}
	for(int i=6;i>=a;--i) for(int j=6;j>=b;--j) if(i!=a||j!=b) solve(i,j,vals[i][j]);
}
int main()
{
	for(int i=1;i<=6;++i)
	{
		for(int j=1;j<=6;++j)
		{
			f[i][j]=0;
			for(int x=1;x<=i;++x) for(int y=1;y<=j;++y) if(x!=i||y!=j) f[i][j]+=f[x][y];
			if(i==1&&j==1) f[i][j]=1;
			if(i==2||j==2) chmax(f[i][j],2);
		}
	}
	int n;read(n);
	std::vector<int> v(n);
	for(auto &&it:v) read(it);
	solve(1,1,v);
	return 0;
}

