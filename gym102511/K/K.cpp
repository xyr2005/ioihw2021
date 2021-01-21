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
int x[N],r[N],p[N];
int l[27],pos,to[105],b[27][105],c[27];
double f[N];
bool check(int x){for(int i=2;i*i<=x;++i)if(!(x%i))return false;return true;}
int main()
{
	to[1]=1;
	for(int i=2;i<=100;++i)if(check(i))
	{
		int x=i;while(x*i<=100) x*=i;
		l[++pos]=x;x=i;while(x*i<=100) to[x]=pos,x*=i;
		to[x]=pos;
	}
	int n;read(n);
	for(int i=1;i<=n;++i) read(x[i],r[i],p[i]),p[i]+=r[i];
	for(int a=0;a<2520;++a)
	{
		double s=1;
		for(int i=1;i<=pos;++i){c[i]=l[i];for(int j=0;j<l[i];++j) b[i][j]=1;}
		for(int i=1;i<=n;++i)
		{
			int t=p[i]/gcd(p[i],2520),limit=l[to[t]]/t;
			if(c[to[t]])
			{
				s/=(double)c[to[t]];
				for(int k=0;k<t;++k) if((2520*k+a+x[i])%p[i]<r[i]) for(int j=0;j<limit;++j) b[to[t]][j*t+k]=0;
				s*=(double)(c[to[t]]=std::accumulate(b[to[t]],b[to[t]]+l[to[t]],0));
			}
			f[i]+=s;
		}
	}
	f[0]=1;for(int i=1;i<=n;++i) f[i]/=2520.0;
	for(int i=0;i<=n;++i) printf("%.12lf\n",f[i]-f[i+1]);
	return 0;
}

