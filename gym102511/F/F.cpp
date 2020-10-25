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

const int N=500005;
int X1[N],Y1[N],X2[N],Y2[N],_[N];
double k[N];
struct Node{
	int x,id;
	inline bool operator < (const Node &o)const
	{
		return x<o.x;
	}
}q[N<<1];
struct node{
	int id;
	inline bool operator < (const node &o)const
	{
		int pos=max(_[id],_[o.id]);
		return Y1[id]+k[id]*(pos-X1[id])<Y1[o.id]+k[o.id]*(pos-X1[o.id]);
	}
};
std::set<node> __;
struct edge{
	int v,nxt;
}c[N<<3];
int front[N],edge_cnt;
int dg[N];
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	++dg[v],front[u]=edge_cnt;
}
int _q[N],_l,_r;
std::map<int,int> S;
std::set<int> S1,S2;
void upd0(int x,int y)
{
	int tmp=S[x];
	if(tmp>0) S1.erase(x);
	else if(tmp<0) S2.erase(x);
	S[x]+=y,tmp+=y;
	if(tmp>0) S1.insert(x);
	else if(tmp<0) S2.insert(x);
	if(!tmp) S.erase(x);
}
void upd1(int l,int r)
{
	S[r+1]+=0;
	for(auto it=S1.lower_bound(l+1);it!=S1.end()&&*it<=r;++it)
	{
		auto __=S.find(*it);
		upd0(S.upper_bound(*it)->first,__->second);
		S.erase(__);
	}
	S1.erase(S1.lower_bound(l+1),S1.upper_bound(r));
}
void upd2(int l,int r)
{
	S[l]+=0;
	for(auto it=S2.upper_bound(r);;)
	{
		if(it==S2.begin()||*(--it)<=l) break;
		auto __=S.find(*it);
		upd0((--S.lower_bound(*it))->first,__->second);
		S.erase(__);
	}
	S2.erase(S2.lower_bound(l+1),S2.upper_bound(r));
}
int main()
{
	int L,R;read(L,R),L<<=1,R<<=1;
	int n;read(n);
	int pos=0;
	for(int i=1;i<=n;++i)
	{
		read(X1[i],Y1[i],X2[i],Y2[i]);
		X1[i]<<=1,X2[i]<<=1;
		_[i]=min(X1[i],X2[i]),k[i]=(double)(Y2[i]-Y1[i])/(X2[i]-X1[i]);
		q[++pos]={min(X1[i],X2[i]),i},q[++pos]={max(X2[i],X1[i])+1,-i};
	}
	std::sort(q+1,q+pos+1);
	for(int i=1;i<=pos;++i)
	{
		if(q[i].id>0) __.insert({q[i].id});
		else
		{
			auto it=__.find({-q[i].id});
			int id=it->id;
			if(it!=__.begin()) addedge(id,(--it)->id),++it;
			if(++it!=__.end()) addedge(it->id,id);
			__.erase(--it);
		}
	}
	_l=1,_r=0;
	for(int i=1;i<=n;++i) if(!dg[i]) _q[++_r]=i;
	while(_l!=_r+1)
	{
		int x=_q[_l++];
		for(int i=front[x];i;i=c[i].nxt) if(!--dg[c[i].v]) _q[++_r]=c[i].v;
	}
	upd0(0,inf),upd0(L,-inf),upd0(R+1,inf);
	for(int _=1;_<=n;++_)
	{
		int i=_q[_];
		if(X1[i]<X2[i])
		{
			upd2(X1[i],X2[i]);
			upd0(X1[i]+1,1),upd0(X2[i]+1,-1);
		}
		else
		{
			upd1(X2[i],X1[i]);
			upd0(X2[i],1),upd0(X1[i],-1);
		}
	}
	S[L]+=0,S[R]+=0;
	int sum=0,ans=inf;
	for(auto it:S)
	{
		sum+=it.second;
		if(it.first>=L&&it.first<=R) chmin(ans,sum);
	}
	printf("%d\n",ans);
	return 0;
}

