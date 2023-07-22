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
 
 
bool stop = false;
map<char, int> f;
set<int> sets[3];

int normal(vector<int>& k) {
    int g = 0;
    for(int x : k) {
        if(x == 0) continue;
        if(g == 0) g = x;
        else g = __gcd(g, x);
    }

    if(g != 0) {
        for(int& x : k) {
            x /= g;
        }
    }
    return g;
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    if(n == 0 && m == 0) {
        stop = true;
        return;
    }

    vector<string> a(n), b(m);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < 3; i++) sets[i].clear();

    vector<int> cnt(3, 0);
    vector<vector<int>> mat;

    for(int i = 0; i < n; i++) {
        string& s = a[i];
        int space = 0;
        for(char& c : s) {
            if(c == '.') space++;
            else break;
        }

        vector<int> c(cnt.begin(), cnt.end());
        c.push_back(space);
        mat.push_back(c);
        //cout << c << endl;

        for(char& c : s) {
            if(f.find(c) == f.end()) continue;
            int j = f[c];
            if(j < 3) cnt[j]++;
            else cnt[j - 3] --;
        }
    }

    for(int x = 1; x <= 20; x++) {
        for(int y = 1; y <= 20; y++) {
            for(int z = 1; z <= 20; z++) {
                bool ok = true;
                for(auto& p : mat) {
                    int s = p[0] * x + p[1] * y + p[2] * z;
                    if(s != p[3]) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    sets[0].insert(x);
                    sets[1].insert(y);
                    sets[2].insert(z);
                }
            }
        }
    }

    vector<int> v(3, -1);
    for(int i = 0; i < 3; i++) {
        if(sets[i].size() == 1) {
            auto it = sets[i].begin();
            v[i] = *it;
        }
    }

    map<vector<int>, int> dp;
    for(int i = 0; i < (1 << n); i++) {
        vector<int> c(3, 0); 
        int sum = 0;
        for(int j = 0; j < n; j++) {
            if(i & (1 << j)) {
                sum += mat[j][3];
                c[0] += mat[j][0];
                c[1] += mat[j][1];
                c[2] += mat[j][2];
            }
        }
       
        int g = normal(c);
        if(g != 0 && dp.find(c) == dp.end()) {
            dp[c] = sum / g;
        }
    }
    
    //cout << endl;
   // cout << v << endl;
    

    cnt[0] = cnt[1] = cnt[2] = 0;
    vector<int> res;
    for(int i = 0; i < m; i++) {
        int sum = 0;
        bool bad = false;
        for(int j = 0; j < 3; j++) {
            if(cnt[j] != 0) {
                if(v[j] == -1) {
                    bad = true;
                } else {
                    sum += (v[j] * cnt[j]);
                }
            }
        }
        
        if(bad) sum = -1;

        vector<int> k(cnt.begin(), cnt.end());
        //cout << cnt <<" " << k << "  " << sum << endl;
        int g = normal(k);
        if(g != 0 && dp.find(k) != dp.end()) {
            sum = dp[k] * g;
        }
        //cout << k << " " << sum << endl << endl;
        res.push_back(sum);
        cin >> b[i];
        for(char& c : b[i]) {
            if(f.find(c) == f.end()) continue;
            int j = f[c];
            if(j < 3) cnt[j]++;
            else cnt[j - 3] --;
        }
    }

    for(int i = 0; i < m; i++) {
        cout << res[i];
        if(i != m - 1) cout << " ";
    }
    cout << endl;
} 
    

int main()
{
  f['('] = 0;
  f['{'] = 1;
  f['['] = 2;

  f[')'] = 3;
  f['}'] = 4;
  f[']'] = 5;

  int t = 1;
  //cin >> t;
  while(!stop) {
    solve();
  }
  return 0;
}

/*
5 4
(Follow.my.style
.........starting.from.round.brackets)
{then.curly.brackets
.....[.and.finally
.......square.brackets.]}
(Thank.you
{for.showing.me
[all
the.secrets]})
4 2
(This.time.I.will.show.you
.........(how.to.use.round.brackets)
.........[but.not.about.square.brackets]
.........{nor.curly.brackets})
(I.learned
how.to.use.round.brackets)
4 2
(This.time.I.will.show.you
.........(how.to.use.round.brackets)
.........[but.not.about.square.brackets]
.........{nor.curly.brackets})
[I.have.not.learned
how.to.use.square.brackets]
2 2
(Be.smart.and.let.fear.of
..(closed.brackets).go)
(A.pair.of.round.brackets.enclosing
[A.line.enclosed.in.square.brackets])
1 2
Telling.you.nothing.but.you.can.make.it
[One.liner.(is).(never.indented)]
[One.liner.(is).(never.indented)]
2 4
([{Learn.from.my.KungFu
...}])
((
{{
[[
]]}}))
1 2
Do.not.waste.your.time.trying.to.read.from.emptiness
(
)
2 3
({Quite.interesting.art.of.ambiguity
....})
{
(
)}
2 4
({[
............................................................]})
(
{
[
]})
0 0
*/
