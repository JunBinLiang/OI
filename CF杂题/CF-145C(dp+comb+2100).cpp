#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
 
 
using namespace std;  
using ll = long long;
#define pb push_back
 
//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");


bool islucky(int num) {
    while(num) {
        int d = num % 10;
        if(d != 4 && d != 7) {
            return false;
        }
        num /= 10;
    }
    return true;
}

int n, k;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int a[N];
ll f[N];
ll res = 0;
int remain;
vector<int> b, c;
ll dp[1110][1110];

ll fpow(ll x, int y, int mod){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) %mod;
		y >>= 1;
	}
	return res;
}  

ll C(int n,int m) {
    return f[n] * fpow(f[n-m], mod - 2, mod) % mod * fpow (f[m], mod - 2, mod) % mod;
}


void solve() {
    scanf("%d%d", &n, &k);
    f[0] = f[1] = 1;
    for(int i = 2; i < N; i++) {
        f[i] = f[i - 1] * i;
        f[i] %= mod;
    }

    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(islucky(a[i])) {
            b.push_back(a[i]);
        }
    }

    sort(b.begin(), b.end());
    for(int i = 0; i < b.size(); i++) {
        int j = i;
        int cnt = 0;
        while(j < b.size() && b[i] == b[j]) {
            cnt++;
            j++;
        }
        c.push_back(cnt);
        i = j - 1;
    }
    
    //for(int x : c) cout << x << " ";
    //cout << endl;


    remain = n - b.size();
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for(int i = 1; i <= c.size(); i++) {
        int cnt = c[i - 1];
        for(int j = 0; j <= c.size(); j++) {
            dp[i][j] += dp[i - 1][j];
            if(j) {
                dp[i][j] += (dp[i - 1][j - 1] * cnt);
            }
            dp[i][j] %= mod;
        }
    }
    
    
    
    //for(int i = 0; i <= c.size(); i++) cout << dp[i] << " ";
    //cout << endl;
    
    for(int i = 0; i <= c.size(); i++) {
        if(i > k) break;
        int need = k - i;
        if(need <= remain) {
            ll w = C(remain, need);
            res += w * dp[c.size()][i];
            res %= mod;
        }
    }

    cout << res << endl;


}

int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
