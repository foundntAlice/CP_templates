#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
//using namespace __gnu_pbds;
//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define nl '\n'
#define fi first
#define se second

typedef long long ll;

const int mod = 1e6 + 3;

long long multiply_modular (long long x, long long y){
	long long tmp = x;
	long long res = 0;
	while(y > 0) {
		if(y % 2) {
			res += tmp;
			res %= mod;
		}
		tmp = (2 * tmp) % mod;
		y /= 2;
	}
	return res;
}
vector<vector<long long>> matrix_multiply(vector<vector<long long>> a, vector<vector<long long>> b){
	int n = a.size();
	int m = b[0].size();
	vector<vector<long long>> res(n, vector<long long>(m));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			long long sum = 0;
			for(int k = 0; k < b.size(); k++){
				sum += multiply_modular(a[i][k], b[k][j]);
				sum %= mod;
			}
			res[i][j] = sum;
		}
	}
	return res;
}
vector<vector<long long>> matrix_exp(vector<vector<long long>> C, long long n){
	vector<vector<long long>> res(C.size(), vector<long long> (C[0].size()));
	for(int i = 0; i < res.size(); i++)
		res[i][i] = 1;
	for(;n; n /= 2, C = matrix_multiply(C, C)){
		if(n % 2){
			res = matrix_multiply(res, C);
		}
	}
	return res;
}

void polar_night(){
	int n, s, e, t;
	cin>>n>>s>>e>>t;
	vector<vector<int>> adj(n, vector<int> (n));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			char c;
			cin>>c;
			adj[i][j] = c - '0';
		}
	}
	vector<vector<long long>> C(n * 5, vector<long long> (n * 5));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(adj[i][j] == 0) continue;
			int left = 5 - adj[i][j];
			C[i * 5 + 4][(j + 1) * 5 - adj[i][j]] = 1;
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 4; j++)
			C[i * 5 + j][i * 5 + j + 1] = 1;
	}
	vector<vector<long long>> res = matrix_exp(C, t);
	s--; e--;
	cout<<res[s * 5 + 4][e * 5 + 4]<<nl;

}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	polar_night();
}
