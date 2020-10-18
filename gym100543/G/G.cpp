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
char s[N];
int ch[N][4],fail[N],half[N],dp[N],len[N],last;
int node_cnt;
int getfail(int x,int n)
{
	while(s[n]!=s[n-len[x]-1]) x=fail[x];
	return x;
}
void insert(int n)
{
	int nd=getfail(last,n),c=s[n]-65;
	if(!ch[nd][c])
	{
		int cur=++node_cnt;
		memset(ch[cur],0,sizeof(ch[cur]));
		len[cur]=len[nd]+2;
		fail[cur]=ch[getfail(fail[nd],n)][c];
		if(len[cur]>2)
		{
			int limit=len[cur]>>1,tmp=half[nd];
			while(s[n-len[tmp]-1]!=s[n]||len[tmp]+2>limit) tmp=fail[tmp];
			half[cur]=ch[tmp][c];
		}
		else half[cur]=fail[cur];
		if(len[cur]&1) dp[cur]=dp[fail[cur]]+len[cur]-len[fail[cur]];
		else dp[cur]=min(dp[nd]+1,dp[half[cur]]+len[cur]/2-len[half[cur]]+1);
		ch[nd][c]=cur;
	}
	last=ch[nd][c];
}
void MAIN()
{
	node_cnt=last=1;
	fail[0]=fail[1]=1;
	len[1]=-1,len[0]=0;
	half[0]=half[1]=1,dp[0]=1,dp[1]=1;
	memset(ch[0],0,sizeof(ch[0]));
	memset(ch[1],0,sizeof(ch[1]));
	int n=read_str(s+1);
	for(int i=1;i<=n;++i)
	{
		if(s[i]=='G') s[i]='B';
		else if(s[i]=='T') s[i]='D';
		insert(i);
	}
	int ans=n;
	for(int i=1;i<=node_cnt;++i) if(!(len[i]&1)) chmin(ans,dp[i]+n-len[i]);
	printf("%d\n",ans);
}
int main()
{
	int _;read(_);
	while(_--) MAIN();
	return 0;
}
