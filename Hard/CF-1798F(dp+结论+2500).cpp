
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)



//from any 2n−1 integers, you can choose n with a sum divisible by n (Erdős–Ginzburg–Ziv theorem)
const int N = 210;
int n, m;
vector<pair<int, int>> a;
vector<int> b;
vector<int> ans[N]; 
bool dp[N][N][N]; int last[N][N][N];
void solve() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b.push_back(x);
    }

    for(int i = 0; i < m; i++) {
        int x;
        cin >> x;
        a.push_back({x, i});
    }

    sort(a.begin(), a.end());
    memset(dp, false, sizeof dp);
    memset(last, -1, sizeof last);
    
    for(int x = 0; x < m - 1; x++) {
        int s = a[x].first, idx = a[x].second;

        dp[0][0][0] = true;
        for(int i = 1; i <= s * 2 - 1; i++) {
            int v = (b[i - 1]) % s;
            for(int j = 0; j <= s; j++) {
                for(int k = 0; k < s; k++) {
                    if(dp[i - 1][j][k]) {
                        dp[i][j + 1][(k + v) % s] = true;
                        last[i][j + 1][(k + v) % s] = i;
                        dp[i][j][k] = true;
                        last[i][j][k] = 0;
                    }
                }
            }
        }

        int i = s * 2 - 1, j = s, k = 0;
        set<int> se;
        while(i > 0) {
            if(last[i][j][k] == 0) {
                i--;
            } else {
                int v = last[i][j][k] - 1;
                ans[idx].push_back(b[v]);
                i--;
                j--;
                k -= (b[v] % s);
                k += s;
                k %= s;
                se.insert(v);
            }
        }

        vector<int> c;
        for(int i = 0; i < b.size(); i++) {
            if(se.find(i) == se.end()) {
                c.push_back(b[i]);
            }
        }
        b = c;

        for(int i = 0; i <= s * 2 - 1; i++) {
            for(int j = 0; j <= s + 1; j++) {
                for(int k = 0; k <= s + 1; k++) {
                    dp[i][j][k] = false;
                    last[i][j][k] = -1;
                }
            }
        }
    }

    int sum = 0;
    for(int x : b) {
        sum += x;
        ans[a.back().second].push_back(x);
        sum %= (a.back().first);
    }

    cout << (a.back().first - sum) + a.back().first << endl;
    ans[a.back().second].push_back((a.back().first - sum) + a.back().first);
    for(int i = 0; i < m; i++) {
        for(int x : ans[i]) {
            cout << x << " ";
        }
        cout << endl;
    }
}

int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
