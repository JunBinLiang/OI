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


//2 : 35 - 3: 30
void solve() {
    int n;
    string s, t;
    cin >> n;
    cin >> s >> t;
    string tt = t;
    if(s == t) {
        cout << "YES" << endl;
        return;
    }
    reverse(tt.begin(), tt.end());
    vector<int> cnt(26);
    for(char c : s) cnt[c - 'a']++;
    for(char c : tt) cnt[c - 'a']++;
    for(int i : cnt) {
        if(i % 2 == 1) {
            cout << "NO" << endl;
            return;
        }
    }

    map<pair<int, int>, int> f;
    for(int i = 0; i < n; i++) {
        int c1 = s[i], c2 = tt[i];
        pair<int, int> p = {min(c1,c2), max(c1,c2)};
        f[p]++;
    }
    
    int odd = 0;
    for(auto it = f.begin(); it != f.end(); it++) {
        if((it -> second) % 2 == 1) odd++;
    }

    if(n % 2 == 1) {
        if(odd != 1) cout << "NO" << endl;
        else cout << "YES" << endl;
    } else {
        if(!odd) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
//abcaa   
//bbabc

//cbbaa
//cbbaa

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
