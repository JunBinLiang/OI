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
using namespace std;
 
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

 
ifstream fcin("digit.in");
ofstream fcout("digit.out");

void divideByTwo(string& num) {
  string res = "";
  int add = 0;
  for(int i = 0; i < num.size(); i++) {
    int d = num[i] - '0' + add * 10;
    int v = d / 2;
    if(v == 0) {
      if(res.size() != 0) res += "0";
    } else {
      res += to_string(v);
    }
    add = d % 2;
  }
  num = res;
}

vector<int> convert(string& num) {
  vector<int> res;
  while(num.size() > 0) {
    if((num.back() - '0') % 2 == 1) {
      res.push_back(1);
    } else {
      res.push_back(0);
    }
    divideByTwo(num);
  }
  return res;
}


string sum(string& s, string& t) {
  if(s.size() > t.size()) return sum(t, s);
  string num1 = s, num2 = t;
  reverse(num1.begin(), num1.end());
  reverse(num2.begin(), num2.end());
  
  int n = num1.size(), m = num2.size();
  string res = "";
  int up = 0;
  for(int i = 0; i < n; i++) {
    int d1 = num1[i] - '0', d2 = num2[i] - '0';
    int x = (d1 + d2 + up);
    up = x / 10;
    res += to_string(x % 10);
  }

  for(int i = n; i < m; i++) {
    int d = num2[i] - '0';
    d += up;
    up = d / 10;
    res += to_string(d % 10);
  }
  if(up > 0) res += "1";
  reverse(res.begin(), res.end());
  return res;
}

struct BIGNUM {
  string num;
  bool ok = false;
  void init(string _num) {
    num = _num;
    ok = true;
  }

  void add(BIGNUM& other) {
    num = sum(num, other.num);
  }
} dp[1100][4];

void solve() {
  string num;
  fcin >> num;
  vector<int> bin = convert(num);
  reverse(bin.begin(), bin.end());

  dp[0][0].init("0");
  dp[0][1].init("1");
  dp[0][2].init("0");
  dp[0][3].init("0");

  for(int i = 1; i < bin.size(); i++) {
    int d = bin[i];
    dp[i][0].init("0");
    dp[i][1].init("0");
    dp[i][2].init("0");
    dp[i][3].init("0");

    if(d == 0) {
      dp[i][0].add(dp[i - 1][0]);
      dp[i][0].add(dp[i - 1][1]);
      dp[i][0].add(dp[i - 1][2]);
      dp[i][2].add(dp[i - 1][1]);
      dp[i][2].add(dp[i - 1][2]);
      dp[i][2].add(dp[i - 1][3]);
      
    } else {
      dp[i][1].add(dp[i - 1][0]);
      dp[i][1].add(dp[i - 1][1]);
      dp[i][1].add(dp[i - 1][2]);
      
      dp[i][3].add(dp[i - 1][1]);
      dp[i][3].add(dp[i - 1][2]);
      dp[i][3].add(dp[i - 1][3]);
    }
  }

  dp[bin.size() - 1][0].add(dp[bin.size() - 1][1]);
  dp[bin.size() - 1][0].add(dp[bin.size() - 1][2]);
  fcout << dp[bin.size() - 1][0].num << endl;
  
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
