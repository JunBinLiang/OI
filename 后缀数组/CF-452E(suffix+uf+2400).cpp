#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector
typedef pair<int, int> PII;
typedef pair<double, double> PDD;

int n, m;
char ch[4] = {'!', ',', '.', '?'};
const int N = 4e5 + 100, mod = 1e9 + 7;
int sa[N], x[N], y[N], c[N], rk[N], height[N];
char s[N];
int ids[N], rights[3];
ll res[N];
int cnt[N][3];
vector<int> g[N];


int p[N];
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

//sa[i] : 排名第i 是第几个后缀
//rank[i] : 第i个后缀排名第几
void SA() {
  int sz = max(n, m);
  for(int i = 1; i <= sz; i++)  height[i] = c[i] = 0; 
  for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
  for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
  for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;

  for (int k = 1; k <= n; k <<= 1) {
    int num = 0;
    for (int i = n - k + 1; i <= n; i++ ) y[++num] = i;
    for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k; //第二关键字排序

    //第一关键字排序
    for (int i = 1; i <= m; i ++ ) c[i] = 0;
    for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
    swap(x, y);

    //离散化
    x[sa[1]] = 1, num = 1;
    for (int i = 2; i <= n; i ++ )
        x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
    if (num == n) break;
    m = num;  
  }
}

//lcp(i, j) = min(lcp(i, k), lcp(k, j))
//height[i] = lcp(i - 1, i)
void Height() {
  for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
  for (int i = 1, k = 0; i <= n; i ++ ) {
    if (rk[i] == 1) continue;
    if (k) k -- ;
    int j = sa[rk[i] - 1];
    while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
    height[rk[i]] = k;
  }
}

//10:40 - 11:31
void solve() {
    int t = 3;
    n = 0;
    m = 122;
    int sz = 3e5 + 5;
    
    for(int i = 0; i < t; i++) {
        scanf("%s", s + n + 1);
        int l = n + 1;
        n = strlen(s + 1);
        int r = n;
        for(int j = l; j <= r; j++) {
            ids[j] = i;
        }
        sz = min(sz, r - l + 1);
        n++;
        s[n] = ch[i];
    }

    for(int i = 0; i < N; i++) {
        p[i] = i;
    }

    
    /*for(int i = 1; i <= n; i++) cout << s[i];
    cout << endl;

    for(int i = 1; i <= n; i++) cout << ids[i] << " ";
    cout << endl;*/
    
    

    SA();
    Height();

    /*cout << n << endl;
    for(int i = 1; i <= n; i++) cout << sa[i] << " ";
    cout << endl;
    
    for(int i = 1; i <= n; i++) cout << height[i] << " ";
    cout << endl;*/
    
    
    memset(res, 0, sizeof res);
    memset(cnt, 0, sizeof cnt);

    for(int i = 1; i <= n; i++) {
        cnt[sa[i]][ids[sa[i]]]++;
    }

    for(int i = 1; i <= n; i++) {
        //int h = min(height[i], rights[ids[sa[i]]] - sa[i] + 1);
        int h = height[i];
        g[h].push_back(i);
        //cout << h << " ";
    }
    //cout << endl;


    ll tot = 0;
    for(int i = n; i >= 1; i--) {
        for(int e : g[i]) {
            if(e == 1) {
                continue;
            }
            //cout << "edge :" << i << " " << sa[e] << endl;
            
            int u = sa[e];
            int v = sa[e - 1];
            int r1 = find(u), r2 = find(v);
            if(r1 != r2) {
                p[r1] = r2; //r1 - > r2

                for(int j = 0; j < 1; j++) {
                    ll v = (cnt[r1][0] + 0ll) * (cnt[r1][1] + 0ll) * (cnt[r1][2] + 0ll);
                    v %= mod;
                    tot -= v;
                    tot %= mod;
                    if(tot < 0) tot += mod;
                }

                for(int j = 0; j < 1; j++) {
                    ll v = (cnt[r2][0] + 0ll) * (cnt[r2][1] + 0ll) * (cnt[r2][2] + 0ll);
                    v %= mod;
                    tot -= v;
                    tot %= mod;
                    if(tot < 0) tot += mod;
                }

                cnt[r2][0] += cnt[r1][0];
                cnt[r2][1] += cnt[r1][1];
                cnt[r2][2] += cnt[r1][2];

                for(int j = 0; j < 1; j++) {
                    ll v = (cnt[r2][0] + 0ll) * (cnt[r2][1] + 0ll) * (cnt[r2][2] + 0ll);
                    v %= mod;
                    tot += v;
                    tot %= mod;
                }
                
                //cout << tot <<"  " << cnt[r2][0] <<"  " << cnt[r2][1] << " " << cnt[r2][2] << endl;
            }
        }
        res[i] = tot;
    }

    for(int i = 1; i <= sz; i++) {
        printf("%lld ", res[i]);
    }
}




int main()
{
  int t = 1;
  //cin >> t;
  solve();
  return 0;
}

//aaaaa aaaaa aaaaa
