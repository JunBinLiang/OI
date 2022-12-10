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

const int N = 2e5 + 10, mod = 1e9 + 7;
int p[N], nxt[N];
ll po[N];
ll h1[N][2];
int sizes[N];
int base = 233;
int pre(int l, int r) {
    if(!l) return p[r];
    return p[r] - p[l - 1];
}

ll get(int l, int r, int i) {
    if(l == 0) {
        return h1[r][i];
    }
    int sz = sizes[r];
    if(l > 0) sz -= sizes[l - 1];
    return (h1[r][i] - (h1[l - 1][i] * po[sz] % mod) + mod) % mod;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    
    for(int i = 0; i < n; i++) {
        p[i] = (s[i] - '0');
        if(i) p[i] += p[i - 1];
    }

    po[0] = 1;
    for(int i = 1; i <= n; i++) {
        po[i] = po[i - 1] * base;
        po[i] %= mod;
    }

    ll h = 0;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        int d = s[i] - '0';
        if(!d) {
            if(i % 2 == 0) {
                h = h * base + 0;
            } else {
                h = h * base + 1;
            }
            h %= mod;
            cnt++;
        }
        h1[i][0] = h;
        sizes[i] = cnt;
    }

    h = 0;
    for(int i = 0; i < n; i++) {
        int d = s[i] - '0';
        if(!d) {
            if(i % 2 == 0) {
                h = h * base + 1;
            } else {
                h = h * base + 0;
            }
            h %= mod;
        }
        h1[i][1] = h;
    }
    

    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int l1, l2, k;
        scanf("%d%d%d", &l1, &l2, &k);
        l1--; l2--;
        if(pre(l1, l1 + k - 1) != pre(l2, l2 + k - 1)) {
            printf("NO\n");
            continue;
        }

        if(pre(l1, l1 + k - 1) == k) {
            printf("YES\n");
            continue;
        }

        int idx1 = 0, idx2 = 0;
        if(l1 % 2 == 1) idx1 = 1;
        if(l2 % 2 == 1) idx2 = 1;
        if(get(l1, l1 + k - 1, idx1) == get(l2, l2 + k - 1, idx2)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

    }
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
