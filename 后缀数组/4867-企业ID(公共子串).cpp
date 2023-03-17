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
const int N = 8e5 + 100;
int sa[N], x[N], y[N], c[N], rk[N], height[N];
char s[N];
bool st[N];
int ids[N], rights[4010];


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

bool solve() {
    int t;
    scanf("%d", &t);
    if(t == 0) return false;
    
    n = 0;
    m = 122;
    for(int i = 0; i < t; i++) {
        scanf("%s", s + n + 1);
        int l = n + 1;
        n = strlen(s + 1);
        int r = n;
        for(int j = l; j <= r; j++) {
            ids[j] = i;
        }
        rights[i] = n;
    }
    
    
    /*for(int i = 0; i <= n; i++) cout << rights[i] << "  ";
    cout << endl;

    for(int i = 1; i <= n; i++) cout << s[i];
    cout << endl;
    
    for(int i = 1; i <= n; i++) cout << ids[i] << " ";
    cout << endl;
    
    printf("%d\n", n);*/
    
    SA();
    Height();
    
    /*cout << n << endl;
    for(int i = 1; i <= n; i++) cout << sa[i] << " ";
    cout << endl;
    for(int i = 1; i <= n; i++) cout << height[i] << " ";
    cout << endl;*/
    
    int res = 0, idx = -1;
    int l = 1, r = 200;
    
    while(l <= r) {
        int mid = l + (r - l) / 2;
        memset(st, false, sizeof st);
        int cnt = 0;
        int pos = -1;
        
        for(int i = 2; i <= n; i++) {
            if(height[i] < mid) continue;
            int j = i;
        
            if(!st[ids[sa[j - 1]]] && sa[j - 1] + mid - 1 <= rights[ids[sa[j - 1]]]) {
                cnt++;
                st[ids[sa[j - 1]]] = true;
            }
        
            while(j <= n && height[j] >= mid) {
                if(!st[ids[sa[j]]] && sa[j] + mid - 1 <= rights[ids[sa[j]]]) {
                    cnt++;
                    st[ids[sa[j]]] = true;
                }
                j++;
            }
            
            j = i;
            st[ids[sa[j - 1]]] = false;
            while(j <= n && height[j] >= mid) {
                st[ids[sa[j]]] = false;
                j++;
            }
            
            if(cnt == t) {
                res = mid;
                pos = sa[i];
                break;
            }
            cnt = 0;
            i = j - 1;
        }
        
        if(pos != -1) {
            l = mid + 1;
            idx = pos;
        }
        else r = mid - 1;
    }
    
    if(res == 0) printf("IDENTITY LOST\n");
    else {
        for(int i = idx; i < idx + res ; i++) printf("%c", s[i]);
        printf("\n");
    } 
    
    return true;
}




int main()
{
  int t = 1;
  //cin >> t;
  while(solve()) {}
  return 0;
}
