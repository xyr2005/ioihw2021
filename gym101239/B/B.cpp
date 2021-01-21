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
const long double eps=1e-12;
struct vec{
	long double x,y;
	inline bool operator != (const vec &o)const{return x!=o.x||y!=o.y;}
	inline bool operator == (const vec &o)const{return x==o.x&&y==o.y;}
	inline bool operator < (const vec &o)const{return x==o.x?y<o.y:x<o.x;}
	inline vec operator + (const vec &o)const{return (vec){x+o.x,y+o.y};}
	inline vec operator - (const vec &o)const{return (vec){x-o.x,y-o.y};}
	inline vec operator += (const vec &o){x+=o.x,y+=o.y;return *this;}
	inline vec operator -= (const vec &o){x-=o.x,y-=o.y;return *this;}
	inline vec operator * (const long double &o)const{return (vec){x*o,y*o};}
	inline long double operator * (const vec &o)const{return x*o.x+y*o.y;}
	inline long double operator ^ (const vec &o)const{return x*o.y-y*o.x;}
	inline long double angle()const{return std::atan2(y,x);}
};
struct segment{
	vec a,b;
};
bool cross(const segment &a,const segment &b)
{
	long double A=(a.a-b.a)^(b.b-b.a);
	long double B=(a.b-b.a)^(b.b-b.a);
	return (A<=0)!=(B<0);
}
inline bool checksameslope(const vec &a,const vec &b)
{
	return abs(a^b)<=eps;
}
inline bool iscross(const segment &a,const segment &b)
{
	return !checksameslope(a.a-a.b,b.a-b.b)&&cross(a,b)&&cross(b,a);
}
inline vec getpoint(const segment &a,const segment &b)
{
	long double s1=(a.b-a.a)^(b.a-a.a),s2=(b.b-a.a)^(a.b-a.a);
	return b.a+(b.b-b.a)*(s1/(s1+s2));
}
typedef std::vector<vec> polygon;
void print(const polygon &a)
{
	fprintf(stderr,"Polygon\n");
	for(auto it:a) fprintf(stderr,"%.3Lf %.3Lf\n",it.x,it.y);
	fprintf(stderr,"...\n\n");
}
bool check(polygon a,const vec &o)
{
	a.pb(a[0]);
	for(int i=0;i+1<SZ(a);++i) if(((a[i]-o)^(a[i+1]-o))<-eps) return false;
	return true;
}
polygon intersect(polygon a,polygon b)
{
	polygon res;
	for(auto it:a) if(check(b,it)) res.pb(it);
	for(auto it:b) if(check(a,it)) res.pb(it);
	a.pb(a[0]),b.pb(b[0]);
	for(int i=0;i+1<SZ(a);++i) for(int j=0;j+1<SZ(b);++j) if(iscross({a[i],a[i+1]},{b[j],b[j+1]})) res.pb(getpoint({a[i],a[i+1]},{b[j],b[j+1]}));
	if(res.empty()) return res;
	vec minn={1e18,1e18};
	for(auto it:res) minn=min(minn,it);
	res.erase(std::find(res.begin(),res.end(),minn));
	for(auto &&it:res) it-=minn;
	std::sort(res.begin(),res.end(),[&](const vec &a,const vec &b)->bool{return a.angle()<b.angle();});
	for(auto &&it:res) it+=minn;
	res.insert(res.begin(),minn);
	return res;
}
long double area(polygon a)
{
	if(a.empty()) return -1e18;
	long double ans=0;
	for(int i=1;i+1<SZ(a);++i) ans+=(a[i]-a[0])^(a[i+1]-a[0]);
	return ans;
}
polygon get()
{
	int n;read(n);
	polygon a(n);
	for(auto &&it:a) scanf("%Lf %Lf",&it.x,&it.y);
	return a;
}
vec v1,v2;
polygon a,b;
inline long double calc(long double mid)
{
	polygon A(a),B(b);
	for(auto &&it:A) it+=v1*mid;
	for(auto &&it:B) it+=v2*mid;
	return area(intersect(A,B));
}
long double getp(polygon a,polygon tmp,const vec &v1,const vec &v2)
{
	tmp.pb(tmp[0]);
	for(auto it:a)
	{
		long double _l=0,_r=5e8;
		for(int j=0;j+1<SZ(tmp);++j)
		{
			if(((tmp[j]-it)^(tmp[j+1]-it))>=0)
			{
				long double L=0,R=1e9;
				int T=80;
				while(T--)
				{
					long double mid=(L+R)/2.0;
					vec qwq=it+v1*mid,a=tmp[j]+v2*mid,b=tmp[j+1]+v2*mid;
					if(((a-qwq)^(b-qwq))>=0) L=mid;
					else R=mid;
				}
				chmin(_r,R);
			}
			else
			{
				long double L=0,R=1e9;
				int T=80;
				while(T--)
				{
					long double mid=(L+R)/2.0;
					vec qwq=it+v1*mid,a=tmp[j]+v2*mid,b=tmp[j+1]+v2*mid;
					if(((a-qwq)^(b-qwq))>=0) R=mid;
					else L=mid;
				}
				chmax(_l,L);
			}
		}
		if(_l<=_r) return (_l+_r)/2.0;
	}
	return -1e18;
}
int main()
{
	a=get();scanf("%Lf %Lf",&v1.x,&v1.y);
	b=get();scanf("%Lf %Lf",&v2.x,&v2.y);
	std::reverse(a.begin(),a.end()),std::reverse(b.begin(),b.end());
	long double l=0,r=1e9;
	long double p=max(getp(a,b,v1,v2),getp(b,a,v2,v1));
	if(p<0) return puts("never"),0;
	int T=100;
	while(T--)
	{
		long double mid=(l+r)/2.0;
		long double A=calc(mid),B=calc(mid+1e-7);
		if(A<-1&&B<-1)
		{
			if(mid<=p) l=mid;
			else r=mid+1e-7;
		}
		else
		{
			if(abs(A-B)<=1e-10) r=mid+1e-7;
			else
			{
				if(A>=B) r=mid+1e-7;
				else l=mid;
			}
		}
	}
	printf("%.8Lf\n",l);
	return 0;
}

