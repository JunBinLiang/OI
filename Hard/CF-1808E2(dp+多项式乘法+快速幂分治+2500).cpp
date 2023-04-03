#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


const int N = 105;
ll n;
int k, mod;


ll fpow(ll x, ll y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return res;
}  

/*
int dfs(int i, int sum) {
    if(i >= n) {
       if(sum == all) return 1;
       else return 0;
    }
    if(dp[i][sum] != -1) {
        return dp[i][sum];
    }
 
    int res = 0;
    for(int x = 0; x < k; x++) {
        int v = all - x;
        if(v < 0) v += k;
        if(v != x) {
            res += dfs(i + 1, (sum + x) % k);
            res %= mod;
        }
    }
 
    return dp[i][sum] = res;
}
*/


void mul(vector<int>& a, vector<int>& b) {
    vector<int> c(k);
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b.size(); j++) {
            int ith = (i + j) % k;
            ll x = (a[i] + 0ll) * (b[j] + 0ll);
            x %= mod;
            c[ith] += x;
            c[ith] %= mod;
        }
    }
    //copy back
    for(int i = 0; i < a.size(); i++) a[i] = c[i];
}

void solve() {
    cin >> n >> k >> mod;
    ll tot = fpow(k, n);
    ll res = 0;

    for(int S = 0; S < k; S++) {
        vector<int> a(k, 1);
        vector<int> b(k, 0);
        b[0] = 1;
        for(int i = 0; i < k; i++) {
            if((S - i + k) % k == i) {
                a[i] = 0; //ban digit
            }
        }

        //做多项式乘法, 时间关系, 不需要fft
        //do linear multiplication, due to low complexity, no fft need
        ll nn = n;
        while(nn) {
            if (nn & 1) mul(b, a);// res = res * a
            mul(a, a);  // a = a * a
            nn >>= 1;
        }

        res += b[S]; 
        res %= mod;
        if(res < 0) res += mod;
    }
    
    tot -= res;
    if(tot < 0) tot += mod;
    cout << tot << endl;
}

int main()
{
    solve();
    return 0;
}
