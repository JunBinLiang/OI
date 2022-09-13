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

const int N = 100010;
int n, m;
int s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N];
int Nxt[N], Pre[N];

ll tot = 0;
ll ans[N];

int get(int x) {
    static unordered_map<int, int> f;
    if(f.find(x) == f.end()) f[x] = ++m;
    return f[x];
}

void get_sa()
{
    for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        int num = 0;
        for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k;
        for (int i = 1; i <= m; i ++ ) c[i] = 0;
        for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
        for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
        for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i ++ )
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
        if (num == n) break;
        m = num;
    }
}

void get_height()
{
    for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i ++ )
    {
        if (rk[i] == 1) continue;
        if (k) k -- ;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
        height[rk[i]] = k;
    }
}

void del(int k) {
    int pre = Pre[k], nxt = Nxt[k];
    tot -= ((n - sa[k] + 1) - height[k]);
    tot -= ((n - sa[nxt] + 1) - height[nxt]);
    height[nxt] = min(height[nxt], height[k]);
    tot += ((n - sa[nxt] + 1) - height[nxt]);
    Nxt[pre] = nxt;
    Pre[nxt] = pre;
}

int main() {
    scanf("%d", &n);
    for(int i = n; i > 0; i--) {
        scanf("%d", &s[i]);
        s[i] = get(s[i]);
    }
    get_sa();
    get_height();
    
    for(int i = 1; i <= n; i++) {
        tot += ((n - sa[i] + 1) - height[i]);
        Nxt[i] = i + 1, Pre[i] = i - 1;
    }
    
    Nxt[0] = 1;
    Pre[n + 1] = n;
    height[0] = height[n + 1] = 0;
    
    for(int i = 1; i <= n; i++) {
        ans[i] = tot;
        del(rk[i]);
    }
    
    for(int i = n; i > 0; i--) printf("%lld\n", ans[i]);
    
    return 0;
}
