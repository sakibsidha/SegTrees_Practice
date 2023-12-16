#include <bits/stdc++.h>
using namespace std;

void solve(){
	int n; cin >> n;
	vector<int> a(n),tr;
	for(int i = 0; i < n; ++i){
		cin >> a[i];
		a[i]--;
	}
	while(__builtin_popcount(n)!=1) n++;
	tr.resize(2*n);
	function<void(int)> update;
	function<int(int,int,int,int,int)> query;
	update = [&](int i){
		tr[n+i]++;
		for(int j = (n+i)/2; j >= 1; j/=2) tr[j] = tr[2*j] + tr[2*j+1];
	};
	query = [&](int node, int n_l, int n_r, int l, int r){
		if(n_l >= l && n_r <= r) return tr[node];
		if(n_l > r || n_r < l) return 0;
		int avg = (n_l+n_r)/2;
		return query(2*node,n_l,avg,l,r) + query(2*node+1,avg+1,n_r,l,r);
	};
	for(int i = 0; i < (int) a.size(); ++i){
		cout << query(1,0,n-1,a[i]+1,n) << " ";
		update(a[i]);
	}
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
