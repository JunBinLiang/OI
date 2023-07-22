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
 
const int INF = 1e9;
int ask(int x, int y) {
    cout << x << " " << y << endl;
    string s;
    cin >> s;
    if(s == "black") {
        return 0;
    } else {
        return 1;
    }
}

void solve() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << "0 10" << endl;
        string s;
        cin >> s;
        cout << "0 9 1 9" << endl;
        return;
    }
    

    int c = ask(0, 0);
    int pc = c;
    
    int x = 0, y = 0;
    int half = (INF) / 2;
    y += (half);
    half /= 2;
    
    for(int i = n - 1; i >= 2; i--) {
        int cc = ask(x, y);
        if(cc == c) {
            if(i > 2) {
                y += half;   
            }
        } else {
            if(i > 2) {
                y -= half;
            }
        }
        half /= 2;
        pc = cc;
    }
    
    //cout << "gg " << x << " " << y << endl;
    
    if(pc == c) {
        int cc = ask(x + 1, y + 1);
        if(cc != pc) {
            cout << x << " " << y + 1 << " " << x + 1 << " " << y << endl;
        } else {
            cout << x << " " << y + 2 << " " << x + 1 << " " << y + 2 << endl;
        }
    } else {
        int cc = ask(x + 1, y - 1);
        //cout << "gg " << cc << " " << c << endl;
        if(cc != pc) {
            cout << x << " " << y - 1 << " " << x + 1 << " " << y << endl;
        } else {
            cout << x << " " << y - 2 << " " << x + 1 << " " << y - 2 << endl;
        }
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

