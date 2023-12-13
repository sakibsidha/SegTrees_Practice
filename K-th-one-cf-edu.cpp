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

vi tr;

int query(int node, int k, int n){
	if(node >= n) return (node-n);
	if(tr[2*node] >= k) return query(2*node, k, n);
	else return query(2*node+1, k - tr[2*node], n);
}

void solve(){
	int n, m; cin >> n >> m;
	vi a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	while(__builtin_popcount(n)!=1){
		n++;
		a.pb(0);
	}
	tr.resize(2*n);
	// build 
	for(int i = 0; i < n; ++i) tr[i+n] = a[i];
	for(int i = n-1; i >= 1; --i) tr[i] = tr[2*i] + tr[2*i+1];
	while(m--){
		int t; cin >> t;
		if(t == 1){
			int i; cin >> i;
			// update
			tr[n+i] = ((tr[n+i]==1)? 0 : 1);
			for(int j = (n+i)/2; j >= 1; j/=2) tr[j] = tr[2*j] + tr[2*j+1];
		}
		else{
			int k; cin >> k;
			cout << query(1,k+1,n) << endl;
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
