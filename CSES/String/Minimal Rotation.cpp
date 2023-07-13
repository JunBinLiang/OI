def least_rotation(S: str) -> int:
    """Booth's algorithm."""
    S += S  # Concatenate string to it self to avoid modular arithmetic
    f = [-1] * len(S)  # Failure function
    k = 0  # Least rotation of string found so far
    for j in range(1, len(S)):
        sj = S[j]
        i = f[j - k - 1]
        while i != -1 and sj != S[k + i + 1]:
            if sj < S[k + i + 1]:
                k = j - i - 1
            i = f[i]
        if sj != S[k + i + 1]:  # if sj != S[k+i+1], then i == -1
            if sj < S[k]:  # k+i+1 = k
                k = j
            f[j - k] = -1
        else:
            f[j - k] = i + 1
    return k
 
S = input("")
i = least_rotation(S)
print(S[i:] + S[:i])






/*
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
#define f first
#define se second
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)


int n, m;
const int N = 2000010;
int sa[N], x[N], y[N], c[N], rk[N], height[N];
char s[N];


//sa[i] : 排名第i 是第几个后缀
//rank[i] : 第i个后缀排名第几
void Sa() {
  //类似第一关键字排序，用前缀和看有多少个小于
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

void solve() {
    scanf("%s", s + 1);
    
    n = strlen(s + 1);
    m = 122;
    
    for(int i = 1; i <= n; i++) {
        s[i + n] = s[i];
    }
    n *= 2;

    
    Sa();
    
    int idx = -1;
    for(int i = 1; i <= n; i++) {
        if(sa[i] <= n / 2) {
            idx = sa[i];
            break;
        }
    }
    
    for(int i = 0; i < n / 2; i++) {
        printf("%c", s[idx + i]);
    }
}




int main()
{
  int t = 1;
  //cin >> t;
  while(t--)
  {
    solve();
  }
  return 0;
}

*/
