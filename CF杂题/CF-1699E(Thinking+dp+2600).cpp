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

   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

unsigned long long seed = 131;
unsigned long long rands() { return seed = (seed << 15) + (seed << 8 ) + (seed >> 3);}

void debug() {
    cout << "________________" << endl;
}


const int N = 1e6 + 10;
const int M = 5e6 + 10, INF = 1e9;
bool is[M];
int dp[M], nums[M];
int n, m;
void solve() {
    scanf("%d%d", &n, &m); 
    int l = INF, r = -1;
    for(int i = 0; i <= m; i++) dp[i] = i, is[i] = false, nums[i] = 0;
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        is[x] = true;
        nums[x] = 1;
        l = min(l, (x)); 
        r = max(r, (x));
    }

    int res = r - l;
    for(int i = m; i >= 1; i--) {
        ll x = i;
        if(x * x > m) continue;
        for(int j = i * i; j <= m; j += i) {
            if(is[j]) nums[dp[j]]--;
            if(dp[j / i] >= i) dp[j] = min(dp[j], dp[j / i]);
            if(is[j]) nums[dp[j]]++;
        }
        while(nums[r] == 0) r--;
        res = min(res, r - min(l, i));
    }
    printf("%d\n", res);
} 

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

