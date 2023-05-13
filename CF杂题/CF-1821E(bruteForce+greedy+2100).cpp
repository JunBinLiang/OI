
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

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


const int N = 2e5 + 10;
int k;
string s;
int match[N];
void solve() {
    ll res = 0;

    cin >> k >> s;
    int n = s.size();

    
    for(int i = 0; i < k; i++) {
        vector<int> stk;
        vector<pair<int, int>> a;
        for(int i = 0; i < n; i++) {
            if(s[i] == '(') {
                stk.push_back(i);
            } else {
                int j = stk.back();
                stk.pop_back();
                if(stk.size() == 0) {
                    match[i] = j;
                    a.push_back({i - j + 1, i});
                }
            }
        }
        sort(a.begin(), a.end());
        pair<int, int> p = a.back();
        int idx1 = p.second, idx2 = match[idx1];
        string t = "";
        for(int i = 0; i < n; i++) {
            if(i == idx1 || i == idx2) continue;
            t += s[i];
        }
        t += "()";
        s = t;
    }

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            res += cnt;
            cnt++;
        } else {
            cnt--;
        }
    }
    cout << res << endl;
    
}

int main()
{   
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
