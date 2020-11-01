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

const int N=4000005;
int n,w,h;
inline int getid(int x,int y)
{
	if(x==0) return y+1;
	if(y==h) return h+1+x+1;
	if(x==w) return w+h+2+h-y+1;
	return w+h+h+3+w-x+1;
}
struct node{
	int x,y,val,id;
	inline bool operator < (const node &o)const
	{
		return val<o.val;
	}
}t[N];
bool vis[N];
inline std::pair<double,double> pre(int x,int y)
{
	if(x==0) return {x,y-0.5};
	if(y==h) return {x-0.5,y};
	if(x==w) return {x,y+0.5};
	return {x+0.5,y};
}
inline std::pair<double,double> suf(int x,int y)
{
	if(x==0) return {x,y+0.5};
	if(y==h) return {x+0.5,y};
	if(x==w) return {x,y-0.5};
	return {x-0.5,y};
}
inline int getside(int x,int y)
{
	return x==0?0:y==h?1:x==w?2:3;
}
int main()
{
	read(n,w,h);
	int x,y,pos=0;
	for(int i=1;i<=n;++i) read(x,y),t[++pos]={x,y,getid(x,y),i},read(x,y),t[++pos]={x,y,getid(x,y),i};
	std::sort(t+1,t+pos+1);
	for(int i=1;i<=pos;++i) t[pos+i]=t[i];
	pos<<=1;
	int cur=0,cnt=0;
	for(int i=1;i+n-1<=pos;++i)
	{
		while(cur+1<=i+n-1)
		{
			++cur;
			cnt-=vis[t[cur].id],vis[t[cur].id]^=1,cnt+=vis[t[cur].id];
		}
		if(cnt==n)
		{
			if(getside(t[i].x,t[i].y)==getside(t[cur].x,t[cur].y))
			{
				int opt=getside(t[i].x,t[i].y);
				if(opt==0) printf("1\n0.5 0 0.5 %d\n",h);
				else if(opt==1) printf("1\n0 %.1lf %d %.1lf\n",(double)h-0.5,w,(double)h-0.5);
				else if(opt==2) printf("1\n%.1lf 0 %.1lf %d\n",(double)w-0.5,(double)w-0.5,h);
				else printf("1\n0 0.5 %d 0.5\n",w);
				return 0;
			}
			std::pair<double,double> a=pre(t[i].x,t[i].y),b=suf(t[cur].x,t[cur].y);
			printf("1\n%.1lf %.1lf %.1lf %.1lf\n",a.first,a.second,b.first,b.second);
			return 0;
		}
		cnt-=vis[t[i].id],vis[t[i].id]^=1,cnt+=vis[t[i].id];
	}
	printf("2\n0 0.5 %d %.1lf\n%.1lf 0 0 %.1lf\n",w,(double)h-0.5,(double)w-0.5,(double)h-0.5);
	return 0;
}

