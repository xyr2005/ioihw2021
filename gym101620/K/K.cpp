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

const int N=505;
int a[N],cnt[9];
int v[5],c[5];
int dp[N][N][N];
struct node{
	int x,y,z;
}__[517];
int main()
{
	std::cin.tie(0),std::ios::sync_with_stdio(false);
	int n;std::cin>>n;
	std::string s;
	for(int i=1;i<=n;++i)
	{
		std::cin>>s;
		bool flag=true;
		for(int j=0;j<7;++j) flag&=s[j]==s[0];
		if(flag){--i,--n;continue;}
		std::vector<std::pair<std::string,int>> v;
		for(int j=0;j<7;++j) v.pb(mkpr(s.substr(j,7-j)+s.substr(0,j),j));
		std::sort(v.begin(),v.end());
		a[i]=v.back().second;
	}
	int sum=0;
	for(int i=n;i>=1;--i) a[i]-=a[i-1],a[i]=(a[i]%7+7)%7,sum+=a[i];
	sum%=7;
	a[++n]=(7-sum)%7;
	int ans=n;
	for(int i=1;i<=n;++i) ++cnt[a[i]];
	ans-=cnt[0],cnt[0]=0;
	for(int i=1;i<=3;++i)
	{
		int tmp=min(cnt[i],cnt[7-i]);
		cnt[i]-=tmp,cnt[7-i]-=tmp;
		ans-=tmp;
	}
	int pos=0;
	for(int i=1;i<7;++i) if(cnt[i]) v[pos]=i,c[pos]=cnt[i],++pos;
	memset(dp,-63,sizeof(dp));
	dp[0][0][0]=0;
	pos=0;
	for(int x=0;x<=7;++x)
	{
		for(int y=0;y<=7;++y)
		{
			for(int z=0;z<=7;++z)
			{
				if((x||y||z)&&(x*v[0]+y*v[1]+z*v[2])%7==0)
				{
					bool flag=true;
					for(int i=1;i<=pos;++i) flag&=x>__[i].x||y>__[i].y||z>__[i].z;
					if(flag) __[++pos]={x,y,z};
				}
			}
		}
	}
	for(int i=0;i<=c[0];++i)
	{
		for(int j=0;j<=c[1];++j)
		{
			for(int k=0;k<=c[2];++k)
			{
				for(int _=1;_<=pos;++_)
				{
					int x=__[_].x,y=__[_].y,z=__[_].z;
					if(i>=x&&j>=y&&k>=z) chmax(dp[i][j][k],dp[i-x][j-y][k-z]+1);
				}
			}
		}
	}
	printf("%d\n",ans-dp[c[0]][c[1]][c[2]]);
	return 0;
}

