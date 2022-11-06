using ll = long long;
unsigned long long seed = 131;
unsigned long long rands() { return seed = (seed << 15) + (seed << 8 ) + (seed >> 3);}

const int N = 3e4 + 100, M = 60;
typedef array<int, M> num;
num rnd[N];
bool is = false;
void init() {
    if(is) return;
    is = true;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            rnd[i][j] = rands() % 3;
        }
    }
}

num operator ^(const num &a, const num &b){
    num c;
    for(int i = 0; i < M; i++) {
        c[i] = a[i] + b[i];
        if (c[i] >= 3) c[i] -= 3;
    }
    return c;
}
bool operator ==(const num &a, const num &b){
    num c;
    for(int i = 0; i < M; i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        init();
        map<int, int> f;
        map<int, int> g;
        int idx = 0;
        for(int i : nums) {
            if(f.find(i) == f.end()) {
                g[idx] = i;
                f[i] = idx++;
            }
        }
        
        num cur;
        for(int j = 0; j < M; j++) cur[j] = 0;
        
        for(int i = 0; i < nums.size(); i++) {
            cur = cur ^ rnd[f[nums[i]]];
        }
        for(int i = 0; i <= idx; i++) {
            if(cur == rnd[i]) {
                return g[i];
            }
        }
        return -1;
    }
};
