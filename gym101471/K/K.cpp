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
std::string s[11];
int _,nxt[N];
char t[N];
std::string calc(std::string s)
{
	int n=SZ(s);
	for(int i=0;i<n;++i) t[i+1]=s[i];
	t[n+1]=0;
	int j=0;
	for(int i=2;i<=n;++i)
	{
		while(j&&t[j+1]!=t[i]) j=nxt[j];
		if(t[j+1]==t[i]) ++j;
		nxt[i]=j;
	}
	std::string ans;
	ans.resize(n);
	int cur=n;
	while(cur)
	{
		if(n*2-cur<=_) ans[cur-1]=1;
		cur=nxt[cur];
	}
	std::reverse(ans.begin(),ans.end());
	return ans;
}
int main()
{
	std::ios::sync_with_stdio(false),std::cin.tie(0);
	int n,m;std::cin>>n>>m;
	_=n;
	std::vector<std::pair<std::string,int>> v;
	for(int i=0;i<m;++i)
	{
		std::cin>>s[i];
		v.pb({calc(s[i]),i});
	}
	std::sort(v.begin(),v.end());
	for(auto it:v) printf("%s\n",s[it.second].c_str());
	return 0;
}

