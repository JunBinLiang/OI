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


using namespace std;  
using ll = long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


namespace Fenwick {
  const int SIZE = 500000 + 100;
  ll tree[SIZE];
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

  ll pre(int i) {
    ll sum = 0;
    while(i > 0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  
  ll query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}

int n, k;
ll res = 0;
void cal(vector<int>& a, int k, bool first) {
    int n = a.size();
    vector<pair<int, int>> b;
    for(int i = 0; i < n; i++) {
        b.push_back({a[i], i});
    }
    sort(b.begin(), b.end());

    set<int> s;
    for(int i = 0, j = 0; i < n; i++) {
        vector<pair<int, int>> c;
        while(j < i && b[j].first + k < b[i].first) {
            int idx = b[j].second;
            s.erase(idx);
            int v = Fenwick :: query(idx, idx);
            c.push_back({idx, v});
            Fenwick :: update(idx, -v);
            j++;
        }
        

        for(pair<int, int>& p : c) {
            int idx = p.first, v = p.second;
            auto it = s.upper_bound(idx);
            if(it != s.end()) {
                Fenwick :: update(*it, v);
            }
        }
        
        
        /*cout << b[i].first << " " << b[i].second <<"       " << c.size() << endl;
        for(int y = 0; y < n; y++) {
            cout << Fenwick :: query(i, i) << " ";
        } cout << endl << endl;*/

        int x = i;
        int cnt = 0;
        vector<int> d;
        while(x < b.size() && b[x].first == b[i].first) {
            int idx = b[x].second;
            s.insert(idx);
            res += Fenwick :: query(0, idx);
            d.push_back(idx);
            x++;
            cnt++;
        }

        if(first) {
            ll tot = (1ll + cnt) * cnt / 2;
            res += tot;
        }

        for(int idx : d) {
            Fenwick :: update(idx, 1);
        }
        
        i = x - 1;
    }

    //clean
    for(int i = 0; i < n; i++) {
        int old = Fenwick :: query(i, i);
        Fenwick :: update(i, -old);
    }
}

void solve() {
    scanf("%d%d", &n, &k);
    vector<int> a(n);
    res = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    cal(a, k, true);
    reverse(a.begin(), a.end());
    cal(a, k, false);
    printf("%lld\n", res);
}

int main() {
	// your code goes here
	int t = 1;
  Fenwick :: init();
	cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
