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

const int N=2000005;
int n,k;
int ch[N][26],sum[N],fail[N],node_cnt;
void init()
{
	int x;
	for(int i=1;i<=n;++i)
	{
		char ch=getchar();while(!isalpha(ch)) ch=getchar();
		read(x),::ch[x][ch-65]=i,sum[i]=1;
	}
}
int insert(char *s,int len)
{
	int cur=0;
	for(int i=0;i<len;++i)
	{
		int tmp=s[i]-65;
		if(!ch[cur][tmp]) ch[cur][tmp]=++node_cnt;
		cur=ch[cur][tmp];
	}
	return cur;
}
int _q[N],_l,_r;
void build()
{
	_l=1,_r=0;
	for(int i=0;i<26;++i) if(ch[0][i]) _q[++_r]=ch[0][i];
	while(_l!=_r+1)
	{
		int x=_q[_l++];
		for(int i=0;i<26;++i)
		{
			if(ch[x][i]) fail[ch[x][i]]=ch[fail[x]][i],_q[++_r]=ch[x][i];
			else ch[x][i]=ch[fail[x]][i];
		}
	}
	for(int i=node_cnt;i>=1;--i) sum[fail[_q[i]]]+=sum[_q[i]];
}
int id[N];
char s[N];
int main()
{
	read(n,k);
	init();
	node_cnt=n;
	for(int i=1;i<=k;++i)
	{
		int l=read_str(s);
		std::reverse(s,s+l);
		id[i]=insert(s,l);
	}
	build();
	for(int i=1;i<=k;++i) printf("%d\n",sum[id[i]]);
	return 0;
}

