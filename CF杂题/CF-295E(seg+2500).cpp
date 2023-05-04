
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

const int N = 1e5 + 10;
int a[N], b[N];
int n, m;

struct Q {
    int op, x, y;
} q[N];

int id = 0;
map<int, int> f;


const int MAX = 300000 + 10;
struct Node {
    int l, r;
    ll sum = 0;
    int cnt = 0;
    ll ans = 0;
} tr[MAX * 4];

void build(int id) {
    int l = tr[id].l, r = tr[id].r;
    if(l == r) {
        return;
    }
    int mid = l + (r - l) / 2;
    tr[id * 2 + 1] = {l, mid, 0, 0, 0};
    tr[id * 2 + 2] = {mid + 1, r, 0, 0, 0};
    build(id * 2 + 1);
    build(id * 2 + 2);
}

void update(int id, int index, int val, int cnt) { 
    int l = tr[id].l, r = tr[id].r;
    if(l == r) {
        tr[id].sum += (val * cnt); 
        tr[id].cnt += cnt;
        return;
    }

    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    if(index <= mid) {
        update(left, index, val, cnt);
    } else {
        update(right, index, val, cnt);
    }
    
    //(a, b, c, d)   (A, B)
    //(A - a, A - b, A - c, A - d)
    //(B - a, B - b, B - c, B - d)
    tr[id].ans = tr[left].ans + tr[right].ans;
    ll cross = (tr[right].sum * tr[left].cnt - tr[left].sum * tr[right].cnt);
    tr[id].ans += cross;
    
    tr[id].cnt = tr[left].cnt + tr[right].cnt;
    tr[id].sum = tr[left].sum + tr[right].sum;
    
    //cout << l << "  " << r << "  " << tr[id].ans << endl;
}

struct Tu {
    ll first, second, third;
};

Tu query(int id, int s, int e) { // query sum from [0 : l]
    int l = tr[id].l, r = tr[id].r;
    if(l == s && r == e){
        return {tr[id].ans, tr[id].sum, tr[id].cnt};
    }
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    if(e <= mid){
        return query(left, s, e);
    } else if(s >= mid + 1) {
        return query(right, s, e);
    } else {
        Tu p1 =  query(left, s, mid);
        Tu p2 =  query(right, mid + 1, e);
        ll ans = p1.first + p2.first;
        ll cross = (p2.second * p1.third - p1.second * p2.third);
        
        //cout << l << "  " << r << "  |" << ans + cross << " " << p1.second + p2.second << " " << p1.third + p2.third << endl;
        
        return {ans + cross, p1.second + p2.second, p1.third + p2.third};
    }
}

void solve() {
    scanf("%d", &n);
    vector<int> all;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
        all.push_back(a[i]);
    }
    
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &q[i].op, &q[i].x, &q[i].y);
        if(q[i].op == 1) {
            b[q[i].x - 1] += q[i].y;
            all.push_back(b[q[i].x - 1]);
        } else {
            all.push_back(q[i].x);
            all.push_back(q[i].y);
        }
    }
    
    sort(all.begin(), all.end());
    for(int x : all) {
        if(f.find(x) != f.end()) continue;
        f[x] = id++;
    }
    
    tr[0] = {0, id, 0, 0, 0};
    build(0);

    for(int i = 0; i < n; i++) {
        update(0, f[a[i]], a[i], 1);
    }
    
    for(int i = 0; i < m; i++) {
        int op = q[i].op;
        if(op == 1) {
            int j = q[i].x - 1;
            int d = q[i].y;
            update(0, f[a[j]], a[j], -1);//delete
            a[j] += d;
            update(0, f[a[j]], a[j], 1); //add
        } else {
            int l = f[q[i].x], r = f[q[i].y];
            ll ans = query(0, l, r).first;
            cout <<  ans << endl;
        }
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
