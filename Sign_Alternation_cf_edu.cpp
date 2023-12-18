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
	ll mid = (n_l + n_r) / 2;
	return query(2*node,n_l,mid,l,r,tr) + query(2*node+1,mid+1,n_r,l,r,tr);
}

void solve(){
	ll n; cin >> n;
	vll a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	while(__builtin_popcount(n)!=1){
		n++;
		a.pb(0);
	}
	vll tr_odd, tr_even;
	tr_odd.resize(2*n);
	tr_even.resize(2*n);
	// build
	for(int i = 0; i < n; ++i){
		if(i%2){
			tr_odd[n+i] = a[i];
			tr_even[n+i] = 0;
		}
		else{
			tr_even[n+i] = a[i];
			tr_odd[n+i] = 0;
		}
	}
	for(int i = n-1; i >= 1; --i){
		tr_even[i] = tr_even[2*i] + tr_even[2*i+1];
		tr_odd[i] = tr_odd[2*i] + tr_odd[2*i+1];
	}
	// query
	ll q; cin >> q;
	while(q--){
		ll t; cin >> t;
		if(t){
			ll l, r; cin >> l >> r;
			l--; r--;
			ll odd_sum = query(1,0,n-1,l,r,tr_odd);
			ll even_sum = query(1,0,n-1,l,r,tr_even);
			if(l%2)	cout << odd_sum-even_sum << endl;
			else cout << even_sum-odd_sum << endl;
		} 
		else{
			ll i, v; cin >> i >> v;
			i--;
			if(i%2){
				tr_odd[n+i] = v;
				for(int j = (n+i)/2; j >= 1; j/=2) tr_odd[j] = tr_odd[2*j] + tr_odd[2*j+1];
			}
			else{
				tr_even[n+i] = v;
				for(int j = (n+i)/2; j >= 1; j/=2) tr_even[j] = tr_even[2*j] + tr_even[2*j+1];
			}
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
