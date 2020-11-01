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

const int D=1505;
const int N=D<<1;
int s1[N][N],s2[N][N];
int main()
{
	int _;read(_);
	char ch;
	int x,y,d;
	while(_--)
	{
		do{ch=getchar();}while(ch!='A'&&ch!='B');
		read(x,y,d),x+=D,y+=D;
		if(ch=='A') x-=d/2,y-=d/2,++s1[x][y],--s1[x+d][y],--s1[x][y+d],++s1[x+d][y+d];
		else x-=d/2,++s2[x][y],--s2[x+d/2][y-d/2],--s2[x+d/2][y+d/2],++s2[x+d][y];
	}
	for(int i=0;i<N;++i) for(int j=1;j<N;++j) s1[i][j]+=s1[i][j-1];
	for(int i=1;i<N;++i) for(int j=0;j<N;++j) s1[i][j]+=s1[i-1][j];
	for(int i=1;i<N;++i) for(int j=1;j<N;++j) s2[i][j]+=s2[i-1][j-1];
	for(int i=1;i<N;++i) for(int j=N-2;j>=0;--j) s2[i][j]+=s2[i-1][j+1];
	int ans=0;
	for(int i=1;i<N;++i)
	{
		for(int j=0;j+1<N;++j)
		{
			if(s1[i][j]) ans+=4;
			else
			{
				if(s2[i][j]||s2[i-1][j]) ++ans;
				if(s2[i][j]||s2[i][j+1]) ++ans;
				if(s2[i][j+1]||s2[i-1][j+1]) ++ans;
				if(s2[i-1][j]||s2[i-1][j+1]) ++ans;
			}
		}
	}
	printf("%d.%c%c\n",ans>>2,"0257"[ans&3],"05"[ans&1]);
	return 0;
}

