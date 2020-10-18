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

const int N=2005;
int n,m,a[N][N],to[N];
inline int modn(int x){return x>=n?x-n:x;}
inline int modm(int x){return x>=m?x-m:x;}
int tim[N];
inline int getnxt(int i,int j)
{
	int x=(j+1)==m?0:j+1,A=modn(i-1+n),C=modn(i+1);
	return (a[A][x]>=a[i][x])?(a[A][x]>=a[C][x]?A:C):(a[i][x]>=a[C][x]?i:C);
}
inline bool check(int x,int y,int l,int r)
{
	int tmp=(getnxt(x,y));
	if(l<=r) return tmp>=l&&tmp<=r;
	return !(tmp>r&&tmp<l);
}
void Update(int X,int Y)
{
	int cx=X,cy=Y;
	while(cy)
	{
		cx=getnxt(cx,cy);
		cy=modm(cy+1);
	}
	int l=X,r=X;
	bool flag=false;
	for(int i=(Y==0?m:Y)-1;i>=0;--i)
	{
		int L=l,R=r;
		
		int tmp=modn(l-1+n),t1=-1,t2=-1;
		if(check(tmp,i,L,R)) t1=tmp;
		tmp=modn(r+1);
		if(check(tmp,i,L,R)) t2=tmp;
		if(l>r)
		{
			while(l<n&&!check(l,i,L,R)) ++l;
			if(l==n) l=0;
			if(l>r)
			{
				while(r>=0&&!check(r,i,L,R)) --r;
				if(r==-1) r=n-1;
			}
		}
		if(l<=r)
		{
			while(l<=r&&!check(l,i,L,R)) ++l;
			while(l<=r&&!check(r,i,L,R)) --r;
			if(l>r)
			{
				if(~t1&&~t2) l=max(t1,t2),r=min(t1,t2);
				else if(~t1) l=t1,r=t1;
				else if(~t2) l=t2,r=t2;
				else
				{
					flag=true;
					break;
				}
			}
		}
		tmp=modn(l-1+n);
		if(tmp!=r&&check(tmp,i,L,R)) l=tmp;
		tmp=modn(r+1);
		if(tmp!=l&&check(tmp,i,L,R)) r=tmp;
	}
	if(!flag)
	{
		int cur=l;
		while(true)
		{
			to[cur]=cx;
			if(cur==r) break;
			cur=modn(cur+1);
		}
	}
}
int main()
{
	read(n,m);
	for(int i=0;i<n;++i) for(int j=0;j<m;++j) read(a[i][j]);
	for(int j=0;j<n;++j)
	{
		int x=j;
		for(int i=0;i<m;++i) x=getnxt(x,i);
		to[j]=x;
	}
	int q;read(q);
	int x=0,y=0;
	int k,X,Y,z;
	while(q--)
	{
		char ch=getchar();
		while(ch!='c'&&ch!='m') ch=getchar();
		if(ch=='c')
		{
			read(X,Y,z);
			--X,--Y;
			if(z>a[X][Y])
			{
				a[X][Y]=z;
				Update(X,Y);
			}
			else
			{
				a[X][Y]=z;
				Update(modn(X-1+n),Y);
				Update(modn(X-2+n),Y);
				Update(modn(X+1),Y);
				Update(modn(X+2),Y);
			}
		}
		else
		{
			read(k);
			while(k&&y)
			{
				--k;
				x=getnxt(x,y);
				y=modm(y+1);
			}
			if(!k)
			{
				printf("%d %d\n",x+1,y+1);
				continue;
			}
			memset(tim,255,sizeof(tim));
			while(true)
			{
				if(~tim[x]) k%=(tim[x]-k);
				else tim[x]=k;
				if(k<=m)
				{
					while(k--)
					{
						x=getnxt(x,y);
						y=modm(y+1);
					}
					printf("%d %d\n",x+1,y+1);
					break;
				}
				k-=m,x=to[x];
			}
		}
	}
	return 0;
}

