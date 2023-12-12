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

vpl tr;

void build(ll n, vll& a){
	for(int i = 0; i < n; ++i) tr[n+i] = {a[i],1};
	for(int i = n-1; i >= 1; --i){
		if(tr[2*i].fi == tr[2*i+1].fi) tr[i] = {tr[2*i].fi, tr[2*i].se + tr[2*i+1].se};
		else{
			if(tr[2*i] < tr[2*i+1]) tr[i] = tr[2*i];
			else tr[i] = tr[2*i+1];
		}
	}
}

pl query(ll node, ll n_l, ll n_r, ll l, ll r){
	if(n_l >= l && n_r <= r) return tr[node];
	if(n_l > r || n_r < l) return {LLONG_MAX,-1};
	ll mid = (n_l + n_r) / 2;
	pl L = query(2*node,n_l,mid,l,r), R = query(2*node+1,mid+1,n_r,l,r);
	if(L.fi==R.fi) return {L.fi,L.se+R.se};
	else return ((L.fi < R.fi) ? L : R);
}

void update(ll node, ll n_l, ll n_r, ll l, ll r, ll v){
	if(n_l >= l && n_r <= r){
		tr[node] = {v, 1};
		return;
	}
	if(n_l > r || n_r < l) return;
	ll avg = (n_l+n_r)/2;
	update(2*node,n_l,avg,l,r,v);
	update(2*node+1,avg+1,n_r,l,r,v);
	ll i = node;
	if(tr[2*i].fi == tr[2*i+1].fi) tr[i] = {tr[2*i].fi, tr[2*i].se + tr[2*i+1].se};
	else{
		if(tr[2*i] < tr[2*i+1]) tr[i] = tr[2*i];
		else tr[i] = tr[2*i+1];
	}
}

void update(ll j, ll v, ll n){
	tr[n+j] = {v,1};
	for(int i = (n+j)/2; i >= 1; i/=2){
		if(tr[2*i].fi == tr[2*i+1].fi) tr[i] = {tr[2*i].fi, tr[2*i].se + tr[2*i+1].se};
		else{
			if(tr[2*i] < tr[2*i+1]) tr[i] = tr[2*i];
			else tr[i] = tr[2*i+1];
		}
	}
}

void solve(){
	ll n, m; cin >> n >> m;
	vll a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	while(__builtin_popcount(n)!=1){
		n++;
		a.pb(0);
	}
	tr.resize(2*n);
	build(n,a);
	while(m--){
		ll c; cin >> c;
		if(c == 1){
			ll i, v; cin >> i >> v;
			//update(1,0,n-1,i,i,v); 
			update(i, v, n);
		}
		else{
			ll l, r; cin >> l >> r;
			r--;
			pl ans = query(1,0,n-1,l,r);
			cout << ans.fi << " " << ans.se << endl;
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
