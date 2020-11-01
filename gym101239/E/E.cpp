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

const int N=4005;
std::string s[N],a[N],b[N],c[N];
bool check(const std::string &s,const std::string &t) // t in s
{
	int cur=0;
	for(int i=0;i<SZ(s)&&cur<SZ(t);++i) if(t[cur]==s[i]) ++cur;
	return cur==SZ(t);
}
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int n;std::cin>>n;
	std::string t;std::cin>>t;
	for(int i=0;i<n;++i)
	{
		std::cin>>s[i];
		if(!check(t,s[i])) return puts("impossible"),0;
	}
	std::sort(s,s+n,[&](const std::string &a,const std::string &b)->bool{return SZ(a)<SZ(b);});
	int p1=0,p2=0,p3=0;
	for(int i=0;i<n;++i)
	{
		if(p3)
		{
			if(check(s[i],c[p3])) c[++p3]=s[i];
			else
			{
				if(check(s[i],a[p1]))
				{
					a[++p1]=s[i];
					for(int j=1;j<=p3;++j) b[++p2]=c[j];
					p3=0;
				}
				else if(check(s[i],b[p2]))
				{
					b[++p2]=s[i];
					for(int j=1;j<=p3;++j) a[++p1]=c[j];
					p3=0;
				}
				else return puts("impossible"),0;
			}
		}
		else
		{
			bool f1=!p1||check(s[i],a[p1]);
			bool f2=!p2||check(s[i],b[p2]);
			if(f1&&f2) c[++p3]=s[i];
			else if(f1) a[++p1]=s[i];
			else if(f2) b[++p2]=s[i];
			else return puts("impossible"),0;
		}
	}
	if(p3) for(int j=1;j<=p3;++j) b[++p2]=c[j];
	printf("%d %d\n",p1,p2);
	for(int i=1;i<=p1;++i) printf("%s\n",a[i].c_str());
	for(int i=1;i<=p2;++i) printf("%s\n",b[i].c_str());
	return 0;
}

