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


//8 : 05 - 8:55
const int N = 2e5 + 10;
int n;
int a[N];
int p[N];
bool is[N];
void solve() {
    scanf("%d", &n);
    ll res = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        p[a[i]] = i;
    }
    for(int i = 0; i <= n + 1; i++) is[i] = false;

    int l = p[0], r = p[0];
    is[0] = true;
    for(int mex = 1; mex < n; mex++) {
        if(is[mex]) continue;
        int pos = p[mex];
        int len = r - l + 1;
        int big = (len - (mex));
        if(big <= mex) {
            res++;
        }
        int more = max(0, mex - big);
        int cnt1 = 0;
        if(pos < l) {
            int cnt2 = (n - r - 1);
            while(l - 1 >= pos) {
                l--;
                is[a[l]] = true;
                cnt1++;
                if(l != pos) {
                    res += min(max(0, mex - big - cnt1), cnt2);
                }
            }
            res += min(more, cnt2);
            res += min(more, cnt1 - 1);
        }
        if(pos > r) {
            int cnt2 = l;
            while(r + 1<= pos) {
                r++;
                is[a[r]] = true;
                cnt1++;
                if(r != pos) {
                    res += min(cnt2, max(0, mex - big - cnt1));
                }
                    
            }
             
            res += min(more, cnt2);
            res += min(more, cnt1 - 1);
        }
    }

    printf("%lld\n", res + 1);
} 

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

