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

const int N=(1<<13)+5;
bool f[1005][N],g[1005][N];
int pre[1005][N],a[N];
int hb[N];
void print(int n,int st)
{
	if(!n) return;
	print(n-1,pre[n][st]);
	putchar(g[n][st]?'r':'l');
}
void MAIN()
{
	int n;read(n);
	int x,sum=0;
	f[0][0]=true;
	for(int i=1;i<=n;++i)
	{
		read(x);
		memset(f[i],0,sum+x+3);
		for(int j=0;j<=sum;++j)if(f[i-1][j])
		{
			int a=j,b=sum-j;
			if(!a||x<=lowbit(a))
			{
				a+=x;
				if(hb[a]==hb[b])
				{
					int t=1<<hb[a];
					a+=t;
					f[i][a]=true,pre[i][a]=j,g[i][a]=0;
					a-=t<<1;
				}
				f[i][a]=true,pre[i][a]=j,g[i][a]=0;
			}
			a=j,b=sum-j;
			if(!b||x<=lowbit(b))
			{
				b+=x;
				if(hb[a]==hb[b])
				{
					int t=1<<hb[a];
					a-=t;
					f[i][a]=true,pre[i][a]=j,g[i][a]=1;
					a+=t<<1;
				}
				f[i][a]=true,pre[i][a]=j,g[i][a]=1;
			}
		}
		sum+=x;
		for(int j=0;j<=sum;++j)if(f[i][j])
		{
			int a=j,b=sum-j;
			if(!a||!b) f[i][a|b]=true,g[i][a|b]=g[i][j],pre[i][a|b]=pre[i][j];
			else
			{
				if(hb[a]>hb[b]) b+=1<<hb[a],a-=1<<hb[a];
				else a+=1<<hb[b],b-=1<<hb[b];
				f[i][a]=f[i][j],g[i][a]=g[i][j],pre[i][a]=pre[i][j];
			}
		}
	}
	if(lowbit(sum)==sum&&f[n][sum]){print(n,sum);return (void)putchar('\n');}
	puts("no");
}
int main()
{
	for(int i=0;i<=1<<13;++i) for(int j=13;j>=0;--j) if((i>>j)&1){hb[i]=j;break;}
	int _;read(_);
	while(_--) MAIN();
	return 0;
}

