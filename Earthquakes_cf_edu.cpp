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

void update(ll i, ll v, ll n){
	tr[i+n] = v;
	for(int j = (i+n)/2; j >= 1; j/=2){
		if(tr[2*j]!=0 && tr[2*j+1]!=0) tr[j] = min(tr[2*j], tr[2*j+1]);
		else{
			if(tr[2*j]==0 && tr[2*j+1]==0) tr[j] = 0;
			else{
				if(tr[2*j]==0) tr[j] = tr[2*j+1];
				else tr[j] = tr[2*j];
			}
		}
	}
}

ll query(ll node, ll n_l, ll n_r, ll l, ll r, ll p,ll n){
	if(n_l >= l && n_r <= r){
		if(tr[node] > p || tr[node]==0) return 0;
		else{
			if(n_l==n_r){
				update(n_l,0,n);
				return 1LL;
			}
		}
	}
	if(n_l > r || n_r < l) return 0;
	ll m = (n_l + n_r) / 2;
	return query(2*node,n_l,m,l,r,p,n) + query(2*node+1,m+1,n_r,l,r,p,n);
}

void solve(){
	ll n; cin >> n;
	ll q; cin >> q;
	while(__builtin_popcount(n)!=1) n++;
	tr.resize(2*n);
	while(q--){
		ll t; cin >> t;
		if(t==1){
			ll i, h; cin >> i >> h;
			update(i,h,n);
		}
		else{
			ll l, r, p; cin >> l >> r >> p;
			r--;
			if(p == 0) cout << 0 << endl;
			else{
				cout << query(1,0,n-1,l,r,p,n) << endl;
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
