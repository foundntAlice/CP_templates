#include <ext/pb_ds/assoc_container.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds; 

#define nl '\n'
#define fi first
#define se second

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //replace less by less_equal if we want ordered_multiset

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n, k;
	cin>>n>>k;
	ordered_set<int> s;
	for(int i = 1; i <= n; i++)
		s.insert(i);
	vector<int> res;
	int cur = 0;
	while(!s.empty()){
		cur += k - 1;
		cur %= n;
		int x = *s.find_by_order(cur);
		res.push_back(x);
		s.erase(x);
		n--;
	}
	cout<<"<";
	for(int i = 0; i < res.size() - 1; i++)
		cout<<res[i]<<", ";
	cout<<res[res.size() - 1]<<">"<<nl;
}
