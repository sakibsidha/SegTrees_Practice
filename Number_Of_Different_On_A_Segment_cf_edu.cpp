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

ll query(ll node, ll n_l, ll n_r, ll l, ll r, vll& tr){
	if(n_l >= l && n_r <= r) return tr[node];
	if(n_l > r || n_r < l) return 0;
	ll m = (n_l + n_r) / 2;
	return (query(2*node,n_l,m,l,r,tr) | query(2*node+1,m+1,n_r,l,r,tr));
}

void solve(){
	ll n, q; cin >> n >> q;
	vll a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	while(__builtin_popcountll(n)!=1){
		n++;
		a.pb(0LL);
	}
	vll tr; tr.resize(2*n);
	for(int i = 0; i < n; ++i){
		tr[i+n] = (tr[i+n] | (1LL << a[i]));
	}
	for(int i = n-1; i >= 1; --i) tr[i] = (tr[2*i] | tr[2*i+1]);
	while(q--){
		ll t; cin >> t;
		if(t==2){
			ll i, v; cin >> i >> v;
			i--;
			tr[i+n] = 0;
			tr[i+n] = (tr[i+n] | (1LL << v));
			for(int j = (i+n)/2; j >= 1; j/=2) tr[j] = (tr[j*2] | tr[j*2+1]);
		}
		else{
			ll l, r; cin >> l >> r;
			l--; r--;
			cout << __builtin_popcountll(query(1,0,n-1,l,r,tr)) << endl;
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
