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

const int N = 3e5 + 10, M = 50;
const int INF = 1e9;
int a[N], b[M];
bool inv[M][M];
int n, m;
int res = INF;
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }

    for(int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    memset(inv, false, sizeof inv);
    for(int i = 0; i < n - 1; i++) {
        int u = a[i], v = a[i + 1];//invalid pair
        inv[u][v] = inv[v][u] = true;
    }

    int mid = m / 2;
    int o = m - mid;
    
    

    //left
    vector<int> dp(1 << mid, INF);
    for(int st = 0; st < (1 << mid); st++) {
        int cost = 0;
        for(int j = 0; j < mid; j++) {
            if(st & (1 << j)) {
                cost += b[j];
            }
        }

        bool bad = false;
        for(int x = 0; x < mid && !bad; x++) {
            for(int y = x; y < mid; y++) {
                if(inv[x][y]) {
                    if(((st & (1 << x)) == 0) && ((st & (1 << y)) == 0)) {
                        bad = true;
                        break;
                    }
                }
            }
        }
        
        if(a[0] < mid) {
            if((st & (1 << a[0])) == 0) bad = true;
        }
        
        if(a[n - 1] < mid) {
            if((st & (1 << a[n - 1])) == 0) bad = true;
        }
        
        if(!bad) {
            dp[st] = cost;
        }
    }

    //bit dp
    for(int i = dp.size() - 1; i >= 0; i--) {
        for(int j = 0; j < mid; j++) {
            if(!(i & (1 << j))) {
                dp[i] = min(dp[i], dp[i | (1 << j)]);
            }
        }
    }
    
    //other side
    for(int st = 0; st < (1 << o); st++) {
        int cost = 0;
        for(int i = 0; i < o; i++) {
            if(st & (1 << i)) {
                cost += b[i + mid];
            }
        }
        
        bool bad = false;
        for(int x = mid; x < m && !bad; x++) {
            for(int y = x; y < m; y++) {
                if(inv[x][y]) {
                    int t1 = x - mid, t2 = y - mid;
                    if(((st & (1 << t1)) == 0) && ((st & (1 << t2)) == 0)) {
                        bad = true;
                        break;
                    }
                }
            }
        }
        
        if(a[0] >= mid) {
            if((st & (1 << (a[0] - mid))) == 0) bad = true;
        }
        
        if(a[n - 1] >= mid) {
            if((st & (1 << (a[n - 1] - mid))) == 0) bad = true;
        }
        
        if(bad) continue;
        
        int need = 0;
        for(int i = 0; i < mid; i++) {
            for(int j = mid; j < m; j++) {
                if(!inv[i][j]) continue;
                if((st & (1 << (j - mid))) == 0) {
                    need = need | (1 << i);
                }
            }
        }
        
        res = min(res, cost + dp[need]);
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
