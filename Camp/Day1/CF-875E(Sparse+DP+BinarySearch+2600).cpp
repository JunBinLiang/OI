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

const int N = 1e5 + 10;
int n, m, s1, s2;
int a[N];
int to[N];
int f1[N][19];
int f2[N][19];
bool check(ll mid) {
    for(int i = 0; i < m; i++) to[i] = -1;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < 19; j++) {
            f1[i][j] = f2[i][j] = -1;
        }
    }
    for(int i = 0; i < m; i++) {
        f1[i][0] = a[i];
        f2[i][0] = a[i];
    }

    for(int j = 1; j < 19; j++) {
        for(int i = 0; i < m; i++) {
            int pa = i + (1 << (j - 1));
            if(pa >= m) break;
            if(pa < m && f1[pa][j - 1] != -1) {
                f1[i][j] = min(f1[i][j - 1], f1[pa][j - 1]);
            }
        }
    }

    for(int j = 1; j < 19; j++) {
        for(int i = 0; i < m; i++) {
            int pa = i + (1 << (j - 1));
            if(pa >= m) break;
            if(f2[pa][j - 1] != -1) {
                f2[i][j] = max(f2[i][j - 1], f2[pa][j - 1]);
            }
        }
    }


    for(int i = 0; i < m; i++) {
        int x = i;
        ll l = (a[i] + 0ll) - mid, r = (a[i] + 0ll) + mid;
        for(int j = 18; j >= 0; j--) {
            if((x + (1 << (j)) - 1) >= m) continue;
            if(f1[x][j] >= l && f1[x][j] <= r && f2[x][j] >= l && f2[x][j] <= r) {
                x += (1 << j);
            }   
        }
        to[i] = x - 1;
    }
    
    /*if(mid == 1) {
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < 5; j++) {
                cout << f1[i][j] << "  ";
            }cout << endl;
        }
        
        cout << endl << endl;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < 5; j++) {
                cout << f2[i][j] << "  ";
            }cout << endl;
        }
        
        cout << endl;
        cout << mid << endl;
        for(int i = 0; i < m; i++) cout << to[i] << "  ";
        cout << endl << endl;
    }*/

    int a1 = to[0], b1 = to[1];
    for(int i = 2; i < m; i++) {
        bool x = false, y = false;
        if(b1 >= i) {
            x = true;
        }
        if(a1 >= i) {
            y = true;
        }
        if(x) {
            a1 = max(a1, to[i]);
        }
        if(y) {
            b1 = max(b1, to[i]);
        }
        if((!x) && (!y)) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> s1 >> s2;
    if(s1 > s2) swap(s1, s2);
    m = n + 2;
    a[0] = s1;
    a[1] = s2;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i + 2]);
    }

    ll l = (s2 - s1), r = 20000000000ll;
    ll res = -1;
    while(l <= r) {
        ll mid = l + (r - l) / 2;
        if(check(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << res << endl;
    return 0;
}
