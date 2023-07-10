#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
 
using ll = long long;
using namespace std;


vector<int> kmp(string& pattern){
  vector<int> pre(pattern.size());
  int l=0, r = 1;
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

int kmpMatch(string& pa, string& t) {
  vector<int> p = kmp(pa);
  int i = 0, j = 0;
  while(i < t.size()) {
    if(pa[j] == t[i]) {
      i++; j++;
    } else {
      if(j == 0) i++;
      else {
        j = p[j - 1];
      }
    }
    if(j >= pa.size()) {
      return i - pa.size();
    }
  }
  return -1;
}

void solve() {
  int n; string s, t;
  cin >> n >> t >> s;


  for(int d = -25; d <= 25; d++) {
    string v = "";
    for(int i = 0; i < t.size(); i++) {
      int c = s[i] - 'a';
      c -= d;
      c += 26;
      c %= 26;
      v += ((char)(c + 'a'));
    }
    
    v += v;
    int p = kmpMatch(t, v);
    if(p != -1) {
      cout << "Success" << endl;
      cout << p << " " << d << endl;
      return;
    }
  }

  cout << "Impossible" << endl;
}

int main() {
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
