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
char s[N];
int id[N],cnt[20][20];
inline bool check(int i)
{
	return i!='a'&&i!='e'&&i!='i'&&i!='o'&&i!='u'&&i!='w'&&i!='y';
}
int main()
{
	freopen("consonant.in","r",stdin);
	freopen("consonant.out","w",stdout);
	
	int n=read_str(s+1);
	int _=0;
	for(int i=0;i<26;++i) if(check(i+97)) id[i]=_++;
	for(int i=1;i<n;++i) if(check(s[i])&&check(s[i+1])) ++cnt[id[s[i]-97]][id[s[i+1]-97]];
	int ans=0,res=0;
	for(int st=0;st<1<<_;++st)
	{
		int tmp=0;
		for(int i=0;i<_;++i) for(int j=0;j<_;++j) tmp+=(((st>>i)&1)^((st>>j)&1))*cnt[i][j];
		if(tmp>ans) ans=tmp,res=st;
	}
	for(int i=1;i<=n;++i) if((res>>(id[s[i]-97]))&1) s[i]-=32;
	printf("%s\n",s+1);
	return 0;
}

