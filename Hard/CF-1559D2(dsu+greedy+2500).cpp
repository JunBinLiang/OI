
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


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}


int find(int p[], int x) {
    if(p[x] == x) {
        return x;
    }
    return p[x] = find(p, p[x]);
}

const int N = 1e5 + 10;
int p1[N], p2[N];
vector<pair<int, int>> res;
void solve() {
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    
    for(int i = 0; i < N; i++) p1[i] = p2[i] = i;
    
    for(int i = 0; i < m1; i++) {
        int u, v;
        cin >> u >> v;
        p1[find(p1, u)] = find(p1, v);
    }
    
    for(int i = 0; i < m2; i++) {
        int u, v;
        cin >> u >> v;
        p2[find(p2, u)] = find(p2, v);
    }
    
    for(int i = 1; i <= n; i++) {
        if(find(p1, 1) != find(p1, i) && find(p2, 1) != find(p2, i)) {
            res.push_back({1, i});
            p1[find(p1, i)] = find(p1, 1);
            p2[find(p2, i)] = find(p2, 1);
        }
    }
    
    vector<int> b, c;
    for(int i = 1; i <= n; i++) {
        if(find(p1, i) != find(p1, 1) && p1[i] == i) b.push_back(i);
        if(find(p2, i) != find(p2, 1) && p2[i] == i) c.push_back(i);
    }
    
    int i = 0, j = 0;
    while(i < b.size() && j < c.size()) {
        res.push_back({b[i], c[j]});
        i++;
        j++;
    }
    
    
    cout << res.size() << endl;
    for(auto p : res) {
        cout << p.first << " " << p.second << endl;
    }
}   


int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}

