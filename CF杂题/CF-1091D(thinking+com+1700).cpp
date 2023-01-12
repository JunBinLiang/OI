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
 

//4 : 45  5:38

const int N = 1e6 + 10;
int n;
ll res = 0;
const int mod = 998244353;

ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

void solve() {
    cin >> n;
    //next permutation algorithm
    //from end, find the first a[i] < a[i + 1]
    //form end, find the last j such a[j] > a[i]
    //swap a[i], a[j]
    //reverse a[j : n]


    //how many subarray equal to (1 + n) * n / 2 from current array to next?
    //find index i, (i + 1) subarrays

    ll f[N];
    f[0] = f[1] = 1;
    for(int i = 2; i < N; i++) {
        f[i] = f[i - 1] * i;
        f[i] %= mod;
    }
    
    

    for(int i = 2; i <= n; i++) {
        ll x = f[n] * modInverse(f[i], mod);
        x %= mod;
        x *= (i - 1);
        x %= mod;
        x *= (n - i + 1);
        x %= mod;
        res += x;
        res %= mod;
    }
    res++;
    res %= mod;
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
