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
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

char next(int c, int m) {
  return min(c + 'a', min((c + 1) % m + 'a', (c - 1 + m) % m + 'a'));
}

const int N = 510;
string dp[N];

void solve() {
  int n, m;
  string s;
  cin >> n >> m >> s;

  for(int i = 0; i < n; i++) {
    dp[i] = (char)('z' + 1);
  }

  dp[0] = next(s[0] - 'a', m);
  for(int i = 1; i < n; i++) {
    char c = next(s[i] - 'a', m);
    dp[i] = min(dp[i], dp[i - 1] + c);
    dp[i] = min(dp[i], dp[i - 1].substr(0, i - 1) + s[i] + dp[i - 1].back());
    if(i - 2 >= 0)  {
      dp[i] = min(dp[i], dp[i - 2] + c + s[i - 1]);
      dp[i] = min(dp[i], dp[i - 2].substr(0, i - 2) + s[i] + dp[i - 2].back() + s[i - 1]);
    }
    
    if(i == 1) {
        string emp = "";
        dp[i] = min(dp[i], emp + c + s[i - 1]);
    }
  }
  
  cout << dp[n - 1] << endl;
}

    

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
