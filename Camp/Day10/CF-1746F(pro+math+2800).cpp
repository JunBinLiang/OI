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

const int N = 3e5 + 10, M = 61;
int a[N];
int n, m;
map<int, int> f;
ll rdn[N * 2];
int id = 0;

namespace Fenwick {
  int tree[M][N];
  void init() {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            tree[i][j] = 0;
        }
    }
  }

  void update(int which, int i, int val) {
    i++;
    while(i < N){
      tree[which][i] += val;
      i += (i & -i);
    }
  }

  int pre(int which, int i) {
    int sum = 0;
    while(i > 0){
      sum += tree[which][i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int which, int i, int j) {
      return pre(which, j + 1) - pre(which, i);
  }
}

void solve() {
    scanf("%d%d", &n, &m);
    
    for(int i = 0; i < N * 2; i++) {
        rdn[i] = rands();
    }
    Fenwick :: init();
    
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        int x = a[i];
        if(f.find(x) == f.end()) {
            f[x] = id;
            id++;
        }
        ll ra = rdn[f[x]];
        for(int j = 0; j < M; j++) {
            if(ra & (1ll << j)) {
                Fenwick :: update(j, i, 1);
            }
        }
    }

    for(int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int idx, x;
            scanf("%d%d", &idx, &x);
            if(f.find(x) == f.end()) {
                f[x] = id++;
            }

            int old = a[idx - 1];
            ll r1 = rdn[f[old]];
            for(int j = 0; j < M; j++) {
                if(r1 & (1ll << j)) {
                    Fenwick :: update(j, idx - 1, -1);
                }
            }

            a[idx - 1] = x;
            ll r2 = rdn[f[x]];
            for(int j = 0; j < M; j++) {
                if(r2 & (1ll << j)) {
                    Fenwick :: update(j, idx - 1, 1);
                }
            }

        } else {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            bool is = true;
            for(int j = 0; j < M; j++) {
                if(Fenwick :: query(j, l - 1, r - 1) % k != 0) {
                    is = false;
                    break;
                }
            }
            if(is) printf("YES\n");
            else printf("NO\n");
        }
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

