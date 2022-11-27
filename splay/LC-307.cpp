const int N = 3e4 + 100, INF = 1e9;
int root, idx;
int n;
int a[N], p[N];
struct Node
{
    int s[2], p, v;
    int size, add;
    void init(int _v, int _p)
    {
        v = _v, p = _p;
        size = 1;
        add = 0;
    }
    
    void clear() {
        size = 0;
        add = 0;
        s[0] = s[1] = 0;
    }
}tr[N];

void pushdown(int u) {
    if(tr[u].add != 0) {
        tr[tr[u].s[0]].add += tr[u].add;
        tr[tr[u].s[1]].add += tr[u].add;
        p[u - 3] += tr[u].add;
        tr[u].add = 0;
    }
}

void pushup(int u) {
    tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1;
}


void rotate(int x)
{
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
}

void splay(int x, int k)
{
    while (tr[x].p != k)
    {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
        {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!k) root = x;
}

void insert(int v)
{
    int u = root, p = 0;
    while (u) p = u, u = tr[u].s[v > tr[u].v];
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(v, p);
    splay(u, 0);
}

int get_k(int k)
{
    int u = root;
    while (true)
    {
        pushdown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
    return -1;
}

class NumArray {
public:
    NumArray(vector<int>& nums) {
        for(int i = 0; i <= idx + 1; i++) {
            tr[i].clear();
        }
        
        idx = 0;
        root = 0;
        n = nums.size();
        int sum = 0;
        for(int i = 0; i < n; i++) {
            a[i] = nums[i];
            sum += a[i];
            p[i] = sum;
        }
        
        insert(-INF); 
        insert(INF);
        for(int i = 0; i < n; i++) {
            insert(i + 1);
        }
    }
    
    void update(int index, int val) {
        int old = a[index];
        int add = val - old;
        a[index] = val;
        int l = get_k(index + 1);
        splay(l, 0);
        int r = 2;
        splay(r, l);
        tr[tr[r].s[0]].add += add;
    }
    
    int sumRange(int l, int r) {
        if(l == 0) {
            get_k(r + 2);
            return p[r];
        } else {
            get_k(l + 1);
            get_k(r + 2);
            return p[r] - p[l - 1];
        }
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
