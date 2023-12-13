#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; cin >> n >> m;
	vector<int> a(n), tr;
	for(int i = 0; i < n; ++i) cin >> a[i];
	while(__builtin_popcount(n)!=1){
		n++;
		a.push_back(0);
	}
	tr.resize(2*n);
	for(int i = 0; i < n; ++i) tr[n+i] = a[i];
	for(int i = n-1; i >= 1; --i) tr[i] = max(tr[2*i],tr[2*i+1]);
	while(m--){
		int t; cin >> t;
		if(t==1){
			int i, v; cin >> i >> v;
			tr[n+i] = v;
			for(int j = (n+i)/2; j >= 1; j/=2) tr[j] = max(tr[2*j],tr[2*j+1]);
		}
		else{
			int x; cin >> x;
			function<int(int)> query;
			query = [&](int node){
				if(tr[node] < x) return -1;
				if(node >= n) return (node-n);
				if(tr[2*node] >= x) return query(2*node);
				else return query(2*node+1);
			};
			cout << query(1) << endl;
		}
	}
	return 0;
}
