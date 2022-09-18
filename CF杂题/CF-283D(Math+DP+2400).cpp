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

const int N = 5050;
ll a[N];
int cnt[N];
int dp[N];

bool ok(int l, int r) {
    if(a[l] % a[r] != 0) {
        return false;
    }
    if(l + 1 == r) {
        if(cnt[r] == 0 && a[l] % a[r] == 0) {
            return true;
        }
        return cnt[r] == cnt[l] + 1;
    }

    if(cnt[r] == 0) {
        if(a[l] != 1) return true;
        if(a[r] == 1) return true;
        return false;
    }

    if(cnt[r] == cnt[l] + (r - l)) {
        return true;
    }

    if(1 <= cnt[r] && cnt[r] <= (r - l - 1)) {
        return true;
    }

    return false;
}

int main() {
    int n;
    cin >> n;
    int res = 0;
    for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for(int i = 0; i < n; i++) {
        ll val = a[i];
        cnt[i] = 0;
        while(val % 2 == 0) val /= 2, cnt[i]++;
        a[i] = val;
    }

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for(int i = 1; i < n; i++) {
        dp[i] = 1;
        for(int j = i - 1; j >= 0; j--) {
            if(ok(j, i)) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        res = max(res, dp[i]);
    }
    
    /*for(int i = 0; i < n; i++) cout << dp[i] << " ";
    cout << endl << endl;*/

    cout << n - res << endl;
    return 0;
}
