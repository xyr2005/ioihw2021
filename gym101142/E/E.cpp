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
const int mod1=1000000007,mod2=1000000009;
const int base1=2333,base2=23333;
ll ksm1(ll a,ll b=mod1-2)
{
	if(b<0) b=-b,a=ksm1(a);
	ll res=1;while(b){if(b&1)res=res*a%mod1;a=a*a%mod1,b>>=1;}return res;
}
ll ksm2(ll a,ll b=mod2-2)
{
	if(b<0) b=-b,a=ksm2(a);
	ll res=1;while(b){if(b&1)res=res*a%mod2;a=a*a%mod2,b>>=1;}return res;
}
struct hash{
	ll a,b;
	inline bool operator == (const hash &o)const
	{
		return a==o.a&&b==o.b;
	}
	inline hash operator += (const hash &o)
	{
		(a+=o.a)>=mod1&&(a-=mod1);
		(b+=o.b)>=mod2&&(b-=mod2);
		return *this;
	}
	inline hash operator -= (const hash &o)
	{
		(a-=o.a)<0&&(a+=mod1);
		(b-=o.b)<0&&(b+=mod2);
		return *this;
	}
	inline hash operator * (const hash &o)const
	{
		return (hash){1ll*a*o.a%mod1,1ll*b*o.b%mod2};
	}
};
char s[N];
struct node{
	int x,y;
	inline bool operator < (const node &o)const
	{
		return x==o.x?y<o.y:x<o.x;
	}
};
std::set<node> S;
std::map<node,int> mp;
hash cur;
inline hash gethash(const node &o)
{
	return (hash){ksm1(base1,o.x),ksm2(base2,o.y)};
}
void upd(node x,int opt)
{
	if(mp[x]) S.erase(x),cur-=gethash(x);
	mp[x]+=opt;
	if(mp[x]) S.insert(x),cur+=gethash(x);
}
node _[N];
int main()
{
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	
	int l;read(l);
	std::string ___;
	std::getline(std::cin,___);
	for(int i=0;i<l;++i) s[i+1]=___[i];
	int n,m;read(n,m);
	char ch;
	node minn={inf,inf};
	hash tar={0,0};
	int cnt=0;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)
		{
			do{ch=getchar();}while(ch!='.'&&ch!='X');
			if(ch=='X') minn=min(minn,(node){i,j}),tar+=gethash({i,j}),++cnt;
		}
	}
	int pos=0;
	int x=0,y=0;
	upd({x,y},1);
	for(int i=1;i<=l;++i)
	{
		if(s[i]!='l'&&s[i]!='r'&&s[i]!='u'&&s[i]!='d') continue;
		while(pos<l&&SZ(S)<cnt)
		{
			++pos;
			_[pos]={x,y};
			if(s[pos]=='l') --y;
			else if(s[pos]=='r') ++y;
			else if(s[pos]=='u') --x;
			else if(s[pos]=='d') ++x;
			else continue;
			upd({x,y},1);
		}
		if(cur*gethash(minn)==tar*gethash(*S.begin()))
		{
			printf("YES\n%d %d\n",i,pos);
			return 0;
		}
		upd(_[i],-1);
	}
	puts("NO");
	return 0;
}

