#pragma GCC optimize("O3")
#include <bits/stdc++.h>

//https://www.acmicpc.net/problem/17731

using namespace std;

#define nl '\n'
#define fi first
#define se second

typedef long long ll;

const int N = 1e5 + 5;

int block_size;

int cnt[N], id[N], arr[N];
ll t[2 * N];

void modify(int p, ll value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

ll query(int l, int r) {  // sum on interval [l, r)
  ll res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(res, t[--r]);
  }
  return res;
}
void add(int idx){
    int x = arr[idx];
    cnt[x]++;
    modify(x, (ll)cnt[x] * id[x]);
}
void remove(int idx){
    int x = arr[idx];
    cnt[x]--;
    modify(x, (ll)cnt[x] * id[x]);
}
struct Query {
    int l, r, idx;
    bool operator<(Query other) const {
        return make_pair(l / block_size, r) < make_pair(other.l / block_size, other.r);
    }
};
vector<ll> mo_s_algorithm(vector<Query> queries) {
    vector<ll> answers(queries.size());
    sort(queries.begin(), queries.end());

    // TODO: initialize data structure

    int cur_l = 0;
    int cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for(Query q : queries){
        while (cur_l > q.l) add(--cur_l);
        while (cur_r < q.r) add(++cur_r); 
        while (cur_l < q.l) remove(cur_l++);
        while (cur_r > q.r) remove(cur_r--); 
        answers[q.idx] = query(0, N - 1);
    }
    return answers;
}
void Solve(){
	memset(cnt, 0, sizeof(cnt));
	memset(t, 0, sizeof(t));
	int n, q;
	cin>>n>>q;
	vector<int> tmp(n);
	map<int, int> myMap;
	int cur = 1;
	for(int i = 0; i < n; i++){
		cin>>tmp[i];
		if(!myMap.count(tmp[i])){
			myMap[tmp[i]] = cur++;
		}
	}
	for(int i = 0; i < n; i++){
		arr[i] = myMap[tmp[i]];
		id[arr[i]] = tmp[i];
	}
	block_size = sqrt(n) + 1;

	vector<Query> v(q);
	for(int i = 0; i < q; i++){
		cin>>v[i].l>>v[i].r;
		v[i].l--; v[i].r--;
		v[i].idx = i;
	}
	vector<ll> res = mo_s_algorithm(v);
	for(auto x: res){
		cout<<x<<nl;
	}

}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Solve();
}
