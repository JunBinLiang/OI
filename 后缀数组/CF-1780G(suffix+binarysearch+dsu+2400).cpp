
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
#define FOR(i, a, b) for (int i = a; i < b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

int n, m;
const int N = 1000010;
int sa[N], x[N], y[N], c[N], rk[N], height[N];
int p[N], sz[N], preLen[N];
char s[N];
vector<int> di[N];
//sa[i] : 排名第i 是第几个后缀
//rank[i] : 第i个后缀排名第几
void Sa() {
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

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

int cal(int L, int R, int len) {
    //cout << L << " " << R << " " << len << endl;
    if(L > R || L == -1 || R == -1) return 0;
    //how many numbers from [L, R] divisible by len
    vector<int>& v = di[len];
    int p1 = -1, p2 = -1;
    
    int l = 0, r = v.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(v[mid] >= L) {
            p1 = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    l = 0; r = v.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(v[mid] <= R) {
            p2 = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
    if(p1 != -1 && p2 != -1 && p1 <= p2) {
        return p2 - p1 + 1;
    } else {
        return 0;
    }
}

void init() {
    const int MAX = 1e6;
    for(int i = 1; i <= MAX; i++) {
        for(int j = i; j <= MAX; j += i) {
            di[j].push_back(i);
        }
    }
}

ll res = 0;

void solve() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    n = strlen(s + 1), m = 256;
    Sa();
    Height();
    
    /*for (int i = 1; i <= n; i ++ ) printf("%d ", sa[i]);
    puts("");
    for (int i = 1; i <= n; i ++ ) printf("%d ", height[i]);
    puts("");*/
    
   
    
    vector<pair<int, int>> a;
    for(int i = 2; i <= n; i++) {
        a.push_back({height[i], i});
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < N; i++) p[i] = i, sz[i] = 1, preLen[i] = -1;
    
    for(int i = 0; i < a.size(); i++) {
        if(a[i].first == 0) break;
        int prefix = a[i].first;
        int j = i;
        vector<int> b;
        while(j < a.size() && a[j].first == a[i].first) {
            int u = sa[a[j].second], v = sa[a[j].second - 1];
            int r1 = find(u), r2 = find(v);
            b.push_back(u);
            b.push_back(v);
            if(r1 != r2) {
                int v1 = cal(prefix + 1, preLen[r1], sz[r1]) * sz[r1], v2 = cal(prefix + 1, preLen[r2], sz[r2]) * sz[r2];
                //cout << "merge  " << u << " " << v <<" " << v1 << " " << v2 << endl;
                res += (v1 + v2);
                preLen[r2] = prefix;
                p[r1] = r2;
                sz[r2] += sz[r1];
            }
            j++;
        }
        i = j - 1;
    }
    
    //cout << "before  " << res << endl;

    set<int> se;
    for(int i = 1; i <= n; i++) {
        se.insert(find(i));
    }
    
    for(auto r : se) {
        if(preLen[r] == -1) {
            res++;
        } else {
            res += cal(1, preLen[r], sz[r]) * sz[r];
        }
    }

    cout << res << endl;
}

int main()
{   
    init();
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
