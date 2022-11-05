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

unsigned long long seed=131;
unsigned long long rands(){return seed=(seed<<15)+(seed<<8)+(seed>>3);}


void debug() {
    cout << "________________" << endl;
}


const int N = 3e5 + 10;
int n;
int a[N];
ll rnd[N], p[N], pre[N];
ll res = 0;
void solve() {
    scanf("%d", &n);
    p[0] = 0;
    for(int i = 1; i <= n; i++) {
        rnd[i] = rands();
        p[i] = rnd[i];  
        p[i] ^= p[i - 1];
    }

    pre[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pre[i] = rnd[a[i]] ^ pre[i - 1];
    }


    for(int i = 1; i <= n; i++) {
        if(a[i] == 1) {
            int mx = 1;
            res++;

            for(int j = i + 1; j <= n && a[j] != 1; j++) {
                mx = max(mx, a[j]);
                if(j - mx < 0) continue;
                if((pre[j] ^ pre[j - mx]) == p[mx]) {
                    res++;
                }
            }

            mx = 1;
            for(int j = i - 1; j >= 0 && a[j] != 1; j--) {
                mx = max(mx, a[j]);
                if(j + mx - 1 > n) continue;
                if((pre[j - 1] ^ pre[j + mx - 1]) == p[mx]) {
                    res++;
                }
            }
        }
    }

    cout << res << endl;
} 

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

