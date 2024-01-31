#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

#define nl '\n'
#define fi first
#define se second

typedef long long ll;

const int N = 1e5 + 5;

const int block_size = 320;
const int sizee = 320;
int arr[N];
deque<int> d[N];
vector<int> bucket(sizee), cnt(102401);

void add(int idx){
	int x = arr[idx];
	int cur = 0;
	if(!d[x].empty()){
		cur = d[x].back() - d[x].front();
		cnt[cur]--;
		bucket[cur / sizee]--;
	}
	if(idx < d[x].front()) d[x].push_front(idx);
	else d[x].push_back(idx);
	cur = d[x].back() - d[x].front();
	cnt[cur]++;
	bucket[cur / sizee]++;
}
void remove(int idx){
	int x = arr[idx];
	int cur = d[x].back() - d[x].front();
	cnt[cur]--;
	bucket[cur / sizee]--;
	if(idx == d[x].front()) d[x].pop_front();
	else d[x].pop_back();
	if(!d[x].empty()){
		cur = d[x].back() - d[x].front();
		cnt[cur]++;
		bucket[cur / sizee]++;
	}
}
struct Query {
    int l, r, idx;
    bool operator<(Query other) const {
        return make_pair(l / block_size, r) < make_pair(other.l / block_size, other.r);
    }
};
vector<int> mo_s_algorithm(vector<Query> queries) {
    vector<int> answers(queries.size());
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
        for(int i = sizee - 1; i >= 0; i--){
        	bool out = false;
        	if(bucket[i]){
        		for(int j = sizee - 1; j >= 0; j--){
        			if(cnt[i * sizee + j]){
        				answers[q.idx] = i * sizee + j;
        				out = true;
        				break;
        			}
        		}
        	}
        	if(out) break;
        }
    }
    return answers;
}
void Solve(){
	int n, q, k;
	cin>>n>>k;
	for(int i = 0; i < n; i++)
		cin>>arr[i];
	
	cin>>q;
	vector<Query> v(q);
	for(int i = 0; i < q; i++){
		cin>>v[i].l>>v[i].r;
		v[i].l--; v[i].r--;
		v[i].idx = i;
	}
	vector<int> res = mo_s_algorithm(v);
	for(auto x: res){
		cout<<x<<nl;
	}

}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Solve();
}
