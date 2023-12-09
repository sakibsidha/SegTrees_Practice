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

ll f(ll node, ll n_l, ll n_r, ll q_l, ll q_r){
	if(q_l <= n_l && q_r >= n_r) return tr[node];
	if(n_r < q_l || q_r < n_l) return -1;
	ll avg = (n_l + n_r) / 2;
	ll L = f(2*node,n_l,avg,q_l, q_r);
	ll R = f(2*node+1,avg+1,n_r,q_l,q_r);
	if(L!=-1 && R!=-1) return (L + R);
	else{
		if(L==-1) return R;
		else return L;
	}
}

void build(ll n,vll& v){
	tr.resize(2*n);
	for(int i = 0; i < n; ++i) tr[n+i] = v[i];
	for(int i = n-1; i >= 1; --i) tr[i] = tr[2*i] + tr[2*i+1];
}

void updateIter(ll n, ll i, ll val){
	tr[n+i] = val;
	for(int j = (n+i)/2; j >= 1; j/=2){
		tr[j] = tr[2*j] + tr[2*j+1];
	}
}

void updateRec(ll node, ll n_l, ll n_r, ll q_l, ll q_r, ll val){
	if(n_l >= q_l && n_r <= q_r){
		tr[node] = val;
		return;
	}
	if(n_l > q_r || n_r < q_l) return;
	ll avg = (n_l + n_r)/2;
	updateRec(2*node,n_l,avg,q_l,q_r,val);
	updateRec(2*node+1,avg+1,n_r,q_l,q_r,val);
	tr[node] = tr[node*2] + tr[node*2+1];
}

void solve(){
	ll n, q;
	cin >> n >> q;
	vector<ll> v(n);
	for(int i = 0; i < n; ++i) cin >> v[i];
	while(__builtin_popcount(n)!=1){
		v.push_back(0);
		n++;
	}
	build(n,v);
	while(q--){
		ll t; cin >> t;
		if(t==1){
			ll k, u; cin >> k >> u;
			k--;
			updateRec(1,0,n-1,k,k,u);
			// updateIter(n,k,u);
		}
		else{
			ll l, r; cin >> l >> r;
			l--; r--;
			cout << f(1,0,n-1,l,r) << endl;
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
