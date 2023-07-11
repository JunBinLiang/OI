
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
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
using namespace __gnu_pbds;


template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

order_tree<int> ord, f;
map<int, int> g;

int n;
string op, c;
void solve() {
  cin >> n;
  
  for(int i = 0; i < n; i++) {
    cin >> op;
    if(op[0] == '+') {
      int t;
      cin >> t >> c;
      if(c[0] == 'E') { //enque
        int v;
        cin >> v;
        f.insert(t);
        g[t] = v;
      } else { //deque
        ord.insert(t);
      }
    } else if(op[0] == '-') { //erase a single time zone
      int t; 
      cin >> t;
      if(ord.find(t) == ord.end()) {
        f.erase(t);
        g.erase(t);
      } else {
        ord.erase(t);
      }
    } else if(op[0] == 'Q') {
      int t, k; 
      cin >> t >> k;
      int delsz = ord.order_of_key(t + 1);
      int kth = k + delsz - 1;
      auto it = f.find_by_order(kth);
      cout << g[*it] << endl;
      fflush(stdout);
    }
  }
  
  /*order_tree<int> ord;
  ord.insert(20);
  ord.insert(10);
  ord.insert(15);
  cout << ord.order_of_key(15) << endl;
  ord.erase(15);*/
  
}

int main() {
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
