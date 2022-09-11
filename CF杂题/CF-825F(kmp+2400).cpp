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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}


const int N = 8050;
const int INF = 1e9;
int dp[N];
int a[N][N];
string s;

int get(int x) {
  int res = 0;
  while(x) res ++, x /= 10;
  return res;
}

vector<int> kmp(string& pattern){
  vector<int> pre(pattern.size());
  int l = 0,r = 1;
  while(r < pattern.size()){
    if(pattern[r] == pattern[l]){
      pre[r] = l + 1;
      l++;
      r++;
    }else{
      if(l == 0)r++;
      else{
            l = pre[l-1];
          }
    }
  }
  return pre;
}

int main() {
    cin >> s;
    int n = s.size();

    for(int i = 0; i < n; i++) {
      for(int j = i; j < n; j++) {
        a[i][j] = 1e8;
      }
    }

    for(int i = 0; i < n; i++) {
      string t = s.substr(i, s.size() - i);
      vector<int> pre = kmp(t);
      for(int j = i; j < n; j++) {
        if(i == j) {
          a[i][j] = 2;
          continue;
        }
        
        int sz = j - i + 1;
        int l = sz - pre[j - i];
        if(sz % l == 0) {
          a[i][j] = l + get(sz / l);
        } else {
            a[i][j] = 1 + sz;
        }
      }
    }
    
    for(int i = 0; i < n; i++) dp[i] = INF;
    for(int i = 0; i < n; i++) {
      for(int j = i; j >= 0; j--) {
        if(j == 0) {
          dp[i] = min(dp[i], a[j][i]);
        } else {
          dp[i] = min(dp[i], dp[j - 1] + a[j][i]);
        }
      }
    }
    
    cout << dp[n - 1] << endl;
    return 0;
}   
