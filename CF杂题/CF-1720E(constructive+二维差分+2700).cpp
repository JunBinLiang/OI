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

const int N = 502;
const int INF = 1e9;
int f1[N * N], f2[N * N], g1[N * N], g2[N * N];
int dp[N][N];
int n, k;
int a[N][N];

ll query(ll sums[N][N], int r1, int c1, int r2, int c2) {
    ll a = sums[r2][c2];
    ll b = 0;
    ll c = 0;
    ll d = 0;
    if(c1 - 1 >= 0) b = sums[r2][c1 - 1];
    if(r1 - 1 >= 0) c = sums[r1 - 1][c2];
    if(r1 - 1 >= 0 && c1 - 1 >= 0) d = sums[r1 - 1][c1 - 1];
    return a - b - c + d;
}

void init(ll sums[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i == 0 && j == 0) {
                continue;
            }
            else if(i == 0) {
                sums[i][j] += sums[i][j - 1];
            } else if(j == 0) {
                sums[i][j] += sums[i - 1][j];
            } else {
                sums[i][j] += sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1];
            }
        } 
    }
}

void solve() {
    cin >> n >> k;
    set<int> s;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
            s.insert(a[i][j]);
        }
    }

    if(s.size() <= k) {
        cout << k - s.size() << endl;
        return;
    }
    if(k == 1) {
        cout << 1 << endl;
        return;
    }


    for(int i = 0; i <= n * n; i++) {
        f1[i] = f2[i] = -1;
        g1[i] = g2[i] = INF;
    }


    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int v = a[i][j];
            g1[v] = min(g1[v], i);
            g2[v] = min(g2[v], j);
            f1[v] = max(f1[v], i);
            f2[v] = max(f2[v], j);
        }
    }

    int tot = s.size();
    for(int le = 1; le <= n; le++) {
        memset(dp, 0, sizeof dp);
        for(int i = 1; i <= n * n; i++) {
            if(f1[i] == -1) continue;
            int r1 = g1[i], c1 = g2[i];
            int r2 = f1[i], c2 = f2[i];
            
            int tr = max(0, r2 - le + 1);
            int tc = max(0, c2 - le + 1);
            int dr = min(r1, n - le);
            int dc = min(c1, n - le);
            
            
            if(tr <= dr && tc <= dc) {
                dp[tr][tc]++;
                dp[dr + 1][tc]--;
                dp[dr + 1][dc + 1]++;
               dp[tr][dc + 1]--;
            }
        }

        
        /*if(le == 2) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    cout << dp[i][j] << " ";
                } cout << endl;
            }
            cout << endl << endl;
        }*/
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i - 1 >= 0) dp[i][j] += dp[i - 1][j];
                if(j - 1 >= 0) dp[i][j] += dp[i][j - 1];
                if(i - 1 >= 0 && j - 1 >= 0) dp[i][j] -= dp[i - 1][j - 1];
                
                if((tot - dp[i][j] == k || tot - dp[i][j] == k - 1) && i <= n - le && j <= n - le) {
                    cout << 1 << endl;
                    return;
                }
            }
        }  
        
    }
    
    cout << 2 << endl;
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
