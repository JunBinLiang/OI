using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector

vector<int> a, b;

const int N = 2e5 + 10;
struct Node {
    int l, r;
    int sum = 0;
    int setTo = 0; 
} tr[N * 4];

void build(int id) {
    int l = tr[id].l, r = tr[id].r;
    if(l == r) {
        tr[id].sum = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    tr[left] = {l, mid, 0, 0};
    tr[right] = {mid + 1, r, 0, 0};
    build(left);
    build(right);
    tr[id].sum = tr[left].sum + tr[right].sum;
}

void update(int id, int s, int e, int val) { 
    int l = tr[id].l, r = tr[id].r;
    if(l == s && r == e) {
        tr[id].setTo ^= val;
        tr[id].sum = (r - l + 1) - tr[id].sum;
        return;
    }

    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;

    if(tr[id].setTo != 0) {
        update(left, tr[left].l, tr[left].r, tr[id].setTo);
        update(right, tr[right].l, tr[right].r, tr[id].setTo);
        tr[id].setTo = 0;
    }

    if(e <= mid) {
        update(left, s, e, val);
    } else if(s >= mid + 1) {
        update(right, s, e, val);
    } else {
        update(left, s, mid, val);
        update(right, mid + 1, e, val);
    }
    tr[id].sum = tr[left].sum + tr[right].sum;
}

int query(int id, int s, int e) {
    int l = tr[id].l, r = tr[id].r;
    if(l == s && r == e){
        return tr[id].sum;
    }
    int mid = l + (r - l) / 2;
    int left = id * 2 + 1, right = id * 2 + 2;
    if(tr[id].setTo != 0) {
        update(left, tr[left].l, tr[left].r, tr[id].setTo);
        update(right, tr[right].l, tr[right].r, tr[id].setTo);
        tr[id].setTo = 0;
    }
    if(e <= mid){
        return query(left, s, e);
    } else if(s >= mid + 1) {
        return query(right, s, e);
    } else {
        return query(left, s, mid) + query(right, mid + 1, e);
    }
}

//10:05
class Solution {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<ll> res;
        a = nums1;
        b = nums2;
        int n = a.size();

        tr[0] = {0, n - 1, 0, 0};
        build(0);
        
        ll tot = 0;
        for(int i : b) {
            tot += i;
        }
        
        for(vector<int>& q : queries) {
            int ty = q[0];
            if(ty == 1) {
                int l = q[1], r = q[2];
                update(0, l, r, 1);
            } else if(ty == 2) {
                int p = q[1];
                int all = query(0, 0, n - 1);
                tot = tot + (all + 0ll) * p;
            } else {
                res.push_back(tot);
            }
        }
        return res;
    }
};
