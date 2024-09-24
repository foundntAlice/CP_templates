// FenwickTree template is from cp-algorithms.com
#include<bits/stdc++.h>

//https://www.acmicpc.net/problem/3770
using namespace std;

#define nl '\n'
#define fi first
#define se second

typedef long long ll;

const int N = 1e3 + 5;

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }
    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
void Solve(int t){
	int n, m, k;
	cin>>n>>m>>k;
	FenwickTree fw(N);
	vector<pair<int, int>> v(k);
	for(int i = 0; i < k; i++){
		cin>>v[i].fi>>v[i].se;
	}
	sort(v.begin(), v.end());
	ll res = 0;
	for(int i = k - 1; i >= 0; i--){
		int x = v[i].se;
		res += fw.sum(x - 1);
		fw.add(x, 1);
	}

	cout<<"Test case "<<t<<": "<<res<<nl;

}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int tests;
	cin>>tests;
	for(int i = 1; i <= tests; i++)
		Solve(i);

}
