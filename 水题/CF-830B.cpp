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

namespace Fenwick {
  const int SIZE = 200000 + 100;
  int tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}

//1: 24 - 1 : 43
const int N = 1e5 + 10;
vector<int> g[N];
int a[N];
int n;
ll res = 0;
void solve() {
    cin >> n;
    vector<int> b;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b.push_back(a[i]);
        g[a[i]].push_back(i);
    }
    Fenwick :: init();
    for(int i = 0; i < n; i++) Fenwick :: update(i, 1);


    /*for(int i : b) cout << i << " ";
    cout << endl << endl;*/

    sort(b.begin(), b.end());
    int last = 0;
    
    for(int i = 0; i < b.size(); i++) {
        int j = i;
        int cnt = 0;
        while(j < b.size() && b[j] == b[i]) {
            j++;
            cnt++;
        }

        vector<int>& v = g[b[i]];
        int l = 0, r = v.size() - 1;
        int p = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(v[mid] >= last) {
                p = mid;
                r = mid - 1;   
            } else {
                l = mid + 1;
            }
        }

        if(p != -1) {
            int end = v.back();
            res += Fenwick :: query(last, v.back());
            int all = 0;
            for(int i = p; i < v.size(); i++) {
                Fenwick :: update(v[i], -1);
                all++;
            }
            while(all--)v.pop_back();
            last = end + 1;
            if(v.size() > 0) {
                res += (Fenwick :: query(last, n));
                last = 0;
                i = i - 1;
                continue;
            } 

        } else {
            res += (Fenwick :: query(last, n));
            last = 0;
            i = i - 1;
            continue;
        }
        i = j - 1;
    }

    cout << res << endl;

}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
