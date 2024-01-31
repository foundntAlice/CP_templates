#include<bits/stdc++.h>

//https://www.acmicpc.net/problem/13977

using namespace std;

#define nl '\n'
#define fi first
#define se second

typedef long long ll;

const int m = 1e9 + 7;
const int N = 4e6 + 5;

ll inverse(ll a) {
  return a <= 1 ? a : m - (ll)(m / a) * inverse(m % a) % m;
}
void polar_night(){
	vector<ll> fact(N);
	fact[0] = 1;
	for(int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % m;

	int t;
	cin>>t;
	while(t--){
		ll n, k;
		cin>>n>>k;
		ll res = fact[n] * inverse(fact[k] * fact[n - k] % m) % m; //nCk
		cout<<res<<nl;
	}

}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	polar_night();
}
