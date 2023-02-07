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

const int N = 110;
const int mod = 1e9 + 7;
ll C[N][N];

void init() {
    memset(C, 0, sizeof C);
    C[0][0] = 1;
    for(int i = 1; i < N; i++) {
        C[i][0]=1;
        for(int j = 1; j <= i;j++) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
        }
    }
}

void solve() {
    int n, i, j, x, y;
    cin >> n >> i >> j >> x >> y;
    i--; j--;
    ll res = 0;
    int gap = j - i - 1;

    if(x == n) {
        res = C[n - y - 1][gap] * C[y - 1][n - j - 1];
        res %= mod;
        if(i == 0) res = 0;
        
        cout << res << endl;
        return;
    }
    if(y == n) {
        res = C[n - x - 1][gap] * C[x - 1][i];
        res %= mod;
        if(j == n - 1) res = 0;
        cout << res << endl;
        return;
    }

    //pivot point
    for(int p = 1; p < n - 1; p++) {
        if(p < i) {
            if(x < y) continue;
            res += ((C[n - x - 1][i - p - 1] * C[x - y - 1][gap] % mod) * C[y - 1][n - j - 1]);
        } else if(p > i && p < j) {
            int g1 = p - i - 1;
            int g2 = j - p - 1;
            ll add = 1;
            if(x < y) {
                int still = max(0, n - y - 1 - g2);
                add *= C[n - y - 1][g2];
                add %= mod;
                if(g1 >= still) {
                    add *= C[y - x - 1][g1 - still];
                    add %= mod;
                } else {
                    add = 0;
                }
                add *= C[x - 1][i];
                add %= mod;
                
                /*cout << "yes  " << p + 1 << "   " << g1  << "  " << g2 << "  " << add << endl;
                cout << C[n - y - 1][g2] << "  " << C[n - x - 2 - g2][g1] << "  " << C[x - 1][i] << endl;
                cout << n - x - 2 - g2  << endl << endl;
                cout << endl;*/
            } else {
                int still = max(0, n - x - 1 - g1);
                add *= C[n - x - 1][g1];
                add %= mod;
                if(g2 >= still) {
                    add *= C[x - y - 1][g2 - still];
                    add %= mod;
                } else {
                    add = 0;
                }
                add *= C[y - 1][n - j - 1];
                add %= mod;
            }
            
            res += add;

        } else if(p > j) {
            if(x > y) continue;
            res += ((C[n - y - 1][p - j - 1] * C[y - x - 1][gap] % mod) * C[x - 1][i]);
        }
        res %= mod;
    }
    cout << res << endl;
} 


int main() {
	// your code goes here
    init();
	int t = 1;
	cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}  
