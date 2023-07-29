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
#include <iomanip>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

/*int ti = 1;
vector<int> cnt(3);

//1. (n - 1) to temp
//2. n to dest
//3. temp to dest

void towerOfHanoi(int n, char from_rod, char to_rod,char aux_rod)
{
    if (n == 0) {
        return;
    }
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    cnt[from_rod - 'A']--;
    cnt[to_rod - 'A']++;
    cout << "Move disk " << n << " from rod " << from_rod
         << " to rod " << to_rod << "  " << cnt << "  "<< ti++ << endl;
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}*/


//2 9 38 135 542 2079

string sub(string& s, int x) {
  string num = s;
  reverse(num.begin(), num.end());
  vector<int> res;
  int c = 0;
  for(int i = 0; i < num.size(); i++) {
    int d = num[i] - '0';
    if(i == 0) {
      if(d >= x) {
        d -= x;
      } else {
        d = (d + 10) - x;
        c = 1;
      }
    } else {
      if(d >= c) {
        d -= c;
        c = 0;
      } else {
        d = (d + 10) - c;
        c = 1;
      }
    }
    res.push_back(d);
  }

  while(res.size() > 0 && res.back() == 0) res.pop_back();
  reverse(res.begin(), res.end());
  string t = "";
  for(int i : res) t += to_string(i);
  return t;
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

string multwo(string& s) {
  return sum(s, s);
}

const int N = 310;
struct BIGNUM {
  string num;
  void init(string _num) {
    num = _num;
  }
  void add(BIGNUM& other) {
    num = sum(num, other.num);
  }
} p[N];


int n;
void solve() { 
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  cin >> n;
  p[0].init("1");
  for(int i = 1; i <= n; i++) {
    string s = multwo(p[i - 1].num);
    p[i].init(s);
  }


  n /= 3;

  if(n % 2 == 0) {
    string num1 = p[2 * n - 1].num;
    string num2 = p[n - 1].num;
    string sum1 = sum(num1, num2);
    cout << sub(sum1, 1) << endl;
  } else {
    string num1 = p[2 * n - 1].num;
    string num2 = p[n].num;
    string sum1 = sum(num1, num2);
    cout << sub(sum1, 2) << endl;
  }

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

