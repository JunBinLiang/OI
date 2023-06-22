
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
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


const int MAX = 2e5 + 100;
const int INF = 2e5 + 100;
set<pair<int, int>> sets1[MAX * 4], sets2[MAX * 4];
struct Node {
  int l, r;
  int mx, mn, mxIdx, mnIdx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    sets1[id].clear();
    sets2[id].clear();
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, -1, INF, -1, -1};
  tree[id * 2 + 2] = {mid + 1, r, -1, INF, -1, -1};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int st, int val, int idx) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    if(st == 0) { //left
      sets1[id].insert({val, idx});
      auto it = sets1[id].begin();
      tree[id].mn = it -> first;
      tree[id].mnIdx = it -> second;
    } else if(st == 1) { //right
      sets2[id].insert({val, idx});
      auto it = sets2[id].end();
      it--;
      tree[id].mx = it -> first;
      tree[id].mxIdx = it -> second;
    } else if(st == 2) {
      sets1[id].erase({val, idx});
      tree[id].mn = INF, tree[id].mnIdx = -1;
      if(sets1[id].size() > 0) {
        auto it = sets1[id].begin();
        tree[id].mn = it -> first;
        tree[id].mnIdx = it -> second;
      }

    } else if(st == 3) {
      sets2[id].erase({val, idx});
      tree[id].mx = -1, tree[id].mxIdx = -1;
      if(sets2[id].size() > 0) {
        auto it = sets2[id].end();
        it--;
        tree[id].mx = it -> first;
        tree[id].mxIdx = it -> second;
      }
    }

    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, st, val, idx);
  } else {
    update(right, index, st, val, idx);
  }

  if(tree[left].mx > tree[right].mx) {
    tree[id].mx = tree[left].mx;
    tree[id].mxIdx = tree[left].mxIdx;
  } else {
    tree[id].mx = tree[right].mx;
    tree[id].mxIdx = tree[right].mxIdx;
  }
  
  if(tree[left].mn < tree[right].mn) {
    tree[id].mn = tree[left].mn;
    tree[id].mnIdx = tree[left].mnIdx;
  } else {
    tree[id].mn = tree[right].mn;
    tree[id].mnIdx = tree[right].mnIdx;
  }
}

pair<int, int> query1(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return {tree[id].mn, tree[id].mnIdx};
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    auto p1 = query1(left, s, mid);
    auto p2 = query1(right, mid + 1, e);
    if(p1.first < p2.first) return p1;
    else return p2;
  }
}

pair<int, int> query2(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return {tree[id].mx, tree[id].mxIdx};
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query2(left, s, e);
  } else if(s >= mid + 1) {
      return query2(right, s, e);
  } else {
    auto p1 = query2(left, s, mid);
    auto p2 = query2(right, mid + 1, e);
    if(p1.first > p2.first) return p1;
    else return p2;
  }
}


const int N = 1e5 + 10;
int n;
int c[N];
pair<int, int> lines[N];
bool ok = true;

void dfs(int u, int col) {
  c[u] = col;
  int l = lines[u].first, r = lines[u].second;
  
  while(true) {
    pair<int, int> p = query1(0, l, r);
    if(p.second == -1 || p.first >= l) break;
    int mostLeft = p.first, index = p.second;
    
    update(0, lines[index].second, 2, lines[index].first, index);
    if(c[index] == -1) {
      //cout << "a  " << u + 1 << " " << col << "  |" << p.second + 1 << endl;
      dfs(index, col ^ 1);
    } else {
      if(c[index] == c[u]) {
          ok = false;
          return;
      }
    }
  }

  while(true) {
    pair<int, int> p = query2(0, l, r);
    if(p.second == -1 || p.first <= r) break;
    int mostRight = p.first, index = p.second;
    update(0, lines[index].first, 3, lines[index].second, index);
    if(c[index] == -1) {
      //cout << "b  " << u + 1 << " " << col << "  |" << p.second + 1 << endl;
      dfs(index, col ^ 1);
    } else {
      if(c[index] == c[u]) {
          ok = false;
          return;
      }
    }
  }

}

void out(vector<int>& a) {
  for(int i : a) cout << i << " ";
  cout << endl;
}


bool check(vector<pair<int, int>>& line) {
    tree[0] = {0, 200000, -1, INF, -1, -1};
    build(0);
    sort(line.begin(), line.end());
    for(int i = 0; i < line.size(); i++) {
        update(0, line[i].first, 1, line[i].second, i);
    }
    
    for(int i = 0; i < line.size(); i++) {
        int l = line[i].first, r = line[i].second;
        update(0, line[i].first, 3, line[i].second, i);
        pair<int, int> p = query2(0, l, r);
        if(p.second != -1 && p.first >= line[i].second) return false;
    }
    return true;
}

void solve() {
  memset(c, -1, sizeof c);
  scanf("%d", &n);
  tree[0] = {0, 200000, -1, INF, -1, -1};
  build(0);
  
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &lines[i].first, &lines[i].second);
    update(0, lines[i].second, 0, lines[i].first, i);
    update(0, lines[i].first, 1, lines[i].second, i);
  }

  for(int i = 0; i < n; i++) {
    if(c[i] != -1) continue;
    dfs(i, 0);
  }
  
  if(!ok) {
    cout << -1 << endl;
    return;
  }
  
  vector<pair<int, int>> l1, l2;
  vector<int> res1, res2;
  for(int i = 0; i < n; i++) {
    if(c[i] == 0) {
      res1.push_back(i + 1);
      l1.push_back(lines[i]);
    } else {
      res2.push_back(i + 1);
      l2.push_back(lines[i]);
    }
  }
  
  if(!check(l1) || !check(l2)) {
      cout << -1 << endl;
      return;
  }
  
  cout << res1.size() << " " << res2.size() << endl;
  out(res1);
  out(res2);
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
