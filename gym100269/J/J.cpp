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

const int N=200005;
const int mod=1000000000;
template<typename _Tp1,typename _Tp2>inline void add(_Tp1 &a,_Tp2 b){(a+=b)>=mod&&(a-=mod);}
template<typename _Tp1,typename _Tp2>inline void sub(_Tp1 &a,_Tp2 b){(a-=b)<0&&(a+=mod);}
ll ksm(ll a,ll b=mod-2){ll res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod,b>>=1;}return res;}
typedef std::vector<int> poly;
void print(const poly &o)
{
	for(auto it:o) fprintf(stderr,"%d ",it);
	fprintf(stderr,"\n");
}
poly operator -(const poly &a)
{
	poly c(a);
	for(auto &&it:c) it=it?mod-it:0;
	return c;
}
poly operator + (const poly &a,const poly &b)
{
	poly c(max(SZ(a),SZ(b)));
	for(uint i=0;i<a.size();++i) add(c[i],a[i]);
	for(uint i=0;i<b.size();++i) add(c[i],b[i]);
	return c;
}
inline poly operator += (poly &a,const poly &b){return a=a+b;}
poly operator * (const poly &a,const poly &b)
{
	poly c(SZ(a)+SZ(b)-1);
	for(uint i=0;i<a.size();++i) for(uint j=0;j<b.size();++j) add(c[i+j],1ll*a[i]*b[j]%mod);
	return c;
}
inline poly operator *= (poly &a,const poly &b){return a=a*b;}
int val[15],X[N];
int calc(const poly &a)
{
	int ans=0;
	for(int i=0;i<SZ(a);++i) add(ans,1ll*val[i]*a[i]%mod);
	return ans;
}
char s[N];
int opt[N],st2[N];
poly a[N],st1[N];
int main()
{
	freopen("j.in","r",stdin);
	freopen("j.out","w",stdout);
	
	int n;read(n);
	for(int i=1;i<=n;++i) read(X[i]);
	for(int i=0;i<=10;++i)
	{
		int sum=0;
		for(int j=1;j<=n;++j) add(sum,ksm(X[j],i));
		val[i]=sum;
	}
	int len=read_str(s+1),m=0;
	for(int i=1;i<=len;++i)
	{
		++m;
		if(s[i]=='X') opt[m]=0,a[m]={0,1};
		else if(s[i]=='N') opt[m]=0,a[m]={n};
		else if(isdigit(s[i]))
		{
			int j=i,x=s[j]-48;
			while(j<len&&isdigit(s[j+1])) x=x*10+(s[++j]-48);
			opt[m]=0,a[m]={x};
			i=j;
		}
		else if(s[i]=='-')
		{
			if(m==1||(opt[m-1]>=1&&opt[m-1]<=6))
			{
				opt[m]=0;
				++m;
			}
			opt[m]=5;
		}
		else if(s[i]=='*')
		{
			if(i<len&&s[i+1]==':') opt[m]=1,++i;
			else opt[m]=3;
		}
		else if(s[i]=='+')
		{
			if(i<len&&s[i+1]=='/') opt[m]=2,++i;
			else opt[m]=4;
		}
		else if(s[i]=='(') opt[m]=6;
		else if(s[i]==')') opt[m]=7;
		else assert(0);
	}
	int top=0;
	for(int i=m;i>=1;--i)
	{
		if(opt[i]==0)
		{
			if(st2[top]>=3&&st2[top]<=5)
			{
				if(st2[top]==3)	st1[top]=a[i]*st1[top];
				else if(st2[top]==4) st1[top]=a[i]+st1[top];
				else st1[top]=a[i]+-st1[top];
				st2[top]=0;
			}
			else st1[++top]=a[i];
		}
		else if(opt[i]==1) st1[top]*=st1[top];
		else if(opt[i]==2) st1[top]={calc(st1[top])};
		else if(opt[i]>=3&&opt[i]<=5) st2[top]=opt[i];
		else if(opt[i]==6)
		{
			poly x=st1[top--];assert(st2[top]==7);
			st2[top]=0,--top;
			if(st2[top]>=3&&st2[top]<=5)
			{
				if(st2[top]==3)	st1[top]=x*st1[top];
				else if(st2[top]==4) st1[top]=x+st1[top];
				else st1[top]=x+-st1[top];
				st2[top]=0;
			}
			else st1[++top]=x;
		}
		else if(opt[i]==7) st2[++top]=7;
	}
	assert(top==1);
	printf("%d\n",st1[top][0]);
	return 0;
}

