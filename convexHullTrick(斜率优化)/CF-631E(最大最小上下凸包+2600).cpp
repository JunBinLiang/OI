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
ll p[N];
ll a[N];
int n;
ll res = 0, sum = 0;
int q[N];
//hull : 最小 => 下凸包   最大 => 上凸包
ll up(int i, int j) {
    return p[i] - p[j];
}

ll down(int i, int j) {
    return i - j;
}

void solve() {
    scanf("%d", &n);
    p[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum += ((i + 0ll) * a[i]); 
        res = sum;
        p[i] = p[i - 1] + a[i];
    }
    
    //move back + move front
    int hh = 0, tt = 1;
    q[0] = n;
    
    //cout << sum << endl;
    
    //上凸包
    for(int i = n - 1; i >= 1; i--) {
        int l = hh, r = tt - 2;
        int pos = tt - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(up(q[mid + 1], q[mid]) >= (double)(a[i] * down(q[mid + 1], q[mid]))) {
                pos = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        
        int j = q[pos];
        ll tot = sum - p[j] + p[i] + (a[i]) * j - (a[i]) * i;
        res = max(res, tot);
        while(tt - hh > 1 && (double)up(q[tt-1], i) * down(q[tt-2], q[tt-1]) >= (double)up(q[tt-2], q[tt-1])* down(q[tt-1], i) ) {
            tt--;
        }
        q[tt++] = i;
    }
    

    hh = 0; tt = 1;
    q[0] = 0;

    //下凸包
    for(int i = 1; i <= n; i++) {
        int l = hh, r = tt - 2;
        int pos = tt - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(up(q[mid + 1], q[mid]) >= (a[i]) * down(q[mid + 1], q[mid])) {
                pos = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        
        int j = q[pos];
        ll tot = sum - a[i] * i + a[i] * j + p[i] - a[i] - p[j] + a[i];
        
        res = max(res, tot);
        while(tt - hh > 1 && (double)up(q[tt-1], i) * down(q[tt-2], q[tt-1]) <= (double)up(q[tt-2], q[tt-1])* down(q[tt-1], i) ) {
            tt--;
        }
        q[tt++] = i;
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

