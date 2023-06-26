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

const int N = 1e5 + 10;
const int INF = 2e9;
int a[N], L[N][2], R[N][2]; //L is minimum, R is maximum
ll p[N];
int n;

struct Node {
  int l, r;
  int setTo = INF;
  int rMin, rIdx;
  ll lval; int lIdx;
  int setIdx = -1;
  ll lbest; int llIdx;
} tree[N * 4];


void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    if(l == 0) return;
    tree[id].lIdx = L[l][0];
    tree[id].lval = p[l] - L[l][1];

    tree[id].llIdx = L[l][0];
    tree[id].lbest = p[l] - L[l][1];

    //cout << "build " << l << "  " << p[l] << " " << L[l][1] << " " << tree[id].lval << endl;
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, INF, INF, -1, INF, -1};
  tree[id * 2 + 2] = {mid + 1, r, INF, INF, -1, INF, -1};
  build(id * 2 + 1);
  build(id * 2 + 2);
  int left = id * 2 + 1; int right = id * 2 + 2;

  if(tree[left].lval < tree[right].lval) {
    tree[id].lval = tree[left].lval;
    tree[id].lIdx = tree[left].lIdx;

    tree[id].lbest = tree[left].lval;
    tree[id].llIdx = tree[left].lIdx;
  } else {
    tree[id].lval = tree[right].lval;
    tree[id].lIdx = tree[right].lIdx;

    tree[id].lbest = tree[right].lval;
    tree[id].llIdx = tree[right].lIdx;
  }
}

void build1(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    if(l == 0) return;
    tree[id].lIdx = l;
    tree[id].lval = p[l];

    tree[id].llIdx = l;
    tree[id].lbest = p[l];
    //cout << "build1 " << l << "  " << p[l] << " " << tree[id].lval << endl;
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, INF, INF, -1, INF, -1};
  tree[id * 2 + 2] = {mid + 1, r, INF, INF, -1, INF, -1};
  build1(id * 2 + 1);
  build1(id * 2 + 2);
  int left = id * 2 + 1; int right = id * 2 + 2;

  if(tree[left].lval < tree[right].lval) {
    tree[id].lval = tree[left].lval;
    tree[id].lIdx = tree[left].lIdx;

    tree[id].lbest = tree[left].lval;
    tree[id].llIdx = tree[left].lIdx;
  } else {
    tree[id].lval = tree[right].lval;
    tree[id].lIdx = tree[right].lIdx;

    tree[id].lbest = tree[right].lval;
    tree[id].llIdx = tree[right].lIdx;
  }
}

