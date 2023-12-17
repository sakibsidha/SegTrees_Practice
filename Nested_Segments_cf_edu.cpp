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

void solve(){
	int n; cin >> n;
	vi a(2*n);
	for(int i = 0; i < 2*n; ++i) cin >> a[i];
	int size = 2*n;
	while(__builtin_popcount(size)!=1) size++;
	vi tr;
	tr.resize(2*size);
	vi v(n+1,-1);
	vpi ans;
	for(int i = 0; i < sz(a); ++i){
		if(v[a[i]]==-1) v[a[i]] = i;
		else{
			int l = v[a[i]], r = i;
			function<int(int,int,int)> sum = [&] (int node, int n_l, int n_r){
				if(n_l >= l && n_r <= r) return tr[node];
				if(n_l > r || n_r < l) return 0;
				int m = (n_r + n_l) / 2;
				return sum(2*node,n_l,m) + sum(2*node+1,m+1,n_r);
			};
			ans.pb({a[i],sum(1,0,size-1)});
			tr[size+l] = 1;
			for(int j = (size+l)/2; j >= 1; j/=2) tr[j] = tr[2*j] + tr[2*j+1];
		}
	}
	sort(all(ans));
	for(auto it: ans) cout << it.se << " ";
	cout << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	//int tc; cin >> tc;
	//while(tc--)
		solve();

	return 0;
}
