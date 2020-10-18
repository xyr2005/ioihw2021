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
struct node{
	int x,y,id;
	inline bool operator < (const node &o)const
	{
		return x==o.x?y>o.y:x>o.x;
	}
}a[N],b[N];
int _X[N],_Y[N];
struct Pair{
	int x,id;
	inline bool operator < (const Pair &o)const
	{
		return x==o.x?id<o.id:x<o.x;
	}
};
std::set<Pair> s;
int ans[N];
struct Node{
	int x,y1,y2,opt;
	inline bool operator < (const Node &o)const
	{
		return x<o.x;
	}
}q[N];
std::multiset<int> S;
int main()
{
	int n;read(n);
	for(int i=1;i<=n;++i)
	{
		read(a[i].x,a[i].y);
		a[i].id=i;
	}
	for(int i=1;i<=n;++i)
	{
		read(b[i].x,b[i].y);
		_X[i]=b[i].x,_Y[i]=b[i].y;
		b[i].id=i;
	}
	std::sort(a+1,a+n+1);
	std::sort(b+1,b+n+1);
	int pos=0;
	int p=0;
	for(int i=1;i<=n;++i)
	{
		while(pos<n&&b[pos+1].x>=a[i].x)
		{
			++pos;
			s.insert((Pair){b[pos].y,b[pos].id});
		}
		auto it=s.lower_bound((Pair){a[i].y,0});
		if(it==s.end()) return puts("syntax error"),0;
		q[++p]={a[i].x,a[i].y,_Y[it->id],1};
		q[++p]={_X[it->id]+1,a[i].y,_Y[it->id],-1};
		ans[a[i].id]=it->id;
		s.erase(it);
	}
	std::sort(q+1,q+p+1);
	for(int i=1;i<=p;++i)
	{
		int j=i;
		while(j<p&&q[j+1].x==q[i].x) ++j;
		for(int k=i;k<=j;++k)
		{
			if(q[k].opt==1) S.insert(q[k].y1),S.insert(q[k].y2);
			else S.erase(S.find(q[k].y1)),S.erase(S.find(q[k].y2));
		}
		for(int k=i;k<=j;++k)
		{
			if(q[k].opt==1)
			{
				int cnt=0;
				for(auto it=S.lower_bound(q[k].y1);it!=S.end()&&*it<=q[k].y2;++it) ++cnt;
				if(cnt>2) return puts("syntax error"),0;
			}
		}
		i=j;
	}
	std::reverse(q+1,q+p+1);
	for(int i=1;i<=p;++i) q[i].opt*=-1;
	S.clear();
	for(int i=1;i<=p;++i)
	{
		int j=i;
		while(j<p&&q[j+1].x==q[i].x) ++j;
		for(int k=i;k<=j;++k)
		{
			if(q[k].opt==1) S.insert(q[k].y1),S.insert(q[k].y2);
			else S.erase(S.find(q[k].y1)),S.erase(S.find(q[k].y2));
		}
		for(int k=i;k<=j;++k)
		{
			if(q[k].opt==1)
			{
				int cnt=0;
				for(auto it=S.lower_bound(q[k].y1);it!=S.end()&&*it<=q[k].y2;++it) ++cnt;
				if(cnt>2) return puts("syntax error"),0;
			}
		}
		i=j;
	}
	for(int i=1;i<=n;++i) printf("%d\n",ans[i]);
	return 0;
}
