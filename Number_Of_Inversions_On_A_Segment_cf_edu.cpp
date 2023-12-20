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

typedef struct node{
	ll cnt; // ei node er under er total range er number of inversions
	ll sobai[41]; // ke kotobar ache
}node;
vector<node> tr;

ll query(ll nd, ll n_l, ll n_r, ll l, ll r, vll& left){
	if(n_l >= l && n_r <= r){
		ll c = 0;
		for(ll i = 1; i <= 40; ++i){
			if(tr[nd].sobai[i]){
				for(ll j = i+1; j <= 40; ++j){
					c += (tr[nd].sobai[i]*left[j]);
				}
			}
		}
		for(ll i = 1; i <= 40; ++i){
			left[i] += tr[nd].sobai[i];
		}
		return (c + tr[nd].cnt);
	}
	if(n_l > r || n_r < l) return 0;
	ll m = (n_l + n_r) / 2;
	ll L = query(nd*2,n_l,m,l,r,left);
	ll R = query(nd*2+1,m+1,n_r,l,r,left);
	return L+R;
}

void solve(){
	ll n, q; cin >> n >> q;
	vll a(n);
	for(ll i = 0; i < n; ++i){
		cin >> a[i];
	}
	while(__builtin_popcountll(n)!=1){
		n++;
		a.pb(0);
	}
	tr.resize(2*n);
	for(ll i = 0; i < n; ++i){
		tr[n+i].cnt = 0;
		tr[n+i].sobai[a[i]]++;
	}
	for(ll i = n-1; i >= 1; --i){
		ll left = 2*i, right = 2*i+1;
		ll c = 0;
		for(ll j = 1; j <= 40; ++j){
			if(tr[right].sobai[j]){
				for(ll k = j+1; k <= 40; ++k){
					c += (tr[right].sobai[j]*tr[left].sobai[k]);
				}
			}
		}
		for(ll j = 1; j <= 40; ++j){
			tr[i].sobai[j] += (tr[left].sobai[j] + tr[right].sobai[j]);
		}
		tr[i].cnt = c + tr[right].cnt + tr[left].cnt;
	}
	//for(int i = 0; i < 2*n; ++i){
		//cout << "node " << i << ", " << "cnt: " << tr[i].cnt << " present: ";
		//for(int j = 1; j <= 40; ++j){
			//if(tr[i].sobai[j]) cout << j << "-" << tr[i].sobai[j] << " ";
		//}
		//cout << endl;
	//}
	while(q--){
		ll t; cin >> t;
		if(t==2){
			ll ii, v; cin >> ii >> v;
			ii--;
			tr[ii+n].cnt = 0;
			for(ll i = 1; i <= 40; ++i){
				tr[ii+n].sobai[i] = 0;
			}
			tr[ii+n].sobai[v]++;
			for(ll i = (ii+n)/2; i >= 1; i/=2){
				for(ll k = 1; k <= 40; ++k){
					tr[i].sobai[k] = 0;
				}
				ll left = 2*i, right = 2*i+1;
				ll c = 0;
				for(ll j = 1; j <= 40; ++j){
					if(tr[right].sobai[j]){
						for(ll k = j+1; k <= 40; ++k){
							c += (tr[right].sobai[j]*tr[left].sobai[k]);
						}
					}
				}
				for(ll j = 1; j <= 40; ++j){
					tr[i].sobai[j] += (tr[left].sobai[j] + tr[right].sobai[j]);
				}
				tr[i].cnt = c + tr[right].cnt + tr[left].cnt;
			}
		}
		else{
			ll L, R; cin >> L >> R;
			L--; R--;
			vll left(41);
			cout << query(1,0,n-1,L,R,left) << endl;
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
