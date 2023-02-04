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

const int N = 1e6 + 10, mod = 1e9 + 7;
int a[N]; 
ll f[N], sums[N];
vector<int> g[N];
int n;

void dfs(int pa, int root) {
    sums[root] = a[root];
    for(int& nxt : g[root]) {
        if(nxt != pa) {
            dfs(root, nxt);
            sums[root] += sums[nxt];
        }
    }
}  

void solve() {
    memset(f, 0, sizeof f);

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 2; i <= n; i++) {
        int u;
        scanf("%d", &u);
        g[i].push_back(u);
        g[u].push_back(i);
    }

    dfs(0, 1);

    for(int i = 1; i <= n; i++) {
        ll g = __gcd(sums[1], sums[i]);
        ll com = (sums[1] / g);
        if(com <= n) {
            f[(int)(com)]++;
        }
    }

    for(int i = n; i >= 1; i--) {
        for(int j = i * 2; j <= n; j += i) {
            f[j] += f[i];
            f[j] %= mod;
        }
    }

    for(int i = 1; i <= n; i++) {
        if(f[i] == i) {
            f[i] = 1;
        } else {
            f[i] = 0;
        }
    }

    for(int i = n; i >= 1; i--) {
        if(!f[i]) continue;
        for(int j = i * 2; j <= n; j += i) {
            f[i] += f[j];
            f[i] %= mod;
        }
    }
    cout << f[1] << endl;
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
