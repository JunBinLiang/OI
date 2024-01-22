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

const int N = 19;
int p[26], rk[1 << N], nums1[1 << N], nums2[1 << N], nums3[1 << N];

bool COMP(pair<int, int>& p1, pair<int, int>& p2) {

}

void solve() {
  int n;
  string s;
  cin >> n >> s;

  memset(p, 0, sizeof p);
  memset(nums1, 0, sizeof nums1);
  memset(nums2, 0, sizeof nums2);

  //sort based on the first character
  for(int i = 0; i < s.size(); i++) p[s[i] - 'a']++;
  for(int i = 1; i < 26; i++) p[i] += p[i - 1];
  for(int i = 0; i < s.size(); i++) {
    int c = s[i] - 'a';
    nums1[i] = c;
    rk[--p[c]] = i; 
  }


  for(int i = 0; i < n; i++) {
    int l = 1 << i, r = l * 2 - 1;

    vector<int> v(s.size());
    for(int j = 0; j < s.size(); j++) v[j] = j;
    for(int j = 0; j < s.size(); j++) nums2[j] = nums1[j ^ (1 << i)];
    
    sort(v.begin(), v.end(), [](const int& x, const int& y) -> bool {
      if(nums1[x] == nums1[y]) {
        return nums2[x] < nums2[y];
      }
      return nums1[x] < nums1[y];
    });

    //离散化
    int id = 0;
    for(int j = 0; j < v.size(); j++) {
      rk[j] = v[j];
      if(j) {
        if(nums1[v[j]] == nums1[v[j - 1]] && nums2[v[j]] == nums2[v[j - 1]]) {
          nums3[v[j]] = id;
        } else {
          nums3[v[j]] = ++id;
        }
      } else {
        nums3[v[j]] = id;
      }
    }
    for(int j = 0; j < v.size(); j++) nums1[j] = nums3[j];
  }

  string ans = "";
  for(int i = 0; i < (1 << n); i++) {
    ans += s[i ^ rk[0]];
  }
  cout << ans << endl;

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
