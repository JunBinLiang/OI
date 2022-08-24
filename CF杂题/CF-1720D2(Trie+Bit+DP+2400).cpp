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


const int N = 3e5 + 10;
int a[N];
int id = N * 4 * 4;

struct Node {
  int bit[2];
  int dp[2][2];
  void init() {
    memset(bit, -1, sizeof(bit));
    memset(dp, 0, sizeof(dp));
  }
} trie[N * 4 * 4];

void add(int x, int v, int value, int idx) {
  int root = 0;
  ve<ve<int>> path;
  for(int i = 30; i >= 0; i--) {
    int b = 0;
    if(x & (1 << i)) b = 1;
    if(trie[root].bit[b] == -1) {
      trie[root].bit[b] = id;
      id++; 
    }
    int b2 = 0, b3 = 0;
    if(value & (1 << i)) b2 = 1;
    if(idx & (1 << i)) b3 = 1;
    
    root = trie[root].bit[b];
    trie[root].dp[b2][b3] = max(v, trie[root].dp[b2][b3]);
  }
}

int query(int x, int value, int idx) {
  int res = 0;
  int root = 0;
  for(int i = 30; i >= 0 && root != -1; i--) {
    int b = 0;
    if(x & (1 << i)) b = 1;
    
    int b2 = 0, b3 = 0;
    if(idx & (1 << i)) b2 = 1;
    if(value & (1 << i)) b3 = 1;

    
    if(b == 0) {
        if(trie[root].bit[1] != -1) {
            res = max(res, trie[trie[root].bit[1]].dp[b2][b3 ^ 1]);
        }
    } else {
        if(trie[root].bit[0] != -1) {
            res = max(res, trie[trie[root].bit[0]].dp[b2][b3 ^ 1]);
        }
    }
    root = trie[root].bit[b];

    
  }
  return res;
}


void solve() { 
  int n;
  int res = 0;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  
  for(int i = 0; i < id; i++) {
      trie[i].init();
  }

  id = 1;
  trie[0].init();
  for(int i = 0; i < n; i++) {
    int v = query(a[i] ^ i, a[i], i);
    v += 1;
    res = max(res, v);
    add(a[i] ^ i, v, a[i], i);
  }
  cout << res << endl;  
}

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
}
  
  
