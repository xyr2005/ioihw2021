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
int n;
ull b[N],s;
namespace sub1
{
int hf;
struct node{
	ull val,st;
	inline bool operator < (const node &o)const
	{
		return val<o.val;
	}
}A[(1<<21)+5],B[(1<<21)+5];
ull sum[1<<21];
void MAIN()
{
	hf=n>>1;
	for(int i=1;i<=hf;++i) sum[1<<(i-1)]=b[i];
	for(int st=0;st<1<<hf;++st)
	{
		sum[st]=sum[lowbit(st)]+sum[st^lowbit(st)];
		A[st]={sum[st],(ull)st};
	}
	memset(sum,0,sizeof(sum));
	for(int i=hf+1;i<=n;++i) sum[1<<(i-hf-1)]=b[i];
	for(int st=0;st<1<<(n-hf);++st)
	{
		sum[st]=sum[lowbit(st)]+sum[st^lowbit(st)];
		B[st]={sum[st],((ull)st)<<hf};
	}
	std::sort(B,B+(1<<(n-hf)));
	for(int i=0;i<1<<hf;++i)
	{
		ull tar=s-A[i].val;
		int p=std::lower_bound(B,B+(1<<(n-hf)),(node){tar,0})-B;
		if(p<(1<<(n-hf))&&B[p].val==tar)
		{
			ull ans=A[i].st|B[p].st;
			for(int i=0;i<n;++i) putchar(48+((ans>>i)&1));
			return;
		}
	}
}
}
namespace sub2
{
ull a[N];
ull ksm(ull a,ull b=(1ULL<<63)-1ULL){ull res=1;while(b){if(b&1)res=res*a;a=a*a,b>>=1;}return res;}
int LOG2(ull x)
{
	for(int i=63;i>=0;--i) if((x>>i)&1) return i;
	return -1;
}
void MAIN()
{
	int _=LOG2(lowbit(b[1]));
	ull ans=0;
	for(ull a1=1ULL<<_;a1<=1ULL<<(64-n);a1+=2ULL<<_)
	{
		ull A=a1>>_,B=b[1]>>_;
		assert(A%2==1);
		ull R=ksm(A)*B;
		for(ull t=0;t<1ULL<<_;++t,R+=1ULL<<(64-_))
		{
			if(R%2==0) continue;
			ll r=ksm(R);
			for(int i=1;i<=n;++i) a[i]=b[i]*r;
			bool flag=true;
			ull sum=0;
			for(int i=1;i<=n;++i)
			{
				if(a[i]<=sum||(ull)(sum+a[i])<a[i])
				{
					flag=false;
					break;
				}
				sum+=a[i];
			}
			if(!flag) continue;
			s*=r;
			for(int i=n;i>=1;--i) if(s>=a[i]) s-=a[i],ans|=1ull<<(i-1);
			for(int i=0;i<n;++i) putchar(48+((ans>>i)&1));
			return;
		}
	}
	putchar('\n');
}
}
int main()
{
	read(n);
	for(int i=1;i<=n;++i) read(b[i]);
	read(s);
	if(n<=42) sub1::MAIN();
	else sub2::MAIN();
	return 0;
}

