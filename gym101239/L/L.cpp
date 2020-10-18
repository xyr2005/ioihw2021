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
ll fac[N];
struct node{
	double val;
	ll cnt;
	inline bool operator < (const node &o)const
	{
		return val>o.val;
	}
};
std::priority_queue<node> q;
double pw1[N],pw2[N],pw3[N],pw4[N];
inline ll C(int a,int b,int c,int d)
{
	return fac[a+b+c+d]/fac[a]/fac[b]/fac[c]/fac[d];
}
int main()
{
	fac[0]=1;for(int i=1;i<=20;++i) fac[i]=fac[i-1]*i;
	int n;read(n);
	double p1,p2,p3,p4;scanf("%lf %lf %lf %lf",&p1,&p2,&p3,&p4);
	pw1[0]=pw2[0]=pw3[0]=pw4[0]=1;
	for(int i=1;i<=n;++i)
	{
		pw1[i]=pw1[i-1]*p1;
		pw2[i]=pw2[i-1]*p2;
		pw3[i]=pw3[i-1]*p3;
		pw4[i]=pw4[i-1]*p4;
	}
	for(int a=0;a<=n;++a)
	{
		for(int b=0;a+b<=n;++b)
		{
			for(int c=0;a+b+c<=n;++c)
			{
				int d=n-a-b-c;
				q.push({pw1[a]*pw2[b]*pw3[c]*pw4[d],C(a,b,c,d)});
			}
		}
	}
	double ans=0;
	while(SZ(q)>1)
	{
		node x=q.top();
		q.pop();
		if(x.cnt>=2)
		{
			if(x.cnt&1) q.push({x.val,1});
			q.push({x.val+x.val,x.cnt>>1});
			ans+=(x.val+x.val)*(x.cnt>>1);
		}
		else
		{
			if(q.empty()) break;
			node y=q.top();
			q.pop();
			ll tmp=min(x.cnt,y.cnt);
			q.push({x.val+y.val,tmp});
			ans+=(x.val+y.val)*tmp;
			x.cnt-=tmp,y.cnt-=tmp;
			if(x.cnt) q.push(x);
			if(y.cnt) q.push(y);
		}
	}
	printf("%.8lf\n",ans);
	return 0;
}
