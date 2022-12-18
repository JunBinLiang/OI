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


const int mod = 1e9 + 7;
const int N = 1e6 + 10;
bool is[N];
vector<int> g[N];
int m;
int f[N][21];
void init() {
    //f(r, x) = f(r - 1, p1) * f(r - 1, p2) ...
    memset(is, false, sizeof is);
    for(int i = 2; i < N; i++) {
        if(is[i]) continue;
        for(int j = i; j < N; j += i) {
            is[j] = true;
            g[j].pb(i);
        }
    }
    
    
    int p[22];
    for(int i = 0; i < 21; i++) {
        if(!i) f[0][i] = 1;
        else f[0][i] = 2;
        p[i] = f[0][i];
        if(i) p[i] += p[i - 1], p[i] %= mod;
    }

    for(int r = 1; r < N; r++) {
        f[r][0] = 1;
        for(int i = 1; i < 21; i++) {
            f[r][i] = p[i];
        }
        
        for(int i = 0; i < 21; i++) {
            p[i] = f[r][i];
            if(i) p[i] += p[i - 1], p[i] %= mod;
        }
    }
}

void solve() {
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int r, n;
        ll res = 1;
        scanf("%d%d", &r, &n);
        
        int v = n;
        for(int& j : g[v]) {
            if(n < j) break;
            if(n % j == 0) {
                int cnt = 0;
                while(n % j == 0) n /= j, cnt ++;
                res *= f[r][cnt];
                res %= mod;
            }
        }

        if(n > 1) {
            res *= f[r][1];
            res %= mod;
        }
        
        printf("%lld\n", res);
    }
}

int main() {
	// your code goes here
	init();
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
