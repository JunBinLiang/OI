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
   
using namespace std;  

using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

const int N = (5e5 + 10) * 3;
int a[3][N];
int R[3][N], sizes[3][N];
int dp[3][N];
int res[N], sz[N], to[N];
int p[N];
vector<pair<int, int>> q[N];
int tot = 0;
int n = 3, m = 0;

int find(vector<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void merge(vector<int>& nums, int r1, int r2) {
    if(r1 != r2) {
        nums[r1] = r2;
        sz[r2] += sz[r1];
        tot--;
    }
}

int cal(vector<int>& nums, int l, int r, int idx) {
    int sum1 = a[0][l] + a[1][l] + a[2][l];
    int sum2 = a[0][l + 1] + a[1][l + 1] + a[2][l + 1];
    
    if(sum1 == 0 || sum2 == 0) { //good
        return p[r] - p[l];
    }

    if(sum1 == 3) {
        if(sum2 == 0) return p[r] - p[l];
        else if(sum2 == 1 || sum2 == 3) return p[r] - p[l] + 1;
        else if(sum2 == 2) {
            if(a[0][l + 1] == 1 && a[2][l + 1] == 1) {
                int l1 = dp[0][l + 1], l2 = dp[2][l + 1];
                int first = to[l + 1];
                if(l + 1 + min(l1, l2) - 1 >= first && first <= r) {
                    return p[r] - p[l] + 1;
                } else {
                    return p[r] - p[l] + 2;
                }

            } else {
                return p[r] - p[l] + 1;
            }
        }
    } else if(sum1 == 1){ //good
        int po = -1;
        for(int i = 0; i < 3; i++) {
            if(a[i][l] == 1) po = i;
        }
        if(a[po][l + 1] == 1) {
            return p[r] - p[l] + 1;
        } else {
            return p[r] - p[l];
        }
    } else if(sum1 == 2 ){
        if(sum2 == 1) {
            int po = -1;
            for(int i = 0; i < 3; i++) {
                if(a[i][l + 1] == 1) po = i;
            }
            
            if(a[po][l] == 1 && a[po][l + 1] == 1) {
                return p[r] - p[l] + 1;
            } else {
                return p[r] - p[l];
            }
        }

        if(a[0][l] == 1 && a[2][l] == 1) {
            if(sum2 == 3) {
                if(R[0][l] == R[2][l]) {
                    return p[r] - p[l] + 1;
                } else {
                    return p[r] - p[l] + 2;
                }
            }
        
            
            if(a[0][l + 1] == 1 && a[2][l + 1] == 1) {
                if(R[0][l] != R[2][l]) {
                    return p[r] - p[l] + 2;
                }

                int l1 = dp[0][l + 1], l2 = dp[2][l + 1];
                int first = to[l + 1];
                if(l + 1 + min(l1, l2) - 1 >= first && first <= r) {
                    return p[r] - p[l] + 1;
                } else {
                    return p[r] - p[l] + 2;
                }

            } else {
                return p[r] - p[l] + 1;
            }
        } else {
            return p[r] - p[l] + 1;
        }
    }
}

void solve() {
    cin >> m;
    a[0][0] = a[0][1] = a[0][2] = 0;
    p[0] = 0;
    for(int i = 0; i < N; i++) sz[i] = 1;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 1; j <= m; j++) {
            a[i][j] = s[j - 1] - '0';
        }
    }
    
    vector<int> nums(3 * (m + 1)); 
    for(int i = 0; i < nums.size(); i++) {
        nums[i] = i;
    }

    int k;
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        q[r].push_back({l, i});
    }

    
    int last = 1e9;
    for(int i = m; i >= 1; i--) {
        to[i] = last;
        int sum = 0;
        for(int j = 0; j < 3; j++) sum += a[j][i];
        if(sum == 3) {
            last = i;
        }
    }
    
    //find longest
    memset(dp, 0, sizeof dp);
    for(int i = m; i >= 1; i--) {
        for(int r = 0; r < 3; r++) {
            if(a[r][i] == 0) {
                dp[r][i] = 0;
            } else {
                if(i + 1 <= m) dp[r][i] = 1 + dp[r][i + 1];
                else dp[r][i] = 1;
            }
        }
    }
    
    for(int i = 1; i <= m; i++) {
        for(int r = 0; r < 3; r++) {
            tot += a[r][i];
        }
        
        for(int r = 0; r < 3; r++) {
            if(a[r][i] == 0) continue;

            int u = r * m + i;
            if(a[r][i - 1] == 1) {
                int v = r * m + (i - 1);
                int r1 = find(nums, u);
                int r2 = find(nums, v);
                merge(nums, r1, r2);
            }

            if(r + 1 < 3 && a[r + 1][i] == 1) {
                int v = (r + 1) * m + i;
                int r1 = find(nums, u);
                int r2 = find(nums, v);
                merge(nums, r1, r2);
            }
        }
        
        for(int r = 0; r < 3; r++) {
            if(!a[r][i]) continue;
            int u = r * m + i;
            R[r][i] = find(nums, u); 
            sizes[r][i] = sz[R[r][i]];
        }
        
        p[i] = tot;
        for(pair<int, int>& pa : q[i]) {
            int l = pa.first, idx = pa.second;
            l--;
            res[idx] = cal(nums, l, i, idx + 1);
        }
    }
    
    for(int i = 0; i < k; i++) {
        printf("%d\n", res[i]);
    }

}

int main() {
    int t = 1;
    //cin >> t;  
    while(t --) {
        solve();
    }
    return 0;
}
