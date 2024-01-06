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

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

map<int, int> f, v;

void init(int u) {
    if(f.find(u) == f.end()) {
        f[u] = u;
        v[u] = 0;
    }
}
 
int find(int u) {
    if(f[u] == u) {
        return f[u];
    }

    int p = find(f[u]);
    v[u] ^= v[f[u]];
    return f[u] = p;
}

void solve() {
    int m;
    cin >> m;
    int ans = 0;
    for(int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        int last = (ans == -1) ? 1 : ans;
        if(op == 1) {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            l ^= last; r ^= last; x ^= last;
            if(l > r) swap(l, r);
            r++;
            init(l), init(r);
            int root1 = find(l), root2 = find(r);
            if(root1 != root2) {
                f[root1] = root2;
                v[root1] = x ^ v[r] ^ v[l];
            }

        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            l ^= last; r ^= last; 
            if(l > r) swap(l, r);
            r++;
            init(l), init(r);
            int root1 = find(l), root2 = find(r);
            if(root1 != root2) ans = -1;
            else {
                ans = v[l] ^ v[r];
            }
            printf("%d\n", ans);
        }
    }
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
