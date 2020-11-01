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

const int N=55;
bool rev[N];
int st[N];
std::vector<int> v[8];
struct node{
	int x,a,y,b;
};
std::vector<node> ans;
std::pair<int,int> t[5];
int main()
{
	int n;read(n);
	int x;
	for(int i=0;i<3;++i) for(int j=1;j<=n;++j) read(x),st[j]|=x<<i;
	for(int i=1;i<=n;++i)
	{
		v[st[i]].pb(i);
		if(st[i]!=0&&st[i]!=1&&st[i]!=2&&st[i]!=4) rev[i]=true;
	}
	int pos=0;
	for(int j=0;j<8;++j)
	{
		if(v[j].empty()) continue;
		if(SZ(v[j])>1)
		{
			for(int i=1;i<SZ(v[j]);++i)
			{
				ans.pb({v[j][0],0,v[j][i],0});
				ans.pb({v[j][0],1,v[j][i],1});
				ans.pb({v[j][i],0,v[j][0],0});
				ans.pb({v[j][i],1,v[j][0],1});
			}
		}
		if(j==0||j==1||j==2||j==4)
		{
			for(auto it:v[7-j])
			{
				ans.pb({v[j][0],0,it,0});
				ans.pb({v[j][0],1,it,1});
				ans.pb({it,0,v[j][0],0});
				ans.pb({it,1,v[j][0],1});
			}
		}
		if(j==0||j==7) ans.pb({v[j][0],1,v[j][0],0});
		else
		{
			int st=j;
			if(j!=1&&j!=2&&j!=4) st^=7;
			if(t[0].first!=st&&t[1].first!=st&&t[2].first!=st) t[pos++]={st,v[j][0]};
		}
	}
	fprintf(stderr,"@ %d\n",pos);
	if(pos==3) return puts("-1"),0;
	if(pos==2)
	{
		int a=t[0].second,b=t[1].second;
		ans.pb({a,1,b,0}),ans.pb({b,1,a,0});
	}
	printf("%d\n",SZ(ans));
	for(auto it:ans)
	{
		if(rev[it.x]) it.a^=1;
		if(rev[it.y]) it.b^=1;
		if(!it.a) printf("!");
		printf("x%d -> ",it.x);
		if(!it.b) printf("!");
		printf("x%d\n",it.y);
	}
	return 0;
}

