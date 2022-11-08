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


const int N = 2e5 + 10;
ll a[N];
void solve() {
    int n;
    scanf("%d", &n);
    ll mn = 1e9, mx = -1e9;;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
    }

    if(mn == 0 && mx == 0) {
        printf("YES\n");
        for(int i = 0; i < n; i++) {
            printf("1 ");
        }
        printf("\n");
        return;
    }

    if(mn == mx) {
        printf("NO\n");
        return;
    }
    


    ll best = -1, idx = -1;
    for(int i = 0; i < n; i++) {
        best = max(best, a[i]);
    }

     

    for(int i = 0; i < n; i++) {
        int p = (i - 1 + n) % n;
        if(a[i] == best && a[p] < a[i]) {
            idx = i;
            break;
        }
    }

    idx--;
    for(int i = 0; i < n - 1; i++) {
        if(idx < 0) {
            idx += n;
        }
        int nxt = (idx + 1) % n;
        if(a[idx] == 0) {
            if(i == 0) {
                a[idx] = a[nxt] * 2;
            } else {
                a[idx] += a[nxt];
            }
        } else {
            a[idx] += a[nxt];
        }
        idx --;
    } 

    
    printf("YES\n");
    for(int i = 0; i < n; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");

} 

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

