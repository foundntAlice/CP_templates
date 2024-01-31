#include<bits/stdc++.h>

using namespace std;

#define nl '\n'
#define fi first
#define se second

typedef long long ll;

const int N = 3e5 + 5;

const int mod = 1e9 + 7;

struct modint {
	int n;
	modint() :n(0) { ; }
	modint(ll m) {
		if (m < 0 || mod <= m) {
			m %= mod; if (m < 0)m += mod;
		}
		n = m;
	}
	operator int() { return n; }
};
bool operator==(modint a, modint b) { return a.n == b.n; }
bool operator<(modint a, modint b) { return a.n < b.n; }
modint operator+=(modint& a, modint b) { a.n += b.n; if (a.n >= mod)a.n -= (int)mod; return a; }
modint operator-=(modint& a, modint b) { a.n -= b.n; if (a.n < 0)a.n += (int)mod; return a; }
modint operator*=(modint& a, modint b) { a.n = ((ll)a.n * b.n) % mod; return a; }
modint operator+(modint a, modint b) { return a += b; }
modint operator-(modint a, modint b) { return a -= b; }
modint operator*(modint a, modint b) { return a *= b; }
modint operator^(modint a, ll n) {
	if (n == 0)return modint(1);
	modint res = (a * a) ^ (n / 2);
	if (n % 2)res = res * a;
	return res;
}

ll inv(ll a, ll p) {
	return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p);
}
modint operator/(modint a, modint b) { return a * modint(inv(b, mod)); }
modint operator/=(modint& a, modint b) { a = a / b; return a; }

int ability[N], pres[N], arr[N];
vector<int> tree[4 * N];
vector<int> g[N];
vector<int> tin(N), tout(N);
int time_stamp = 0;
vector<int> sz(N);
vector<modint> dp(N);

void dfs(int u, int v = -1){
	tin[u] = time_stamp++;
	sz[u] = 1;
	for(auto x: g[u]){
		if(x == v) continue;
		dfs(x, u);
		sz[u] += sz[x];
	}
	tout[u] = time_stamp - 1;
}
void dfs2(int u, int v = -1){
	for(auto x: g[u]){
		if(x == v) continue;
		dfs2(x, u);
		dp[u] += dp[x];
	}
}
void build(int u, int low, int high){
	if(low == high){
		tree[u] = {arr[low]};
		return;
	}
	int mid = (low + high) / 2;
	build(2 * u, low, mid);
	build(2 * u + 1, mid + 1, high);
	tree[u].resize(high - low + 1);
	merge(tree[2 * u].begin(), tree[2 * u].end(), tree[2 * u + 1].begin(), tree[2 * u + 1].end(), tree[u].begin());	
}
int query(int u, int low, int high, int l, int r, int k){
	if(low > r || high < l) return 0;
	if(low >= l && high <= r){
		int x = upper_bound(tree[u].begin(), tree[u].end(), k) - tree[u].begin();
		return x;
	}
	int mid = (low + high) / 2;
	return query(2 * u, low, mid, l, r, k) + query(2 * u + 1, mid + 1, high, l, r, k);
}
void Solve(){
	int n, m;
	cin>>n>>m;
	int root = 0;
	for(int i = 0; i < n; i++){
		int x;
		cin>>x;
		if(x == 0) root = i;
		else{
			g[i].push_back(x - 1);
			g[x - 1].push_back(i);
		}
	}
	dfs(root);
	for(int i = 0; i < n; i++){
		cin>>ability[i];
	}
	for(int i = 0; i < n; i++){
		cin>>pres[i];
	}
	for(int i = 0; i < n; i++){
		arr[tin[i]] = ability[i];
	}
	build(1, 0, n - 1);
	for(int i = 0; i < n; i++){
		modint tmp = query(1, 0, n - 1, tin[i], tout[i], ability[i] + pres[i]);
		tmp /= sz[i];
		dp[i] = tmp;
	}
	dfs2(root);
	while(m--){
		int u;
		cin>>u;
		u--;
		cout<<dp[u]<<nl;
	}

}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Solve();
}
