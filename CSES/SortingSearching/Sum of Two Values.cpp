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
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define JBFOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 


void solve() {
    int n, x;
    cin >> n >> x;
    map<int, int> f;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        if(f.find(x - v)  != f.end()) {
            cout << f[x - v] << " " << i << endl;
            return;
        }
        f[v] = i;
    }
    cout << "IMPOSSIBLE" << endl;
}

int main()
{
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
