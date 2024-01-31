#include<bits/stdc++.h>

using namespace std;

#define nl '\n'
#define fi first
#define se second

const int N = 1e5 + 5;

int child[N], del[N];
vector<int> g[N];
int dist[20][N];
vector<int> ans(N, INT_MAX);
int label[N];
vector<int> ancestor(N);

void countChild(int u, int parent){
	child[u] = 1;
	for(auto x: g[u]){
		if(x == parent || del[x]) continue;
		countChild(x, u);
		child[u] += child[x];
	}
}
int centroid(int u, int parent, int treeSize){
	for(auto x: g[u]){
		if(x == parent || child[x] <= treeSize / 2 || del[x]) continue;
		return centroid(x, u, treeSize);
	}
	return u;
}
void dfs(int u, int parent, int root, int h){
	for(auto x: g[u]){
		if(x == parent || del[x]) continue;
		dist[h][x] = dist[h][u] + 1;
		ancestor[x] = root;
		dfs(x, u, root, h);
	}
}
int dfs2(int u, int parent = -1){
	int res = 1e9;
	if(u == 1) res = 0;
	for(auto x: g[u]){
		if(x == parent || del[x]) continue;
		res = min(res, dfs2(x, u) + 1);
	}
	return res;
}
void decompose(int u, int h){
	countChild(u, 0);
	int tSize = child[u];
	int root = centroid(u, 0, tSize);
	label[root] = h;
	dist[h][root] = 0;
	dfs(root, -1, root, h);
	ans[root] = dfs2(root);
	del[root] = 1;
	for(auto x: g[root]){
		if(del[x]) continue;
		decompose(x, h + 1);
	}
}
void update(int u){
	int k = u;
	while(ancestor[u]){
		int p = ancestor[u];
		ans[p] = min(ans[p], dist[label[p]][k]);
		u = p;
	}
}
int get(int u){
	int res = ans[u];
	int k = u;
	while(ancestor[u]){
		int p = ancestor[u];
		res = min(res, ans[p] + dist[label[p]][k]);
		u = p;
	}
	return res;
}
void Solve(){
	int n, m;
	cin>>n>>m;
	for(int i = 1; i < n; i++){
		int u, v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	decompose(1, 0);
	while(m--){
		int typ, u;
		cin>>typ>>u;
		if(typ == 1){
			ans[u] = 0;
			update(u);
		}
		else{
			cout<<get(u)<<nl;
		}
	}
	
}
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int tests = 1;
	//cin>>tests;
	while(tests--){
		Solve();
	}
}
