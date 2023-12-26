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

ll n, q; 

typedef struct node{
	ll sum, prop;
} node;
vector<node> tr;

void update(ll nd, ll n_l, ll n_r, ll l, ll r, ll v){
	if(n_l >= l && n_r <= r){
		tr[nd].sum += (n_r-n_l+1)*v;
		tr[nd].prop += v;
		return;
	}
	if(n_l > r || n_r < l) return;
	ll mid = (n_l + n_r) / 2;
	update(2*nd,n_l,mid,l,r,v);
	update(2*nd+1,mid+1,n_r,l,r,v);
	tr[nd] = {tr[2*nd].sum + tr[2*nd+1].sum + tr[nd].prop*(n_r-n_l+1),tr[nd].prop};
}

ll query(ll nd, ll n_l, ll n_r, ll l, ll r, ll carry = 0){
	if(n_l >= l && n_r <= r){
		return tr[nd].sum + (n_r-n_l+1)*carry;
	}
	if(n_l > r || n_r < l) return 0;
	ll mid = (n_l + n_r) / 2;
	return query(2*nd,n_l,mid,l,r,carry+tr[nd].prop) + query(2*nd+1,mid+1,n_r,l,r,carry+tr[nd].prop);
}

void printTree(){
	for(int i = 0; i < 2*n; ++i){
		cout << "i: " << i << " sum: " << tr[i].sum << " prop: " << tr[i].prop << endl;
	}
	cout << endl;
}

void solve(){
	cin >> n >> q;
	vll a(n,0);
	while(__builtin_popcount(n)!=1){
		n++;
		a.pb(0);
	}
	tr.resize(2*n);
	while(q--){
		ll t; cin >> t;
		if(t==1){
			ll l, r, v; cin >> l >> r >> v; r--;
			update(1,0,n-1,l,r,v);
			// printTree();
		}
		else{
			ll l, r; cin >> l >> r; r--;
			cout << query(1,0,n-1,l,r,0) << endl;
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
