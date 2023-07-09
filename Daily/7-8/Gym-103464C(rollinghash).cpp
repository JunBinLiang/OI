#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

const int N = 2e6 + 10;
int base = 131;

char s[N];
ull h1[N], h2[N], p[N];
int n;

void init() {
  p[0] = 1;
  for(int i = 1; i < N; i++) p[i] = p[i - 1] * base;
}


ull get1(ull h[], int l, int r) {
    if(l == 0) return h[r];
    int sz = r - l  +1;
    return h[r] - h[l - 1] * p[sz]; 
}

ull get2(ull h[], int l, int r) {
    if(r == n) return h[l];
    int sz = r - l + 1;
    return h[l] - h[r + 1] * p[sz];
}

int main()
{
    scanf("%d", &n);
    scanf("%s", s);
    
    init();
    
    //forward hash
    ull sum = 0;
    for(int i = 0; i < n; i++) {
        sum = sum * base + s[i] - 'a' + 1;
        h1[i] = sum;
    }
    
    sum = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] == 'a') s[i] = 'b';
        else s[i] = 'a';
        sum = sum * base + s[i] - 'a' + 1;
        h2[i] = sum;
    }
    
    
    int res = 0;
    for(int i = 0; i < n - 1; i++) {
        if(s[i] == s[i + 1]) continue;
        res = max(res, 2);
        int add = -1;
        int l = 1, r = min(i + 1, n - (i + 1)); 
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(get1(h1, i - mid + 1, i) == get2(h2, i + 1, i + 1 + mid - 1)) {
                add = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        
        if(add != -1) {
            res = max(res, 2 * add);
        }
    }
    cout << res << endl;
}
