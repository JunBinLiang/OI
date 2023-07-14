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
 


const int N = 2e5 + 10;
int a[N], b[N];
ll p[N];
ll x;
int n; 

bool comp(int i, int j) {
  int mn1 = min(a[i], b[i]), mn2 = min(a[j], b[j]);
  return mn1 < mn2;
}

void solve() {
  cin >> n >> x;
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  for(int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }

  vector<int> c;
  for(int i = 0; i < n; i++) {
    c.push_back(i);
  }
  sort(c.begin(), c.end(), comp);
  for(int i = 0; i < n; i++) {
    p[i] = min(a[c[i]], b[c[i]]);
    if(i) p[i] += p[i - 1];
  }
  

  string res(n, '0');
  for(int i = 0; i < n; i++) {
    //take i 0
    int k = n - i; 
    if(p[k - 1] > x) continue;
    
    //take as b as much possible
    vector<pair<int, int>> d;
    priority_queue<pair<int, int>> pq1;
    priority_queue<pair<int, int>> pq2;
    bool vis[N];
    memset(vis, 0, sizeof vis);
    ll sum = 0;
    for(int j = 0; j < n; j++) {
      int idx = c[j];
      if(j < k) {
        if(a[idx] < b[idx]) { //may taks a
          pq1.push({a[idx], idx});
          pq2.push({-(b[idx] - a[idx]), idx});  
          res[idx] = '1';
        } else {
          res[idx] = '2';
        }
        sum += min(a[idx], b[idx]);
      } else {
        d.push_back({b[idx], idx});
      }
    }
    
    //cout << res << endl;

    sort(d.begin(), d.end());
    
    for(int j = 0; j < d.size(); j++) {
      auto& pa = d[j];
      int bval = pa.first, bidx = pa.second;
      while(pq1.size() > 0 && vis[pq1.top().second]) pq1.pop();
      while(pq2.size() > 0 && vis[pq2.top().second]) pq2.pop();

      if(pq1.size() > 0 && pq2.size() > 0) {
        auto top1 = pq1.top();
        auto top2 = pq2.top();
        int idx1 = top1.second, idx2 = top2.second;
        if(sum + b[idx2] - a[idx2] < sum + bval - a[idx1]) { //internal replacement
          if(sum + b[idx2] - a[idx2] <= x) {
            sum = sum + b[idx2] - a[idx2];
            res[idx2] = '2';
            vis[idx2] = true;
            j--;
          } else {
            break;
          }
        } else {
          if(sum + bval - a[idx1] <= x) { //cross replace
            sum = sum + bval - a[idx1];
            res[bidx] = '2';
            vis[bidx] = true;
            res[idx1] = '0';
            vis[idx1] = true;
          } else {
            break;
          }
        }
      } else {
        
      }
    }
    
    while(pq2.size() > 0) {
        if(vis[pq2.top().second]) pq2.pop();
        else {
            auto top = pq2.top();
            int idx = top.second;
            if(sum - a[idx] + b[idx] <= x) {
                sum = sum - a[idx] + b[idx];
                res[idx] = '2'; pq2.pop();
            } else {
                break;
            }
        }
    } 
    
    
    break;
  }

  cout << res << endl;
  
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
