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

const int N=400005;
const int mod=1000003;
template<typename _Tp1,typename _Tp2>inline void add(_Tp1 &a,_Tp2 b){(a+=b)>=mod&&(a-=mod);}
template<typename _Tp1,typename _Tp2>inline void sub(_Tp1 &a,_Tp2 b){(a-=b)<0&&(a+=mod);}
ll fac[N],inv[N],ifac[N],f[N],g1[N],g2[N],pwa[N],pwb[N];
ll ksm(ll a,ll b=mod-2){ll res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod,b>>=1;}return res;}
inline ll C(int n,int m)
{
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
void init(int n,int a,ll *g,ll *pw)
{
	if(a==1) for(int i=0;i<=n;++i) g[i]=C(i+i+1,i+1);
	else
	{
		ll inv=ksm(1-a+mod);
		g[0]=1,g[1]=(1+a+a)%mod;
		for(int i=2;i<=n;++i) g[i]=((g[i-1]+C(i+i,i)*pw[i]-C(i+i-1,i)*pw[i]-C(i+i,i)*pw[i+1])%mod+mod)*inv%mod;
	}
}
int main()
{
	fac[0]=fac[1]=inv[0]=inv[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<N;++i) fac[i]=fac[i-1]*i%mod,inv[i]=inv[mod%i]*(mod-mod/i)%mod,ifac[i]=ifac[i-1]*inv[i]%mod;
	int n,a,b,c;read(n,a,b,c),--n;
	pwa[0]=pwb[0]=1;
	for(int i=1;i<N;++i) pwa[i]=pwa[i-1]*a%mod,pwb[i]=pwb[i-1]*b%mod;
	init(n,a,g1,pwa),init(n,b,g2,pwb);
	f[0]=1;
	for(int i=1;i<=n;++i) f[i]=(f[i-1]+pwb[i]*g1[i]+pwa[i]*g2[i]-C(i+i,i)*pwa[i]*pwb[i]%mod+mod)%mod;
	int x;read(x);
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		read(x);
		add(ans,1ll*x*C(n+n-i-1,n-1)%mod*pwa[n]%mod*pwb[n-i]%mod);
	}
	read(x);
	for(int i=1;i<=n;++i)
	{
		read(x);
		add(ans,1ll*x*C(n+n-i-1,n-1)%mod*pwb[n]%mod*pwa[n-i]%mod);
	}
	add(ans,1ll*c*f[n-1]%mod);
	printf("%d\n",ans);
	return 0;
}