void update(int id, int s, int e, int val, int idx) { 
  int l = tree[id].l, r = tree[id].r;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(l == s && r == e) {
    //if(l == 2 && r == 3) {
        //cout << "before update gg : " << tree[id].lIdx << " " << tree[id].lval << " "  << tree[id].rMin << " " << tree[id].rIdx <<"    |" << tree[right].lval << endl;
        //cout << val << "  " << idx << " " << tree[id].setTo << endl;
    //}  
      
    if(tree[id].setTo == INF) {
      tree[id].setTo = val;
      tree[id].setIdx = idx;
      if(l != r && min(tree[left].lbest, tree[right].lbest) + tree[id].setTo 
        < min(tree[left].lval + tree[left].rMin, tree[right].lval + tree[right].rMin)
      ) {
        tree[id].rMin = tree[id].setTo;
        tree[id].rIdx = tree[id].setIdx;
        if(tree[left].lbest < tree[right].lbest) {
          tree[id].lval = tree[left].lbest;
          tree[id].lIdx = tree[left].llIdx;
        } else {
          tree[id].lval = tree[right].lbest;
          tree[id].lIdx = tree[right].llIdx;
        }
      } else if(l == r) {
          if(tree[id].rMin > tree[id].setTo) {
              tree[id].rMin = tree[id].setTo;
              tree[id].rIdx = tree[id].setIdx;
          }
      }
    
    } else {
      if(val < tree[id].setTo) {
        tree[id].setTo = val;
        tree[id].setIdx = idx;

        if(l != r && min(tree[left].lbest, tree[right].lbest) + tree[id].setTo 
        < min(tree[left].lval + tree[left].rMin, tree[right].lval + tree[right].rMin)
      ) {
        tree[id].rMin = tree[id].setTo;
        tree[id].rIdx = tree[id].setIdx;
        if(tree[left].lbest < tree[right].lbest) {
          tree[id].lval = tree[left].lbest;
          tree[id].lIdx = tree[left].llIdx;
        } else {
          tree[id].lval = tree[right].lbest;
          tree[id].lIdx = tree[right].llIdx;
        }
      } else if(l == r) {
          if(tree[id].rMin > tree[id].setTo) {
              tree[id].rMin = tree[id].setTo;
              tree[id].rIdx = tree[id].setIdx;
          }
      }
        
      } 
    }

    return;
  }

  int mid = l + (r - l) / 2;
  if(tree[id].setTo != INF) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo, tree[id].setIdx);
    update(right, tree[right].l, tree[right].r, tree[id].setTo, tree[id].setIdx);
    tree[id].setTo = INF;
    tree[id].setIdx = -1;
  }

  if(e <= mid) {
    update(left, s, e, val, idx);
  } else if(s >= mid + 1) {
    update(right, s, e, val, idx);
  } else {
    update(left, s, mid, val, idx);
    update(right, mid + 1, e, val, idx);
  }

  if(tree[left].rMin + tree[left].lval < tree[right].rMin + tree[right].lval) {
    tree[id].lval = tree[left].lval;
    tree[id].lIdx = tree[left].lIdx;
    tree[id].rMin = tree[left].rMin;
    tree[id].rIdx = tree[left].rIdx;
  } else {
    tree[id].lval = tree[right].lval;
    tree[id].lIdx = tree[right].lIdx;
    tree[id].rMin = tree[right].rMin;
    tree[id].rIdx = tree[right].rIdx;
  } 
}

struct Info {
  ll lval; int lIdx;
  int rMin, rIdx;
};

Info query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return {tree[id].lval, tree[id].lIdx, tree[id].rMin, tree[id].rIdx};
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].setTo != INF) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo, tree[id].setIdx);
    update(right, tree[right].l, tree[right].r, tree[id].setTo, tree[id].setIdx);
    tree[id].setTo = INF;
    tree[id].setIdx = -1;
  }
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    auto p1 = query(left, s, mid);
    auto p2 = query(right, mid + 1, e);
    if(p1.rMin + p1.lval < p2.rMin + p2.lval) {
      return p1;
    } else {
      return p2;
    }
    
  }
}

Info query1(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  int mid = l + (r - l) / 2;
  if(l == s && r == e){
    cout << "query gg  :" << l << " " << r << "   |" << tree[id].lIdx << "  " << tree[id].lval << " " << tree[id].rIdx << "  " << tree[id].rMin  << endl;
    return {tree[id].lval, tree[id].lIdx, tree[id].rMin, tree[id].rIdx};
  }
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].setTo != INF) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo, tree[id].setIdx);
    update(right, tree[right].l, tree[right].r, tree[id].setTo, tree[id].setIdx);
    tree[id].setTo = INF;
    tree[id].setIdx = -1;
  }
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    auto p1 = query1(left, s, mid);
    auto p2 = query1(right, mid + 1, e);
    
    //cout <<"query " <<l << "  " << r << "    |" << p1.lval << "  " <<p1.rMin << "   |" << p2.lval << " " << p2.rMin << endl;
    if(p1.rMin + p1.lval < p2.rMin + p2.lval) {
      return p1;
    } else {
      return p2;
    }
    
  }
}


