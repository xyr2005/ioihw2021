// Author -- xyr2005

#include<bits/stdc++.h>
#include "sort.h"

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

const int N=10005;
int A,B;
int cnt[N],bel[N];
int ans[5005][5005];
inline bool Query(int x,int y)
{
	if(y>=A)
	{
		if(~ans[x][y-A]) return ans[x][y-A];
		return (ans[x][y-A]=(query(x+1,y-A+1)=='>'));
	}
	else
	{
		std::swap(x,y);
		if(~ans[x][y-A]) return !ans[x][y-A];
		return !(ans[x][y-A]=(query(x+1,y-A+1)=='>'));
	}
}
void divide(std::vector<int> v,std::vector<int> c,std::vector<int> d,int opt)
{
	if(v.empty()) return;
	if(SZ(c)==1||SZ(d)==1)
	{
		int val=SZ(c)==1?c[0]:d[0];
		for(auto it:v) bel[it]=Query(it,val);
		return;
	}
	opt=(opt+1)&3;
	while((opt==0&&v.empty())||(opt==1&&c.empty())||(opt==2&&v.empty())||(opt==3&&d.empty())) opt=(opt+1)&3;
	if(SZ(c)==2) opt=1;
	if(SZ(d)==2) opt=3;
	if(opt==0||opt==2)
	{
		int x=rnd()%SZ(v);
		std::vector<int> v1,v2;
		bool f1=true,f2=true;
		for(int i=0;i<min(SZ(c),SZ(d));++i)
		{
			if(!Query(v[x],c[i]))
			{
				f1=false;
				break;
			}
			if(Query(v[x],d[i]))
			{
				f2=false;
				break;
			}
		}
		if(!f1){for(int i=0;i<SZ(c);++i) if(!Query(v[x],c[i])) v1.pb(c[i]),f1=false;}
		else if(!f2){for(int i=0;i<SZ(d);++i) if(Query(v[x],d[i])) v2.pb(d[i]),f2=false;}
		else
		{
			if(SZ(d)>SZ(c)){for(int i=0;i<SZ(d);++i) if(Query(v[x],d[i])) v2.pb(d[i]),f2=false;}
			else if(SZ(c)>SZ(d)) for(int i=0;i<SZ(c);++i) if(!Query(v[x],c[i])) v1.pb(c[i]),f1=false;
		}
		if(f1) v1=c;
		if(f2) v2=d;
		if(!f1) bel[v[x]]=0;
		else bel[v[x]]=1;
		v.erase(v.begin()+x);
		return divide(v,v1,v2,opt);
	}
	else if(opt==1)
	{
		int x=rnd()%SZ(c);
		std::vector<int> o;
		for(auto it:v) if(Query(it,c[x])) o.pb(it);else bel[it]=0;
		if(SZ(c)>=2) c.erase(c.begin()+x);
		return divide(o,c,d,opt);
	}
	else
	{
		int x=rnd()%SZ(d);
		std::vector<int> o;
		for(auto it:v) if(!Query(it,d[x])) o.pb(it);else bel[it]=1;
		if(SZ(d)>=2) d.erase(d.begin()+x);
		return divide(o,c,d,opt);
	}
}
void solve(std::vector<int> a,std::vector<int> b)
{
	if(SZ(a)>SZ(b)) std::swap(a,b);
	if(a.empty()) return;
	int x=rnd()%SZ(a);
	std::vector<int> c,d;
	for(int i=0;i<SZ(b);++i)
	{
		if(Query(a[x],b[i])) c.pb(b[i]),++cnt[a[x]];
		else d.pb(b[i]);
	}
	a.erase(a.begin()+x);
	for(auto it:a) bel[it]=-1;
	divide(a,c,d,rnd()&3);
	std::vector<int> v1,v2;
	for(auto it:a) if(bel[it]==0) v1.pb(it);else v2.pb(it);
	for(auto it:d) cnt[it]+=SZ(v1)+1;
	for(auto it:v2) cnt[it]+=SZ(c);
	solve(v1,c),solve(v2,d);
}
std::vector<int> MAIN(int n)
{
//	int n;read(n);
	memset(ans,255,sizeof(ans));
	A=n>>1,B=n-A;
	std::vector<int> v1(A),v2(B);
	std::iota(v1.begin(),v1.end(),0);
	std::iota(v2.begin(),v2.end(),A);
	solve(v1,v2);
	std::vector<int> ans;
	for(int i=0;i<A;++i) ans.pb(cnt[i]<<1);
	for(int i=A;i<n;++i) ans.pb((cnt[i]<<1)+1);
	return ans;
	printf("! ");
	for(int i=0;i<A;++i) printf("%d ",cnt[i]<<1);
	for(int i=A;i<n;++i) printf("%d ",(cnt[i]<<1)+1);
	printf("\n");fflush(stdout);
//	return 0;
}

