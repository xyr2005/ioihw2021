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
int cnt[N];
int v1[N],p1,v2[N],p2;
int ans1[N],ans2[N];
int main()
{
	freopen("equal.in","r",stdin);
	freopen("equal.out","w",stdout);
	
	int n;read(n);
	int x;
	for(int i=1;i<=n;++i) read(x),++cnt[x];
	for(int i=1;i<N;++i)
	{
		if(cnt[i])
		{
			++ans1[0],++ans2[0];
			v2[++p2]=cnt[i];
			for(int j=i+i;j<N;j+=i)
			{
				if(cnt[j])
				{
					v1[++p1]=cnt[i];
					break;
				}
			}
		}
	}
	std::sort(v1+1,v1+p1+1),std::sort(v2+1,v2+p2+1);
	int cur=0;
	for(int i=1;i<=p1;++i) ans1[cur+=v1[i]]=-1;
	for(int i=1;i<=n;++i) ans1[i]+=ans1[i-1];
	cur=0;
	for(int i=1;i<=p2;++i) ans2[cur+=v2[i]]=-1;
	ans2[v2[1]]=0;
	for(int i=1;i<=n;++i) ans2[i]+=ans2[i-1];
	for(int i=0;i<=n;++i) printf("%d%c",min(ans1[i],ans2[i])," \n"[i==n]);
	return 0;
}
