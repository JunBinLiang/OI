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

const int N = 1e6 + 10;
int a[N];
struct Node {
  int l, r;
  int setTo = 0;
  int o, i, oi, io;
} tree[N * 4];


void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    if(a[l] == 0) {
        tree[id].o = 1; 
    } else {
        tree[id].i = 1;
    }
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree[left] = {l, mid, 0, 0, 0, 0, 0};
  tree[right] = {mid + 1, r, 0, 0, 0, 0, 0};
  build(left);
  build(right);
  
  tree[id].o = tree[left].o + tree[right].o;
  tree[id].i = tree[left].i + tree[right].i;
  
  if(tree[left].o != 0 && tree[right].i != 0) {
      tree[id].oi = max(tree[id].oi, tree[left].o + tree[right].i);
  }
  if(tree[right].oi != 0) {
      tree[id].oi = max(tree[id].oi, tree[left].o + tree[right].oi);
  }
  if(tree[left].oi != 0) {
      tree[id].oi = max(tree[id].oi, tree[left].oi + tree[right].i);
  }
  
  if(tree[left].i != 0 && tree[right].o != 0) {
      tree[id].io = max(tree[id].io, tree[left].i + tree[right].o);
  }
  if(tree[right].io != 0) {
      tree[id].io = max(tree[id].io, tree[left].i + tree[right].io);
  }
  if(tree[left].io != 0) {
      tree[id].io = max(tree[id].io, tree[left].io + tree[right].o);
  }
}

void update(int id, int s, int e) { 
  int l = tree[id].l, r = tree[id].r;
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(l == s && r == e) {
    if(l == r) {
        swap(tree[id].i, tree[id].o);
    } else {
        tree[id].setTo ^= 1;
        swap(tree[id].i, tree[id].o);
        swap(tree[id].io, tree[id].oi);
    }
    return;
  }

  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r);
    update(right, tree[right].l, tree[right].r);
    tree[id].setTo = 0;
  }

  if(e <= mid) {
    update(left, s, e);
  } else if(s >= mid + 1) {
    update(right, s, e);
  } else {
    update(left, s, mid);
    update(right, mid + 1, e);
  }
  
  tree[id].o = tree[left].o + tree[right].o;
  tree[id].i = tree[left].i + tree[right].i;
  
  tree[id].oi = tree[id].io = 0;
  if(tree[left].o != 0 && tree[right].i != 0) {
      tree[id].oi = max(tree[id].oi, tree[left].o + tree[right].i);
  }
  if(tree[right].oi != 0) {
      tree[id].oi = max(tree[id].oi, tree[left].o + tree[right].oi);
  }
  if(tree[left].oi != 0) {
      tree[id].oi = max(tree[id].oi, tree[left].oi + tree[right].i);
  }
  
  if(tree[left].i != 0 && tree[right].o != 0) {
      tree[id].io = max(tree[id].io, tree[left].i + tree[right].o);
  }
  if(tree[right].io != 0) {
      tree[id].io = max(tree[id].io, tree[left].i + tree[right].io);
  }
  if(tree[left].io != 0) {
      tree[id].io = max(tree[id].io, tree[left].io + tree[right].o);
  }
}


int n, m;
void solve() {
    cin >> n >> m;
    string s;
    cin >> s;   
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '4') a[i] = 0;
        else a[i] = 1;
    } 

    tree[0] = {0, n - 1, 0, 0, 0, 0, 0};
    build(0);

    for(int i = 0; i < m; i++) {
        string q;
        cin >> q;
        if(q[0] == 'c') {
            int res = 0;
            res = max(res, tree[0].i);
            res = max(res, tree[0].o);
            res = max(res, tree[0].oi);
            printf("%d\n", res);
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            l--; r--;
            update(0, l, r);
        }
    }

}

int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
