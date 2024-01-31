#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//https://www.acmicpc.net/problem/1761

using namespace std;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define nl '\n'
#define fi first
#define se second

typedef long long ll;

const int N = 1e5 + 5;

vector<pair<int, int>> g[N];
vector<vector<int>> lift(N, vector<int> (20));
vector<int> depth(N);
vector<long long> dist(N);

void dfs(int u, int v = -1){
	for(auto [x, w]: g[u]){
		if(x == v) continue;
		dist[x] = dist[u] + w;
		dfs(x, u);
	}
}
void buildLCA(int u, int p){
	lift[u][0] = p;
	for(int i = 1; i < 20; i++){
		if(lift[u][i - 1] == -1) lift[u][i] = -1;
		else lift[u][i] = lift[lift[u][i - 1]][i - 1];
	}
	for(auto [x, w]: g[u])
		if(x != p){
			depth[x] = depth[u] + 1;
			buildLCA(x, u);
		}
}
int k_th_ancestor(int u, int k){
	for(int i = 19; i >= 0; i--){
		if(u == -1) return u;
		if((1 << i) <= k){
			u = lift[u][i];
			k -= (1 << i);
		}
	}
	return u;
}
int lca(int a, int b){
	if(depth[a] < depth[b]) swap(a, b);
	int diff = depth[a] - depth[b];
	int u = k_th_ancestor(a, diff);
	if(u == b) return u;
	for(int i = 19; i >= 0; i--){
		if(lift[u][i] != lift[b][i]){
			u = lift[u][i];
			b = lift[b][i];
		}
	}
	return lift[b][0];
}
void Solve(){
	int n;
	cin>>n;
	for(int i = 1; i < n; i++){
		int u, v, w;
		cin>>u>>v>>w;
		u--; v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	buildLCA(0, -1);
	dfs(0);
	int q;
	cin>>q;
	while(q--){
		int u, v;
		cin>>u>>v;
		u--; v--;
		int anc = lca(u, v);
		int res = dist[u] + dist[v] - 2 * dist[anc];
		cout<<res<<nl;
	}

}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Solve();
}
