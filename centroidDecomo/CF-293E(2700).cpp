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
 
 
using namespace std;  
using ll = long long;
#define pb push_back

 
//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

namespace Fenwick1 {
  const int SIZE = 100000 + 100;
  int tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}

const int N = 1e5 + 10, M = N * 2;
int h[N], e[M], w[M], ne[M], idx = 0;
bool st[N];
int n, l, k;

void add(int a, int b, int c) {
  e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int get_wc(int fa, int u, int tot, int& wc) { // 求重心
    if (st[u]) return 0;
    int sum = 1, ms = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(u, j, tot, wc);
        ms = max(ms, t);
        sum += t;
    }
    ms = max(ms, tot - sum);
    if (ms <= tot / 2) wc = u;
    return sum;
}

int get_size(int u, int fa) { // 求子树大小
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        if (e[i] != fa) res += get_size(e[i], u);
    }            
    return res;
}

void dfs(vector<pair<int, ll>>& a, int fa, int u, int len, ll weight) {
    if(st[u]) return;
    a.push_back({len, weight});
    for(int i = h[u]; ~i; i = ne[i]) {
        if(e[i] == fa) continue;
        dfs(a, u, e[i], len + 1, weight + w[i]);
    }
}

bool COMP(pair<int, ll>& p1, pair<int, ll>& p2) {
    if(p1.second == p2.second) {
        return p1.first < p2.first;
    }
    return p1.second < p2.second;
}

ll get(vector<pair<int, ll>>& a) {
    sort(a.begin(), a.end(), COMP);
    
    /*cout << "get   " << endl;
    for(pair<int, ll>& p : a) {
        cout << p.first << " " << p.second << endl;
    }*/
    
    ll res = 0;
    for(int i = 0; i < a.size(); i++) {
        Fenwick1 :: update(a[i].first, 1);
    }

    //l1 + x <= l
    //x <= l - l1
    int left = 0, right = a.size() - 1;
    while(left <= right) {
        if(a[left].second + a[right].second > k) {
            Fenwick1 :: update(a[right].first, -1);
            right--;
        } else {
            Fenwick1 :: update(a[left].first, -1);
            int o = a[left].first;
            if(l - o >= 0) {
                res += Fenwick1 :: query(0, l - o);
            }
            left++;
        }
    }
    
    for(int i = 0; i < a.size(); i++) {
        int idx = a[i].first;
        int t = Fenwick1 :: query(idx, idx);
        if(t != 0) {
            Fenwick1 :: update(idx, -t);
        }
    }
    return res;
}

ll calc(int u) {
    if (st[u]) return 0;
    ll res = 0;
    get_wc(-1, u, get_size(u, -1), u);
    st[u] = true;  // 删除重心
    
    vector<pair<int, ll>> all;
    for (int i = h[u]; ~i; i = ne[i]) {
        vector<pair<int, ll>> a;
        dfs(a, -1, e[i], 1, w[i]);
        res -= get(a);
        for(pair<int, ll>& p : a) {
            if(p.first <= l && p.second <= k) {
                all.push_back(p);
                res++;
            }
        }
    }
    
    //cout << "all   " << u << endl;
     //for(pair<int, ll>& p : all) {
        //cout << p.first << " " << p.second << endl;
    //}
    
    res += get(all);

    //分治理
    for (int i = h[u]; ~i; i = ne[i]) res += calc(e[i]);
    return res;
}


void solve() {
    memset(st, false, sizeof st);
    memset(h, -1, sizeof h);
    idx = 0;
    Fenwick1 :: init();

    scanf("%d%d%d", &n, &l, &k);
    for(int i = 1; i <= n - 1; i++) {
        int pi, w;
        scanf("%d%d", &pi, &w);
        //cout << i + 1 - 1 << "   " << pi - 1 << endl;
        add(i + 1 - 1, pi - 1, w);
        add(pi - 1, i + 1 - 1, w);
    }

    ll res = calc(0);
    cout << res << endl;
} 


int main() {
	// your code goes here
	int t = 1;
	//cin >> t;
	while(t--) {
	    solve();
	}
	return 0;
}
