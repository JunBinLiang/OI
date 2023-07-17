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
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define JBFOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 

const int MOD = 1e9 + 7;
void solve() {
    vector<int> dp(26);
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i++) {
        int sum = 0;
        for(int x : dp) {
            sum += x;
            sum %= MOD;
        }
        
        dp[s[i] - 'a'] = 1 + sum; 
    }
    
    int res = 0;
    for(int x : dp) {
        res += x;
        res %= MOD;
    }
    cout << res << endl;
}

int main()
{
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
