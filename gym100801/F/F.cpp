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

const int N=25;
struct edge{
	int v,nxt;
}c[N<<1];
int front[N],edge_cnt;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
char val[N],rng[N];
char t[1005];
int last[1005];
int y[N],cnt;
int mp[127];
void dfs(int x)
{
	if(rng[x]=='$')
	{
		++cnt;
		return;
	}
	int limit=mp[rng[x]];
	for(int cur=0;cur<limit;++cur)
	{
		mp[val[x]]=cur;
		for(int i=front[x];i;i=c[i].nxt) dfs(c[i].v);
	}
}
typedef std::vector<int> poly;
poly operator * (const poly &a,const poly &b)
{
	poly c(SZ(a)+SZ(b)-1);
	for(uint i=0;i<a.size();++i) for(uint j=0;j<b.size();++j) c[i+j]+=a[i]*b[j];
	return c;
}
struct frac{
	ll a,b;
	inline frac operator * (const frac &o)const
	{
		ll A=a*o.a,B=b*o.b,g=gcd(abs(A),abs(B));
		return (frac){A/g,B/g};
	}
	inline frac operator + (const frac &o)const
	{
		ll c=b/gcd(abs(b),abs(o.b))*o.b;
		ll A=a*(c/b)+o.a*(c/o.b);
		ll g=gcd(abs(c),abs(A));
		return (frac){A/g,c/g};
	}
};
frac ans[8];
int main()
{
	freopen("fygon.in","r",stdin);
	freopen("fygon.out","w",stdout);
	
	std::string s;
	int cur=0;
	val[0]='#',rng[0]='1';
	while(std::getline(std::cin,s))
	{
		int qwq=0;
		while(!s.empty()&&*s.begin()==' ') s.erase(s.begin()),++qwq;
		if(s.empty()) break;
		++cur;
		if(qwq>=4) addedge(last[qwq-4],cur);
		else addedge(0,cur);
		if(s[0]=='l') rng[cur]='$';
		else
		{
			for(int i=0;i<SZ(s);++i) t[i]=s[i];
			sscanf(t,"for %c in range(%c):",&val[cur],&rng[cur]);
		}
		last[qwq]=cur;
	}
	for(int x=1;x<=7;++x)
	{
		memset(mp,0,sizeof(mp));
		for(int i=0;i<10;++i) mp[48+i]=i;
		mp['n']=x;
		cnt=0,dfs(0);
		y[x]=cnt;
	}
	for(int i=0;i<8;++i) ans[i]={0,1};
	for(int i=1;i<=7;++i)
	{
		poly tmp={1};
		frac coef={y[i],1};
		for(int j=1;j<=7;++j) if(i!=j) tmp=tmp*(poly){-j,1},coef=coef*(frac){1,i-j};
		for(int j=0;j<SZ(tmp);++j) ans[j]=ans[j]+coef*(frac){tmp[j],1};
	}
	printf("0");
	for(int i=7;i>=0;--i)
	{
		if(!ans[i].a) continue;
		ll A=ans[i].a,B=ans[i].b;
		if((A<0)!=(B<0)) printf(" - ");
		else printf(" + ");
		printf("%lld/%lld",abs(A),abs(B));
		for(int j=1;j<=i;++j) printf(" * n");
	}
	printf("\n");
	return 0;
}

