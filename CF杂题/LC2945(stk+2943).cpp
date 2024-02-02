using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N  = 1e5 + 10;
ll p[N];
ll dp[N], v[N];
ll get(int l, int r) {
    if(l > r) return 0;
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

vector<int> stks[N];

class Solution {
public:
    int findMaximumLength(vector<int>& a) {
        int n = a.size();
        for(int i = 0; i <= n; i++) {
            dp[i] = v[i] = 0;
            stks[i].clear();
        }
        for(int i = 0; i < n; i++) {
            p[i] = a[i];
            if(i) p[i] += p[i - 1];
        }
        
        int ans = 0;
        vector<int> stk;
        for(int i = 0; i < n; i++) {
            if(i == 0) {
                dp[i] = 1;
                v[i] = a[i];
                stk.push_back(i);
                stks[dp[i]].push_back(i);
            } else {
                int maxCnt = dp[stk.back()];
                int l = 0, r = stks[maxCnt].size() - 1;
                int po = -1;
                while(l <= r) {
                    int mid = l + (r - l) / 2;
                    if(get(stks[maxCnt][mid] + 1, i) >= v[stks[maxCnt][mid]]) {
                        po = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                if(po == -1) {
                    dp[i] = maxCnt;
                    v[i] = v[stk.back()] + get(stk.back() + 1, i);
                    if(maxCnt - 1 > 0) {
                        int l = 0, r = stks[maxCnt - 1].size() - 1;
                        while(l <= r) {
                            int mid = l + (r - l) / 2;
                            ll x = get(stks[maxCnt - 1][mid] + 1, i);
                            if(x >= v[stks[maxCnt - 1][mid]]) {
                                v[i] = min(v[i], x);
                                l = mid + 1;
                            } else {
                                r = mid - 1;
                            }
                        }
                        
                    }
                    
                    while(dp[stk.back()] == maxCnt && 
                          v[i] < v[stk.back()] && 
                          get(stk.back() + 1, n - 1) - get(i + 1, n - 1) < v[stk.back()] - v[i]) {
                        
                        stk.pop_back();
                        stks[maxCnt].pop_back();
                    }
                    stk.push_back(i);
                    stks[maxCnt].push_back(i);
                } else {
                    dp[i] = dp[stk.back()] + 1;
                    v[i] = get(stks[maxCnt][po] + 1, i);
                    stks[dp[i]].push_back(i);
                    stk.push_back(i);
                }
            }
        }
        
        for(int i = 0; i < n; i++) {
            ans = max(ans, (int)(dp[i]));
        }

        return ans;
    }
};
