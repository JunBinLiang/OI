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
const int N = 2005;
int c[N];
void mul(vector<int>& a, vector<int>& b) {
    for(int i = 0; i < k; i++) c[i] = 0;
    
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b.size(); j++) {
            int ith = (i + j);
            if(ith >= k) ith -= k;
            int x = (a[i] + 0ll) * (b[j]) % mod;
            c[ith] += x;
            if(c[ith] >= mod) c[ith] -= mod;
        }
    }
    //copy back
    for(int i = 0; i < a.size(); i++) a[i] = c[i];
}

void solve() {
    cin >> n >> k >> mod;
    ll nn = n;
    ll tot = fpow(k, n), res = 0;

    vector<int> a(k, 1);
    a[0] = 0;
    vector<int> b(k, 0);
    b[0] = 1;
    
    if(k % 2 == 1) {
        while(nn) {
            if (nn & 1) mul(b, a);// res = res * a
            mul(a, a);  // a = a * a
            nn >>= 1;
        }

        for(int s = 0; s < k; s ++) {
            for(int d = 0; d < k; d++) {
                int v = s + ((n % k * d) % k);
                v %= k;
                if(v == (d * 2) % k) {
                    res += b[s];
                    res %= mod;
                }
            }
        }

    } else {
        a[0] = 0;
        a[k / 2] = 0;
        
        tot *= fpow(2, mod - 2);
        tot %= mod;
        
       // cout << tot << endl;

        while(nn) {
            if (nn & 1) mul(b, a);// res = res * a
            mul(a, a);  // a = a * a
            nn >>= 1;
        }   
        
        for(int x1 = 0; x1 < k; x1++) {
            for(int x2 = x1 + 1; x2 < k; x2++) {
                if((2 * x1 % k) == (2 * x2 % k)) {
                    int S = 2 * x1 % k;
                    int s1 = S - (n % k * x1 % k);
                    if(s1 < 0) s1 += k;
                    res += b[s1];
                    res %= mod;
                }
            }
        }
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
