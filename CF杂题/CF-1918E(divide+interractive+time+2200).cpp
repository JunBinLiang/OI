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
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 2010;
int ans[N], n;
int curX = -1;

void output() {
  cout << "! ";
  for(int i = 1; i <= n; i++) {
    cout << ans[i];
    if(i < n) cout << " ";
  }
  cout << endl;
  cout.flush();
}

int c = 0;
vector<char> seq;
vector<int> per = {0, 2, 4, 1, 5, 3};
int ask(int i) {
  cout << "? " << i << endl;
  cout.flush();
  char c;
  cin >> c;
  if(c == '=') {
      return 0;
  }
  else if(c == '>') {
      curX++;
      return 1;
  }
  curX--;
  return 2;
  /*
  if(curX == per[i]) {
      seq.push_back('=');
      return 0;
  }
  else if( per[i] > curX) {
      seq.push_back('>');
      curX++;
      return 1;
  }
  curX--;
  seq.push_back('<');
  return 2;*/
}

void divide(int L, int R, vector<int> p) {
  if(L == R) {
    ans[p[0]] = L;
    return;
  }

  int mid = L + (R - L) / 2;
  vector<int> left, right;
  while(true) {
    int op = ask(p[0]);
    if(op == 0) break;
  }
  

  if(curX < mid) left.push_back(p[0]);
  else if(curX > mid) right.push_back(p[0]);
  else ans[p[0]] = mid;

  for(int i = 1; i < p.size(); i++) {
      if(curX < mid) {
        while(curX < mid) {
            int op = ask(p[i]);
            if(op == 1) {
              
            } else if(op == 2) {
                ask(p[0]);
                left.push_back(p[i]);
                break;
            } else {
                left.push_back(p[i]);
                break;
            }
        }
        if(curX == mid) {
          i--;
        }
    } else if(curX > mid) {
        while(curX > mid) {
            int op = ask(p[i]);
            if(op == 2) {
              
            } else if(op == 1) {
                ask(p[0]);
                right.push_back(p[i]);
                break;
            } else {
                right.push_back(p[i]);
                break;
            }
        }
        if(curX == mid) {
          i--;
        }
    } else {
        int op = ask(p[i]);
        ask(p[0]);
        if(op == 1) right.push_back(p[i]);
        else if(op == 2) left.push_back(p[i]);
        else {
            ans[p[i]] = mid;
        }
    }
  }
  
  if(L <= mid - 1) {
    divide(L, mid - 1, left);
  }
  if(mid + 1 <= R) {
    divide(mid + 1, R, right);
  }    
}

void solve() {
  cin >> n;
  vector<int> a;
  for(int i = 1; i <= n; i++) {
    a.push_back(i);
  }

  while(true) {
      int op = ask(1);
      if(op == 0) break;
  }
  int pre = 1;
  for(int i = 2; i <= n; i++) {
    while(true) {
      int op = ask(i);
      if(op == 1) { 
        ask(pre);
        break;
      } else if(op == 2){
        pre = i;
      } else {
        break;
      }
    }
  }

  curX = 1;
  divide(1, n, a);
  output();
}


int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
