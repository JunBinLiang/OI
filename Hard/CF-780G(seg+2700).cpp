#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>


using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector



struct Line {
    int u, l, r, s;
};

bool COMP(Line& l1, Line& l2) {
    return l1.u > l2.u;
}


const int mod = 1e9 + 7;
const int N = 1e5 + 100;
int tot = 0;
int w, h, n;

vector<Line> a;
vector<pair<int, int>> stks[N];

struct Node {
  int l, r;
  int mn, idx;
} tr[N * 4];

void build(int id) {
    int l = tr[id].l, r = tr[id].r;
    if(l == r) {
        stks[l].push_back({h + 1, 1});
        tr[id].mn = h + 1;
        tr[id].idx = l;
        return;
    }
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    tr[left] = {l, mid, -1, -1};
    tr[right] = {mid + 1, r, -1, -1};
    build(left);
    build(right);
    tr[id].mn = h + 1;
    tr[id].idx = l;
}


//single update
void update(int id, int idx, int op, int row, int cnt) { 
    int l = tr[id].l, r = tr[id].r;
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    
    if(l == r) {
        if(op == 0) {
            //delete
            int cnt = stks[l].back().second; stks[l].pop_back();
            tot += cnt;
            tot %= mod;
            if(stks[l].size() == 0) {
                tr[id].idx = -1;
                tr[id].mn = 2e9;
            } else {
                tr[id].mn = stks[l].back().first;
                tr[id].idx = l;
            }
        } else {
            //inserrt
            stks[l].push_back({row, cnt});
            tr[id].mn = row;
            tr[id].idx = l;
            //cout << "update  " << l << " " << cnt << endl;
        }
        return;
    }
    if(idx <= mid) {
        update(left, idx, op, row, cnt);
    } else if(idx >= mid + 1) {
        update(right, idx, op, row, cnt);
    } 

    if(tr[left].mn < tr[right].mn) {
        tr[id].mn = tr[left].mn;
        tr[id].idx = tr[left].idx;
    } else {
        tr[id].mn = tr[right].mn;
        tr[id].idx = tr[right].idx;
    }
}

pair<int,int> query(int id, int s, int e) {
    int l = tr[id].l, r = tr[id].r;
    if(l == s && r == e){
        return {tr[id].mn, tr[id].idx};
    }

    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    if(e <= mid){
        return query(left, s, e);
    } else if(s >= mid + 1) {
        return query(right, s, e);
    } else {
        pair<int, int> p1 = query(left, s, mid);
        pair<int, int> p2 = query(right, mid + 1, e);
        if(p1.first < p2.first) {
            return p1;
        } else {
            return p2;
        }
    }
}



void solve() {
    scanf("%d%d%d", &h, &w, &n);

    for(int i = 0; i < n; i++) {
        int u, l, r, s;
        scanf("%d%d%d%d", &u, &l, &r, &s);
        a.push_back({u, l, r, s});
    }
    
    sort(a.begin(), a.end(), COMP);
    tr[0] = {0, w - 1, -1 , -1};
    build(0);

    for(int i = 0; i < a.size(); i++) {
        int row = a[i].u, l = a[i].l, r = a[i].r, s = a[i].s;   
    
        l--; r--;
        tot = 0;
        while(true) {
            pair<int, int> p = query(0, l, r);
            if(p.first > min(row + s, h + 1)) break;
            int idx = p.second;
            update(0, idx, 0, -1, -1);
        }

        if(tot > 0) {
            if(l == 0) {
                update(0, r + 1, 1, row, (2 * tot) % mod);
            } else if(r == w - 1) {
                update(0, l - 1, 1, row, (2 * tot) % mod);
            } else {
                update(0, l - 1, 1, row, tot);
                update(0, r + 1, 1, row, tot);
            }
        }
        
        //cout <<"query  : " << row << " " << l << " " << r << "  " << row + s << endl;
        //cout << tot <<endl << endl;
    }

    ll res = 0;
    for(int i = 0; i < w; i++) {
        ll sum = 0;
        while(stks[i].size() > 0) {
            sum += stks[i].back().second;
            stks[i].pop_back();
        }
        res += sum;
        res %= mod;
       // cout <<i << "  " << sum << endl;
    }
    cout << res << endl;

}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
