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
#include <iostream>
   
using ll = long long;
using namespace std;  



int n, m, mod;
string s;

const int N = 22;
ll a[N][N], f1[N];

void mul1() {
    ll temp[N];
    for(int i = 0; i <= m; i++) temp[i] = f1[i];
    for(int c = 0; c <= m; c++) {
        ll sum = 0;
        for(int r = 0; r <= m; r++) {
            sum += (temp[r] * a[r][c]);
            sum %= mod;
        }
        f1[c] = sum;
    }
}

void mul2() {
    ll temp[N][N];
    for(int i = 0; i <= m; i++)
        for(int j = 0; j <= m; j++)
            temp[i][j] = a[i][j];
            
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= m; j++) {
            ll sum = 0;
            for(int k = 0; k <= m; k++) {
                sum += temp[i][k] * temp[k][j];
                sum %= mod;
            }
            a[i][j] = sum;
        }
    }
    
}

vector<int> kmp(string& pattern){
    vector<int> pre(pattern.size());
    int l=0,r=1;
    while(r < pattern.size()){
        if(pattern[r] == pattern[l]){
          pre[r] = l + 1;
          l++;
          r++;
        }else{
            if(l == 0)r++;
            else{
                l = pre[l-1];
            }
        }
    }
    return pre;
}

void solve() {
    cin >> n >> m >> mod;
    cin >> s;
    
    //kmp
    vector<int> pre = kmp(s);
    memset(a, 0, sizeof a);
    memset(f1, 0, sizeof f1);
    f1[0] = 1;
  
    for(int j = 1; j <= m; j++) {
        a[j - 1][j] += 1;
    }
    a[0][0] += 9;
    
    for(int i = 0; i < pre.size() - 1; i++) {
        for(int j = 0; j <= 9; j++) {
            if(j == s[i + 1] - '0') continue;
            int t = pre[i];
            while(t != 0) {
                if(s[t] - '0' == j) {
                    break;
                } else {
                    t = pre[t - 1];
                }
            }
            
            if(s[t] - '0' == j) {
                a[i + 1][t + 1]++;
            } else {
                a[i + 1][0]++;
            }
        }
    }
    
    while(n) {
        if (n & 1) mul1();  // res = res * a
        mul2();  // a = a * a
        n >>= 1;
    }
    
    ll res = 0;
    for(int i = 0; i < m; i++) {
        res += f1[i];
        res %= mod;
    }
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}
