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

std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
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

const int N=1000005;
struct edge{
	int v,nxt;
}c[N*6];
int front[N],edge_cnt=-1;
inline void addedge(int u,int v)
{
	c[++edge_cnt]=(edge){v,front[u]};
	front[u]=edge_cnt;
}
namespace e3 // copy from https://yhx-12243.github.io/OI-transit/memos/29.html
{
#define EB emplace_back
#define ad(x) (((x - 1) ^ 1) + 1)
using std::cin;
using std::cout;

typedef unsigned long long u64;
typedef std::pair <u64, int> pui;
typedef std::vector <int> vector;
const int N = 1000054, M = N * 6;
struct edge {
	int u, v;
	edge (int u0 = 0, int v0 = 0) : u(u0), v(v0) {}
} e[M];

int V, E, C, Es = 0;
int first[N], next[M], col[M];
int cnt = 0, p[N], id[N], low[N];
bool bridge[M], treeQ[M];
pui ew[M];
u64 weight[N];

inline void down(int &x, const int y) {x > y ? x = y : 0;}

inline void addedge(int u, int v) {
	e[++Es] = edge(u, v), next[Es] = first[u], first[u] = Es;
	e[++Es] = edge(v, u), next[Es] = first[v], first[v] = Es;
}

void dfs(int x) {
	int i, y;
	id[x] = low[x] = ++cnt;
	for (i = first[x]; i; i = next[i])
		if (!id[y = e[i].v]) {
			p[y] = i, treeQ[i] = treeQ[ad(i)] = true, dfs(y), down(low[x], low[y]);
			if (id[x] < low[y]) bridge[ad(i)] = bridge[i] = true;
		} else if ((p[x] - 1) ^ (i - 1) ^ 1)
			down(low[x], id[y]);
}

void dfs2(int x) {
	int i, y;
	for (i = first[x]; i; i = next[i])
		if (p[y = e[i].v] == i) dfs2(y), weight[x] ^= weight[y], ew[ad(i)].first = ew[i].first = weight[y];
}

namespace e3cc {
	typedef std::list <int> list;

	int n_e3cc = 0, p[N], deg[N], count[M];
	int na = 0, absQ[M];
	int nd = 0, deg2Q[N];
	list li[N];
	vector e3cc[N];

	int ancestor(int x) {return p[x] == x ? x : (p[x] = ancestor(p[x]));}

	void main() {
		int i, j, c, u, v, x, z[3], nz;
		for (i = 1; i <= Es; i += 2) if (!bridge[i]) ++count[col[i]];
		for (i = 1; i <= Es; i += 2) if (!bridge[i]) {
			++deg[e[i].u], ++deg[e[i].v];
			if (count[col[i]] == 1) absQ[na++] = i;
		}
		for (i = 1; i <= V; ++i) {
			li[i].EB(i), p[i] = i, assert(deg[i] != 1);
			if (deg[i] == 2) deg2Q[nd++] = i;
		}
		for (; ; )
			if (na) {
				i = absQ[--na], u = ancestor(e[i].u), v = ancestor(e[i].v);
				if (u == v) deg[u] -= 2;
				else p[v] = u, deg[u] += deg[v] - 2, li[u].splice(li[u].end(), li[v]);
				if (deg[u] == 2) deg2Q[nd++] = u;
			} else if (nd) {
				x = deg2Q[--nd];
				if (deg[x] != 2) continue;
				x = ancestor(x), nz = 0;
				for (int r : li[x])
					for (i = first[r]; i; i = next[i])
						if (!bridge[i] && ancestor(e[i].v) != x)
							z[nz++] = i;
				assert(nz == 2), u = e[i = *z].v, v = e[j = z[1]].v;
				assert(col[i] == col[j]), c = col[i];
				if (p[u] == p[v]) continue;
				e[i].u = e[ad(i)].v = v, next[i] = first[v], first[v] = i, p[x] = p[v];
				if (--count[c] == 1) absQ[na++] = i;
			} else break;
		for (i = 1; i <= V; ++i) if (!li[i].empty()) e3cc[n_e3cc++].assign(li[i].begin(), li[i].end());
	}
}

ll MAIN(int n,int m,std::vector<int> E1,std::vector<int> E2) {
	int i, u, v; u64 w; vector *ans = e3cc::e3cc;
	std::mt19937_64 gen((std::random_device())());
	V=n,E=m;
	for (i = 0; i < E; ++i) if ((u=E1[i])!=(v=E2[i])) addedge(u, v);
	for (i = 1; i <= V; ++i) if (!id[i]) dfs(i);
	for (i = 1; i <= Es; i += 2) if (!treeQ[i])
		ew[ad(i)].first = ew[i].first = w = gen(), weight[e[i].u] ^= w, weight[e[i].v] ^= w;
	for (i = 1; i <= V; ++i) if (!p[i]) dfs2(i);
	for (i = 1; i <= Es; ++i) ew[i].second = i;
	std::sort(ew + 1, ew + (Es + 1));
	for (i = 1; i <= Es; ++i) col[ew[i].second] = (i != 1 && ew[i].first == ew[i - 1].first ? C : ++C);
	e3cc::main();
	ll res=0;
	for (i = 0; i < e3cc::n_e3cc; ++i) res+=1LL*SZ(ans[i])*(SZ(ans[i])-1)/2;
	return res;
}

}
int dfn[N],low[N],id,st[N],top,tot,Fa[N];
ll cnt1,cnt2;
void dfs(int x,int fa)
{
	++tot;
	dfn[x]=low[x]=++id,st[++top]=x;
	for(int i=front[x];~i;i=c[i].nxt)
	{
		if((i^fa)==1) continue;
		int v=c[i].v;
		if(!dfn[v]) dfs(v,i),chmin(low[x],low[v]);
		else if(dfn[v]<dfn[x]) chmin(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		int cnt=1;
		while(st[top]!=x) --top,++cnt;
		--top;
		cnt2+=1LL*(cnt-1)*cnt/2;
	}
}
int main()
{
	memset(front,255,sizeof(front));
	int n,m;read(n,m);
	int x,y;
	std::vector<int> E1,E2;
	for(int i=1;i<=m;++i) read(x,y),addedge(x,y),addedge(y,x),E1.pb(x),E2.pb(y);
	for(int i=1;i<=n;++i) if(!dfn[i]) tot=0,dfs(i,-233),cnt1+=1LL*(tot-1)*tot/2;
	ll cnt3=e3::MAIN(n,m,E1,E2);
	printf("%lld\n",cnt1+cnt2+cnt3);
	return 0;
}

