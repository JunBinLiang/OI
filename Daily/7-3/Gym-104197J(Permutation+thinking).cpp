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
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

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


const int N = 2e5 + 10;
int n, m;
int a[N];
int sameCnt = 0, evenCnt = 0;
ll inv = 0;
void solve() {
  Fenwick :: init();

  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    inv += Fenwick :: query(a[i], n + 1);
    Fenwick :: update(a[i], 1);
    if(a[i] == i) sameCnt++;
    if((a[i] + i) % 2 == 0) {
      evenCnt++;
    }
  }
  
  //cout << sameCnt << " " << evenCnt << endl;

  for(int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    
    if(a[x] == x) sameCnt--;
    if(a[y] == y) sameCnt--;
    if((a[x] + x) % 2 == 0) evenCnt--;
    if((a[y] + y) % 2 == 0) evenCnt--;
    
    swap(a[x], a[y]);
    
    if(a[x] == x) sameCnt++;
    if(a[y] == y) sameCnt++;
    if((a[x] + x) % 2 == 0) evenCnt++;
    if((a[y] + y) % 2 == 0) evenCnt++;
    
    //for(int j = 1; j <= n; j++) cout << a[j] << " ";
    //cout << endl;
    //cout << sameCnt << "  " << evenCnt << "  " << endl << endl;
    
    inv++;
    if(inv % 2 == 1) {
      printf("%d\n", n);
    } else {
      if(sameCnt == n) { //array is sorted
        printf("-1\n", n);
      } else {
        if(evenCnt != n) {
          printf("%d\n", n - 1);
        } else {
          printf("%d\n", n - 2);
        }
      }
    }
  }
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
      solve();
    }
    return 0;
}

