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

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");
const int MAX = 300000 + 100;

void solve() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    
    ll l = 0, r = 300000000000000ll / 2;
    ll res = 0;
    while(l <= r) {
        ll mid = l + (r - l) / 2;
        bool ok = false;

        priority_queue<int> maxHeap;
        vector<int> right(n);
        int j = n - 1;
        ll sum = 0;
        for(int i = 0; i <= k; i++) {
            while(maxHeap.size() < i && j >= 0) {
                sum += a[j];
                maxHeap.push(a[j]);
                if(sum > mid) {
                    sum -= maxHeap.top();
                    maxHeap.pop();
                }
                j--;
            }

            if(maxHeap.size() == i && j + 1 < n) {
                right[j + 1] = max(right[j + 1], i);
            }
        }

        for(int i = n - 2; i >= 0; i--) {
            right[i] = max(right[i], right[i + 1]);
        }
        
        while(maxHeap.size() > 0) maxHeap.pop();
        j = 0;
        sum = 0;
        for(int i = 0; i <= k && !ok; i++) {
            while(maxHeap.size() < i && j < n) {
                sum += a[j];
                maxHeap.push(a[j]);
                if(sum > mid) {
                    sum -= maxHeap.top();
                    maxHeap.pop();
                }
                j++;
            }

            if(maxHeap.size() == i) {
                int otherK = k - i;
                if(otherK == 0) {
                    ok = true;
                } else if(j < n && otherK <= right[j]) {
                    ok = true;
                }
            } else {
                break;
            }

        }


        if(ok) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }


    printf("%lld\n", res);
}

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
