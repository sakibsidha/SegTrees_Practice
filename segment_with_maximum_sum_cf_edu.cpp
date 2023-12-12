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

/*
 things we need to keep track of for each node:
 1. maximum prefix 2. maximum suffix 3. ans (maximum subsegment sum) 4. total sum
 
 when merged,
 1. maximum prefix = max(prefix of left child, sum of left child + prefix of right child);
 2. maximum suffix = max(suffix of right child, sum of right child + suffix of left child);
 3. maximum seg sum (ans) = max(left seg ans, right seg ans,suffix of left + prefix of right);
 4. sum = left child sum + right child sum
 
 */

typedef struct node {
	ll pre, suf, ans, sum;
} node;

vector<node> tr;

void build(vll& a, ll n){
	for(int i = 0; i < n; ++i){
		tr[i+n] = {a[i],a[i],a[i],a[i]};
	}
	for(int i = n-1; i >= 1; --i){
		tr[i].pre = max(tr[2*i].pre,tr[2*i].sum + tr[2*i+1].pre);
		tr[i].suf = max(tr[2*i+1].suf,tr[2*i+1].sum + tr[2*i].suf);
		tr[i].ans = max(tr[2*i].ans,tr[2*i+1].ans);
		tr[i].ans = max(tr[i].ans, tr[2*i].suf + tr[2*i+1].pre);
		tr[i].sum = tr[2*i].sum + tr[2*i+1].sum;
	}
}

void update(ll j, ll v, ll n){
	tr[j+n] = {v,v,v,v};
	for(int i = (j+n)/2; i >= 1; i/=2){
		tr[i].pre = max(tr[2*i].pre,tr[2*i].sum + tr[2*i+1].pre);
		tr[i].suf = max(tr[2*i+1].suf,tr[2*i+1].sum + tr[2*i].suf);
		tr[i].ans = max(tr[2*i].ans,tr[2*i+1].ans);
		tr[i].ans = max(tr[i].ans, tr[2*i].suf + tr[2*i+1].pre);
		tr[i].sum = tr[2*i].sum + tr[2*i+1].sum;
	}
}

void print_tr(ll n){
	for(int i = 0; i < 2*n; ++i){
		cout << "{" << tr[i].pre << "," << tr[i].suf << "," << tr[i].ans << "," << tr[i].sum << "}" << " ";
	}
	cout << endl;	
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
	build(a,n);
	cout << ((tr[1].ans < 0) ? 0 : tr[1].ans) << endl;
	while(m--){
		ll i, v; cin >> i >> v;
		update(i,v,n);
		cout << ((tr[1].ans < 0) ? 0 : tr[1].ans) << endl;
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
