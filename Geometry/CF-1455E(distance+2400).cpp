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

pair<int, int> seg(int a, int b) {
  return {min(a, b), max(a, b)};
}

pair<int, int> getLen(pair<int, int> p1, pair<int, int> p2) {
  if(p1.first > p2.first) swap(p1, p2);
  if(p2.first > p1.second) {
    return {p2.first - p1.second, p2.second - p1.first};
  } else { 
    return {0, p2.second - p1.first};
  }
}

void solve() {

  vector<pair<int, int>> a(4);
  for(int i = 0; i < 4; i++) {
    cin >> a[i].first >> a[i].second;
  }
  
  vector<int> id = {0, 1, 2, 3};

  ll ans = 2e18;
  do {
    int ax = a[id[0]].first, bx = a[id[1]].first, cx = a[id[2]].first, dx = a[id[3]].first;
    int ay = a[id[0]].second, by = a[id[1]].second, cy = a[id[2]].second, dy = a[id[3]].second;
    ll xdis = (max(ax, bx) - min(ax, bx)) + (max(cx, dx) - min(cx, dx));
    ll ydis = (max(ay, cy) - min(ay, cy)) + (max(by, dy) - min(by, dy));

    pair<int, int> s1 = seg(ax, bx), s2 = seg(cx, dx);
    pair<int, int> s3 = seg(ay, cy), s4 = seg(by, dy);

    pair<int, int> L1 = getLen(s1, s2), L2 = getLen(s3, s4);
    if(L1.first > L2.first) swap(L1, L2);
    ans = min(ans, xdis + ydis + 2 * max(0, L2.first - L1.second));
  } while(next_permutation(id.begin(), id.end()));

  cout << ans << endl;
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
