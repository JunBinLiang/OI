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
const int N = 1000000 * 2 + 10;
pair<int, int> a[N];
pair<int, ll> mono[N];
ll s[N];
bool ans[N];
int l = 0, r = -1;

ll get(int l, int r) {
    if(!l) return s[r];
    return s[r] - s[l - 1];
}

int main() {
    int n;
    scanf("%d", &n);
    int last = -1;
    for(int i = 0; i < n; i++) {
        int p, d;
        scanf("%d%d", &p, &d);
        a[i] = {p, d};
        a[i + n] = {p, d};
        last = d;
    }
    
    //forward
    for(int i = 0; i < 2 * n; i++) {
        s[i] = a[i].first - a[i].second;
        if(i) s[i] += s[i - 1];
    }

    for(int i = 0; i < 2 * n; i++) {
        while(r - l + 1 > 0 && i - mono[l].first > n) l++;
        if(i >= n - 1) {
            ll pre = 0;
            if(i - n >= 0) pre = s[i - n];
            if(mono[l].second >= pre) {
                ans[i + 1 - n] = true;
            }
        }
        while(r - l + 1 > 0 && s[i] < mono[r].second) r--;
        mono[++ r] = {i, s[i]};
    }
    
    //backward
    int index = n - 1;
    int left = 0, right = 2 * n - 1;
    while(left < right) {
        swap(a[left], a[right]);
        left++; right--;
    }
    
    for(int i = 0; i < 2 * n - 1; i++) {
        a[i].second = a[i + 1].second;    
    }
    a[2 * n - 1].second = last;
    
    
    for(int i = 0; i < 2 * n; i++) {
        s[i] = a[i].first - a[i].second;
        if(i) s[i] += s[i - 1];
    }
    l = 0; r = -1;
    
    for(int i = 0; i < 2 * n; i++) {
        while(r - l + 1 > 0 && i - mono[l].first > n) l++;
        if(i >= n - 1) {
            ll pre = 0;
            if(i - n>= 0) pre = s[i - n];
            if(mono[l].second >= pre) {
                ans[index] = true;
            }
            index--;
        }
        while(r - l + 1 > 0 && s[i] < mono[r].second) r--;
        mono[++ r] = {i, s[i]};
    }

    
    
    for(int i = 0; i < n; i++) {
        if(ans[i]) {
            printf("TAK \n");
        } else {
            printf("NIE \n");
        }
    }
    
    return 0;
}
