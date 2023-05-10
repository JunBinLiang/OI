
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

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 3e5 + 5;
int a[N], p[N];
ll dp[N], is[N];
int n;

int get(int L, int R) {
    if(L > R) return 0;
    if(L == 0) return p[R];
    return p[R] - p[L - 1];
}

void solve() {
    memset(p, 0, sizeof p);
    memset(dp, 0, sizeof dp);
    memset(is, false, sizeof is);

    cin >> n;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        p[a[i]] = 1;
        is[a[i]] = true;
    }
    for(int i = 1; i < N; i++) p[i] += p[i - 1];

    for(int i = 3e5; i >= 1; i--) {
        dp[i] = 0;
        int points = 0;
        ll sub = 0;
        for(int j = i; j <= 3e5; j += i) {
            if(is[j]) {
                ll sum = get(i, j - 1);
                dp[i] += (sum * points - sub - points);
                sub += get(i, j - 1);
                points++;
            }
        }

        for(int j = i + i; j <= 3e5; j += i) {
            dp[i] -= dp[j];
        }
    }

    cout << dp[1] << endl;
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
