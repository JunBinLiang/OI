
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


const int MAX = 20000 + 10;
struct Node {
  int l, r;
  int sum, cnt;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].sum += val;
    tree[id].cnt ++;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].sum = tree[left].sum + tree[right].sum;
  tree[id].cnt = tree[left].cnt + tree[right].cnt;
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}

int query1(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].cnt;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    return query1(left, s, mid) + query1(right, mid + 1, e);
  }
}

int dfs(int id, int sz) {
    if(tree[id].l == tree[id].r) {
        return tree[id].l;
    }
    int left = id * 2 + 1, right = id * 2 + 2;
    if(sz > tree[left].cnt) {
        return dfs(right, sz - tree[left].cnt);
    } else {
        return dfs(left, sz);
    }
}


const int N = 2e5 + 10, INF = 2000000000 + 5;
int p1[N], p2[N];
int get(int p[], int l, int r) {
    if(l > r) return 0;
    if(l == 0) return p[r];
    return p[r] - p[l - 1];
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> v00, v01, v10, v11; 
    for(int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        if(y == 0 && z == 0) {
            v00.push_back({x, i + 1});
        } else if(y == 1 && z == 1) {
            v11.push_back({x, i + 1});
        } else if(y == 1) {
            v10.push_back({x, i + 1});
        } else if(z == 1) {
            v01.push_back({x, i + 1});
        }
    }

    sort(v00.begin(), v00.end());
    sort(v11.begin(), v11.end());
    sort(v01.begin(), v01.end());
    sort(v10.begin(), v10.end());

    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < min(v01.size(), v10.size()); i++) {
        sum1 += v01[i].first;
        sum2 += v10[i].first;
        p1[i] = sum1; 
        p2[i] = sum2;
    }

    /*tree[0] = {0, 20000, 0, 0};
    build(0);
    update(0, 5, 5);
    update(0, 5, 5);
    update(0, 5, 5);
    update(0, 5, 5);
    update(0, 6, 6);
    update(0, 6, 6);
    update(0, 3, 3);
    update(0, 3, 3);
    update(0, 2, 2);
    cout << dfs(0, 4) << endl;*/
    
    tree[0] = {0, 20000, 0, 0};
    build(0);
    for(int i = 0; i < v00.size(); i++) {
        update(0, v00[i].first, v00[i].first);
    }


    int mn = INF, take = -1;
    int idx1 = v01.size() - 1, idx2 = v10.size() - 1;

    int x = 0;
    for(int i = 0; i < min(m, (int)(v11.size())); i++) {
        x += v11[i].first;
        int need = (k - i - 1);
        need = max(need, 0);
        
        if(need <= min(v01.size(), v10.size())) {
            int y = get(p1, 0, need - 1) + get(p2, 0, need - 1);
            
            while(idx1 >= need) {
                update(0, v01[idx1].first, v01[idx1].first);
                idx1--;
            }
            while(idx2 >= need) {
                update(0, v10[idx2].first, v10[idx2].first);
                idx2--;
            }
                
            int z = 0;
            int ith = -1;
            if(m - (i + 1 + need * 2) >= 0) {
                if(m - (i + 1 + need * 2) == 0) {
                    ith = 0;
                } else {
                    int tot = query1(0, 0, 12000);
                    if(tot >= m - (i + 1 + need * 2)) {
                        ith = dfs(0, m - (i + 1 + need * 2));
                        z = query(0, 0, ith);
                        int all = query1(0, 0, ith);
                        z -= ((all - (m - (i + 1 + need * 2))) * ith);
                    }
                }
            }
            if(x + y + z < mn && ith != -1) {
                mn = x + y + z;
                take = i + 1;
                    
                //cout << idx1 << " " << idx2 << endl;
                //cout << mn << "  " << i + 1 << "   |" << x << " " << y << " " << z << endl;
                  // cout << "need  " << m - (i + 1 + need * 2) <<"    " << ith << endl;
                //cout << endl;
            }
            
        }
    }
    

    //no 11
    if(min(v01.size(), v10.size()) >= k && m >= k + k) {
        int sum = 0;
        for(int i = 0; i < k; i++) {
            sum += (v01[i].first + v10[i].first);
        }
        
        vector<pair<int, int>> c;
        for(int i = k; i < v01.size(); i++) c.push_back(v01[i]);
        for(int i = k; i < v10.size(); i++) c.push_back(v10[i]);
        for(int i = 0; i < v00.size(); i++) c.push_back(v00[i]);
        sort(c.begin(), c.end());
        if(c.size() >= m - k - k) {
            for(int i = 0; i < m - k - k; i++) {
                sum += c[i].first;
            }
            
            if(sum < mn) {
                cout << sum << endl;
                for(int i = 0; i < k; i++) {
                    cout << v01[i].second << " ";
                }
                for(int i = 0; i < k; i++) {
                    cout << v10[i].second << " ";
                }
                for(int i = 0; i < m - k - k; i++) {
                    cout << c[i].second << " ";
                }
                cout << endl;
                return;
            }
        }
    }

    if(take == -1) {
        cout << -1 << endl;      
        return;
    }

    cout << mn << endl;

    for(int i = 0; i < take; i++) {
        cout << v11[i].second << " ";
    }
    for(int i = 0; i < max(k - take, 0); i++) {
        cout << v01[i].second << " ";
    }
    for(int i = 0; i < max(k - take, 0); i++) {
        cout << v10[i].second << " ";
    }
    vector<pair<int, int>> c;
    for(int i = max(k - take, 0); i < v01.size(); i++) c.push_back(v01[i]);
    for(int i = max(k - take, 0); i < v10.size(); i++) c.push_back(v10[i]);
    for(int i = 0; i < v00.size(); i++) c.push_back(v00[i]);
    sort(c.begin(), c.end());
    for(int i = 0; i < m - (take + (max(0, k - take)) * 2); i++) {
        cout << c[i].second << " ";
    }
    cout << endl;

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
