#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

const int N = 2e5 + 10;
//2:57

bool find(vector<int>& a, ll v) {
    int l = 0, r = a.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] == v) return true;
        if(a[mid] > v) r = mid - 1;
        else l = mid + 1;

    }
    return false;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    sort(a.begin(), a.end());

    vector<ll> res;
    res.push_back(a[0]);

    for(int i = 0; i < n; i++) {
        ll v = a[i];
        for(int j = 0; j < 31; j++) {
            int add = (1 << j);
            if(find(a, v + add)) {
                if(res.size() == 1) {
                    res.clear();
                    res.push_back(v);
                    res.push_back(v + add);
                }

                if(find(a, v + add + add)) {
                    res.clear();
                    res.push_back(v);
                    res.push_back(v + add);
                    res.push_back(v + add + add);
                    cout << 3 << endl;
                    cout << v << " " << v + add << " " << v + add * 2 << endl;
                    return;
                }
            }
        }

    }
    
    cout << res.size() << endl;
    for(ll v : res) {
        cout << v << " ";
    }


}

int main() {
    solve();
    return 0;
}
