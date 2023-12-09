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

vll tr;

void build(ll n, vll& v){
	tr.resize(2*n);
	for(int i = 0; i < n; ++i){
		tr[n+i] = v[i];
	}
}

void updateRange(ll node, ll n_l, ll n_r, ll a, ll b, ll u){
	if(n_l >= a && n_r <= b){
		tr[node] += u;
		return;
	}
	if(n_l > b || n_r < a) return;
	ll avg = (n_l + n_r) / 2;
	updateRange(2*node, n_l, avg, a, b, u);
	updateRange(2*node+1, avg+1, n_r, a, b, u);
}

ll valueAt(ll k,ll n){
	ll sum = tr[n+k];
	for(int i = (n+k)/2; i >= 1; i/=2){
		sum += tr[i];
	}
	return sum;
}

void solve(){
	ll n, q; cin >> n >> q;
	vll v(n);
	for(int i = 0; i < n; ++i) cin >> v[i];
	while(__builtin_popcount(n)!=1){
		n++;
		v.pb(0);
	}
	build(n,v);
	while(q--){
		ll f; cin >> f;
		if(f==1){
			ll a, b, u; cin >> a >> b >> u;
			a--; b--;
			updateRange(1,0,n-1,a,b,u);
		}
		else{
			ll k; cin >> k;
			k--;
			cout << valueAt(k,n) << endl;
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	//int tc; cin >> tc;
	//while(tc--)
		solve();

	return 0;
}
