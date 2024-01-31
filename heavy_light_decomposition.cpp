#include <bits/stdc++.h>
//https://www.acmicpc.net/problem/17033

using namespace std;

#define nl '\n'
#define fi first
#define se second

typedef long long ll;

const int N = 1e5 + 5;

vector<int> g[N];
vector<int> parent(N), depth(N), heavy(N, -1), head(N), pos(N);
int time_stamp = 0;

int n, arr[N];

struct node{
	ll left, right, maxx, total;
	node(){};
	node(ll L, ll R, ll MX, ll TOT){
		left = L;
		right = R;
		maxx = MX;
		total = TOT;
	}
};
// there's a function named merge in STL, so i'll name this 'fusion' (from dragon ball), haha
node fusion(node L, node R){
	node M;
	M.total = L.total + R.total;
	M.maxx = max({L.maxx, R.maxx, L.right + R.left});
	M.left = max(L.left, L.total + R.left);
	M.right = max(R.right, R.total + L.right);
	return M;
}

vector<node> tree(4 * N);
vector<ll> lazy(4 * N);

void build(int u, int low, int high){
	if(low == high){
		tree[u].total = arr[low];
		tree[u].left = max(0, arr[low]);
		tree[u].right = max(0, arr[low]);
		tree[u].maxx = max(0, arr[low]);
		return;
	}
	int mid = (low + high) / 2;
	build(2 * u, low, mid);
	build(2 * u + 1, mid + 1, high);
	tree[u] = fusion(tree[2 * u], tree[2 * u + 1]);
}
void push(int u, int low, int high){
	int mid = (low + high) / 2;

	lazy[2 * u] = lazy[2 * u + 1] = lazy[u];
	tree[2 * u].total = lazy[u] * (ll)(mid - low + 1);
	tree[2 * u].maxx = tree[2 * u].left = tree[2 * u].right = max(tree[2 * u].total, (ll)0);

	tree[2 * u + 1].total = lazy[u] * (ll)(high - mid);
	tree[2 * u + 1].maxx = tree[2 * u + 1].left = tree[2 * u + 1].right = max(tree[2 * u + 1].total, (ll)0);

	lazy[u] = 1e9;
}
void modify(int u, int low, int high, int l, int r, int val){
	if(low > r || high < l) return;
	if(low >= l && high <= r){
		lazy[u] = val;
		tree[u].total = (ll)val * (high - low + 1);
		tree[u].maxx = tree[u].left = tree[u].right = max(tree[u].total, (ll)0);
		if(low < high) push(u, low, high);
		return;
	}
	if(lazy[u] != 1e9) push(u, low, high);
	int mid = (low + high) / 2;
	modify(2 * u, low, mid, l, r, val);
	modify(2 * u + 1, mid + 1, high, l, r, val);
	tree[u] = fusion(tree[2 * u], tree[2 * u + 1]);
}
node get(int u, int low, int high, int l, int r){
	if(lazy[u] != 1e9 && low < high) push(u, low, high);
	if(low > r || high < l){
		node ret(0, 0, 0, 0);
		return ret;
	}
	if(low >= l && high <= r) return tree[u];
	int mid = (low + high) / 2;
	return fusion(get(2 * u, low, mid, l, r), get(2 * u + 1, mid + 1, high, l, r));
}
int dfs(int u){
	int size = 1;
	int max_child_size = 0;
	for(auto x: g[u]){
		if(x == parent[u]) continue;
		parent[x] = u;
		depth[x] = depth[u] + 1;
		int child_size = dfs(x);
		size += child_size;
		if(child_size > max_child_size){
			max_child_size = child_size;
			heavy[u] = x;
		}
	}
	return size;
}
void decompose(int u, int h){
	head[u] = h;
	pos[u] = time_stamp++;
	if(heavy[u] != -1) decompose(heavy[u], h);
	for(auto x: g[u]){
		if(x != parent[u] && x != heavy[u]) decompose(x, x);
	}
}
void init(int root){
	time_stamp = 0;
	dfs(root);
	decompose(root, root);
}
void update(int u, int v, int w){
	for(; head[u] != head[v]; v = parent[head[v]]){
		if(depth[head[u]] > depth[head[v]]) swap(u, v);
		modify(1, 0, n - 1, pos[head[v]], pos[v], w);
	}
	if(depth[u] > depth[v]) swap(u, v);
	modify(1, 0, n - 1, pos[u], pos[v], w);
}
ll query(int u, int v){
	node L(0, 0, 0, 0);
	node R(0, 0, 0, 0);
	if(pos[u] > pos[v]) swap(u, v);
	for(; head[u] != head[v];){
		if(depth[head[u]] > depth[head[v]]){
			node cur = get(1, 0, n - 1, pos[head[u]], pos[u]);
			L = fusion(cur, L);
			u = parent[head[u]];
		}
		else{
			node cur = get(1, 0, n - 1, pos[head[v]], pos[v]);
			R = fusion(cur, R);
			v = parent[head[v]];
		}
	}
	if(depth[u] > depth[v]) L = fusion(get(1, 0, n - 1, pos[v], pos[u]), L);
	else R = fusion(get(1, 0, n - 1, pos[u], pos[v]), R);
	swap(L.left, L.right);
	node res = fusion(L, R);
	return res.maxx;
}
void Solve(){
	for(int i = 0; i < 4 * N; i++)
		lazy[i] = 1e9;
	cin>>n;
	vector<int> tmp(n);
	for(int i = 0; i < n; i++)
		cin>>tmp[i];
	for(int i = 1; i < n; i++){
		int u, v;
		cin>>u>>v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	init(0);
	for(int i = 0; i < n; i++){
		arr[pos[i]] = tmp[i];
	}
	build(1, 0, n - 1);
	int q;
	cin>>q;
	while(q--){
		int t;
		cin>>t;
		if(t == 1){
			int u, v;
			cin>>u>>v;
			u--; v--;
			cout<<query(u, v)<<nl;
		}
		else{
			int u, v, w;
			cin>>u>>v>>w;
			u--; v--;
			update(u, v, w);
		}
	}

}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Solve();
}