int ans1 = -1, ans2 = -1;
ll maxSum = -1000000000000000000;
void init() { 
  map<ll, int> f;
  ll sum = 0;
  for(int i = 1; i <= n; i++) {
    sum += a[i];
    if(sum > maxSum) {
      maxSum = sum;
      ans1 = i; 
      ans2 = 1;
    }
    if(f.size() > 0) {
      auto it = f.begin();
      if(sum - (it -> first) > maxSum) {
        maxSum = sum - (it -> first);
        ans1 = it -> second + 1;
        ans2 = i;
      }
    }
    f[sum] = i;
  }
  
  if(ans1 == ans2) {
    ans1 = 1; 
    ans2 = n;
  } else { //just swap within the segment
  }
}

void solve() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  init();
  
  //cout << "init  : " << maxSum << " "  << ans1 << " " << ans2 << endl;

  p[0] = 0;
  for(int i = 1; i <= n; i++) {
    p[i] = p[i - 1] + a[i];
  }
  R[n][0] = n;
  R[n][1] = a[n];
  for(int i = n - 1; i >= 1; i--) {
    if(a[i] > R[i + 1][1]) {
      R[i][0] = i; 
      R[i][1] = a[i];
    } else {
      R[i][0] = R[i + 1][0];
      R[i][1] = R[i + 1][1];
    }
  }
  //////////////////////////////////////////////
 
  //cross swap
  int mn = a[1], j = 1;
  for(int i = 1; i < n; i++) {
      if(a[i] < mn) {
          mn = a[i];
          j = i;
      }
      int rIdx = R[i + 1][0], rval = R[i + 1][1];
      if(p[i] - a[j] + rval > maxSum) {
          maxSum = p[i] - a[j] + rval;
          ans1 = j;
          ans2 = rIdx;
      }
  }
  
  
  tree[0] = {0, n, INF, INF, -1, -INF, -1};
  build1(0);
  for(int i = 2; i < n; i++) {
      int rIdx = R[i + 1][0], rval = R[i + 1][1];
      int v = a[i];
      update(0, 1, i - 1, v, i);
      auto pa = query(0, 1, i - 1);
      if(p[i] - pa.lval - pa.rMin + rval > maxSum) {
          maxSum = p[i] - pa.lval - pa.rMin + rval;
          ans1 = pa.rIdx;
          ans2 = rIdx;
      }
  }
  
  
  //max
  L[1][0] = 1;
  L[1][1] = a[1];
  for(int i = 2; i <= n; i++) {
    if(a[i] > L[i - 1][1]) {
      L[i][0] = i;
      L[i][1] = a[i];
    } else {
      L[i][0] = L[i - 1][0];
      L[i][1] = L[i - 1][1];
    }
  }
  
  tree[0] = {0, n, INF, INF, -1, -INF, -1};
  build(0);
  //swap inside [1 : i]
  //auto ppa = query(0, 1, 3);
 // cout << "begore "  << "   | " << ppa.lIdx << "  " << ppa.lval << " " << ppa.rMin <<"  " << ppa.rIdx << endl;
  
  for(int i = 2; i <= n; i++) {
    int v = a[i];
    update(0, 1, i - 1, v, i);
    auto pa = query(0, 1, i - 1);
    int lIdx = pa.lIdx, rIdx = pa.rIdx;
    if(maxSum < p[i] - (pa.lval + pa.rMin)) {
      maxSum = p[i] - (pa.lval + pa.rMin);
      ans1 = lIdx;
      ans2 = rIdx;
    }
    

   // cout << "loop   " << i << endl;
    /*if(maxSum == 15) {
        auto ppa = query1(0, 1, i - 1);
        cout << "gg " << i << "   | " << ppa.lIdx << "  " << ppa.lval << " " << ppa.rIdx << "  " << ppa.rMin <<"  " << endl;
   
        cout << p[i] << "  "  <<  (pa.lval + pa.rMin) << endl;
    }*/
  }
  
  //cout << endl;
  cout << maxSum << endl;
  cout << ans1 << " " << ans2 << endl;

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


/*
7
1 -5 -3 3 1 -2 10

7
1 3 -3 3 5 -2 10

7
1 2 -2 -3 -4 5 6

7
3 2 -2 -10 5 -10 7



8
1 1 1 1 -9 -2 -3 0


9
1 2 -3 -4 5 6 -2 -1 3

*/
