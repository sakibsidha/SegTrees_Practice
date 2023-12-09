#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
n -> node, q -> query
r-l -> right-left

int f(int node, int node_left, int node_right, int query_left, int query_right){
	if(the node is completely within the interval [query_left,query_right]) return tree[node];
	if(the node is disjoint with interval [q_l,q_h]) return 0;
	int avg (i.e. left_tree_nodes_right_child) = (node_left + node_right) / 2;
	return f(2*node, node_left, avg, query_left, query_right) + f(2*node+1, avg+1, node_right,query_left, query_right);
}

remarks:
* left child can be found by 2*node, right by 2*node+1

*/

vector<ll> tree;

ll f(ll node, ll n_l, ll n_r, ll q_l, ll q_r){
	if(q_l <= n_l && q_r >= n_r) return tree[node];
	if(n_r < q_l || q_r < n_l) return 0;
	ll avg = (n_l + n_r) / 2;
	return f(2*node,n_l,avg,q_l, q_r) + f(2*node+1,avg+1,n_r,q_l,q_r);
}

void build(ll n,vector<ll>& v){
	tree.resize(2*n);
	for(int i = 0; i < n; ++i) tree[n+i] = v[i];
	for(int i = n-1; i >= 1; --i) tree[i] = tree[2*i] + tree[2*i+1];
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
		int l, r; cin >> l >> r;
		l--; r--;
		cout << f(1,0,n-1,l,r) << endl;
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
