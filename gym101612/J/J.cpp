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
const int S=250;
int a[N],n;
int bel[N],L[N/S+5],R[N/S+5];
ll s1[N],s2[N];
struct node{
	ll x,y;
	int id;
	inline bool operator < (const node &o)const{return x>o.x;}
};
struct BLOCK{
	int siz;
	ll tag1,tag2;
	node val[S+5];
	int q[S+5],_l,_r;
	inline double Slope(int i,int j)
	{
		if(val[j].x-val[i].x==0) return val[j].y>val[i].y?1e18:-1e18;
		return (double)(val[j].y-val[i].y)/(val[i].x-val[j].x);
	}
	void rebuild()
	{
		std::sort(val,val+siz);
		_l=1,_r=0;
		for(int i=0;i<siz;++i)
		{
			while(_r-_l>=1&&Slope(q[_r-1],q[_r])<=Slope(q[_r],i)) --_r;
			q[++_r]=i;
		}
	}
	inline std::pair<ll,int> calc(const node &o,ll a,ll b)
	{
		return mkpr(a*(o.x+tag1)+b*(o.y+tag2),-o.id);
	}
	std::pair<ll,int> Query(ll a,ll b)
	{
		int l=_l,r=_r;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(calc(val[q[mid]],a,b)>=calc(val[q[mid+1]],a,b)) r=mid;
			else l=mid+1;
		}
		return calc(val[q[l]],a,b);
	}
}b[N/S+5];
int max_block;
void build()
{
	int cur=0;
	for(int l=1,r=S;l<=n;l+=S,r+=S)
	{
		chmin(r,n),++cur,b[cur].siz=r-l+1,L[cur]=l,R[cur]=r;
		for(int k=l;k<=r;++k) bel[k]=cur,b[cur].val[k-l]={s1[k],s2[k],k};
		b[cur].rebuild();
	}
	max_block=cur;
}
void Update(int pos,ll A,ll B)
{
	int _=bel[pos];
	for(int i=L[_];i<=R[_];++i) s1[i]+=b[_].tag1,s2[i]+=b[_].tag2;
	for(int i=pos;i<=R[_];++i) s1[i]+=A,s2[i]+=B;
	for(int i=L[_];i<=R[_];++i) b[_].val[i-L[_]]={s1[i],s2[i],i};
	b[_].tag1=b[_].tag2=0;
	b[_].rebuild();
	for(int i=bel[pos]+1;i<=max_block;++i) b[i].tag1+=A,b[i].tag2+=B;
}
int Query(ll A,ll B)
{
	std::pair<ll,int> ans={-INF,0};
	for(int i=1;i<=max_block;++i) ans=max(ans,b[i].Query(A,B));
	return -ans.second;
}
int main()
{
	freopen("joker.in","r",stdin);
	freopen("joker.out","w",stdout);
	
	int m;read(n,m);
	for(int i=1;i<=n;++i) read(a[i]),s1[i]=s1[i-1]+(a[i]>0?a[i]:0),s2[i]=s2[i-1]+(a[i]<0?a[i]:0);
	build();
	ll a=s1[n],b=s2[n];
	printf("%d\n",Query(-b,a));
	int x,y;
	while(m--)
	{
		read(x,y);
		ll A=0,B=0;(::a[x]>0?A:B)-=::a[x];::a[x]=y;(::a[x]>0?A:B)+=::a[x];
		a+=A,b+=B,Update(x,A,B);
		printf("%d\n",Query(-b,a));
	}
	return 0;
}

