#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
using ld = long double;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vb = vector<bool>;
template<class T>
using indexed_set = tree<T,null_type,less<T>,rb_tree_tag,
tree_order_statistics_node_update>;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ins insert
#define all(x) (x).begin(),(x).end()
#define sz(y) (int) y.size()
#define endl "\n"
#define sim template < class c 
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {  
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {  
  *this << "[";  
  for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define db(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

typedef struct mat{
	ll a, b, c, d;
}mat;

void solve(){
	ll r, n, m; cin >> r >> n >> m;
	vector<mat> v(n);
	for(int i = 0; i < n; ++i){
		ll a, b, c, d; cin >> a >> b >> c >> d;
		v[i] = {a,b,c,d};
	}
	while(__builtin_popcount(n)!=1){
		n++; v.pb({0,0,0,0});
	}
	vector<mat> tr; tr.resize(2*n);
	for(int i = 0; i < n; ++i){
		tr[i+n] = v[i];
	}
	for(int i = n-1; i >= 1; --i){
		mat mt;
		mt.a = ((tr[2*i].a*tr[2*i+1].a)%r + (tr[2*i].b*tr[2*i+1].c)%r)%r;
		mt.b = ((tr[2*i].a*tr[2*i+1].b)%r + (tr[2*i].b*tr[2*i+1].d)%r)%r;
		mt.c = ((tr[2*i].c*tr[2*i+1].a)%r + (tr[2*i].d*tr[2*i+1].c)%r)%r;
		mt.d = ((tr[2*i].c*tr[2*i+1].b)%r + (tr[2*i].d*tr[2*i+1].d)%r)%r;

		tr[i] = mt;
	}
	while(m--){
		ll L, R; cin >> L >> R;
		L--; R--;
		mat nullmat = {-1,-1,-1,-1};
		function<mat(ll,ll,ll)> query = [&](ll node, ll n_l, ll n_r){
			if(n_l >= L && n_r <= R) return tr[node];
			if(n_l > R || n_r < L) return nullmat;
			ll mid = (n_l + n_r) / 2;
			mat mat1 = query(2*node,n_l,mid);
			mat mat2 = query(2*node+1,mid+1,n_r);
			if(mat1.a!=-1 && mat2.a!=-1 && mat1.b!=-1 && mat2.b!=-1 && mat1.c !=-1 && mat2.c!=-1 && mat1.d!=-1 && mat2.d!=-1){
				mat ret;
				ret.a = ((mat1.a*mat2.a)%r + (mat1.b*mat2.c)%r)%r;
				ret.b = ((mat1.a*mat2.b)%r + (mat1.b*mat2.d)%r)%r;
				ret.c = ((mat1.c*mat2.a)%r + (mat1.d*mat2.c)%r)%r;
				ret.d = ((mat1.c*mat2.b)%r + (mat1.d*mat2.d)%r)%r;
				return ret;
			}
			else{
				if(mat1.a==-1 && mat1.b==-1 && mat1.c==-1 && mat1.d==-1) return mat2;
				else return mat1;
			}
		};
		mat ans = query(1,0,n-1);
		cout << ans.a << " " << ans.b << endl << ans.c << " " << ans.d << endl;
		cout << endl;
	}
}

/*a1 b1
c1 d1

a2 b2
c2 d2

= a1*a2+b1*c2 	a1*b2+b1*d2 	c1*a2+d1*c2 	c1*b2+d1*d2 

*/
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	//int tc; cin >> tc;
	//while(tc--)
		solve();

	return 0;
}
