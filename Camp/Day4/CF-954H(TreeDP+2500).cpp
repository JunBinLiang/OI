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

int n;
const int N = 5005, mod = 1e9 + 7;
int a[N];
int f[N][N * 2];
int ans[N * 2];
ll p[N];
int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;

    return d;
}

int mul(int x, int y) {
    ll xx = x;
    ll yy = y;
    ll res = xx * yy;
    return (int)((xx * yy) % mod);
}

void solve() {
    scanf("%d", &n);
    n--;
    p[0] = 1;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(i)p[i] = ((ll)(p[i - 1]) * (ll)(a[i])) % mod;
        else p[i] = a[i];
    }
    
    memset(ans, 0, sizeof ans);
    memset(f, 0, sizeof f);
    
    for(int i = 0; i <= n; i++) f[i][0] = 1;
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 1; j <= 2 * n; j++) {
            if(j > n - i) break;
            f[i][j] = ((ll)(f[i + 1][j - 1]) * (ll)((a[i])) % mod); 
            f[i][j] %= mod;
            if(i) {
                ans[j] += ((ll)(f[i][j])* (ll)(p[i - 1]) % mod);
            } else {
                ans[j] += (f[i][j]) * 1;
            }
            ans[j] %= mod;
        }
    }
    
    int x, y;
    exgcd(2, mod, x, y);
    ll rev = (x % mod + mod) % mod;
    
    for(int i = 1; i <= n; i++) f[0][i] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 2 * n; j >= 1; j--) {
            f[i][j] = f[i - 1][j - 1];
            if(j - 2 >= 0)  {
                f[i][j] += mul(f[i][j - 2], a[i - 1] - 1);
                f[i][j] %= mod;
            }
            
            int x = mul(p[i - 1], f[i][j]);
            ans[j] += x;
            ans[j] %= mod;
        }
        
    }

    for(int i = 1; i <= 2 * n; i++) {
        printf("%lld ", ((ll)(ans[i]) * (rev)) % mod);
    }
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
