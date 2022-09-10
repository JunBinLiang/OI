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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 5e5 + 10;
int n, m;
ll a[N];
int base[N][21], idx[N][21];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }

    memset(base, -1, sizeof(base));
    memset(idx, -1, sizeof(idx));


    for(int i = 1; i <= n; i++) {
      int x = a[i], k = i;
      
      for(int j = 0; j < 21; j++) {
        base[i][j] = base[i - 1][j];
        idx[i][j] = idx[i - 1][j];
      }

      for(int j = 20; j >= 0; j--) {
        if(x & (1 << j)) {
            if(base[i][j] == -1) {
                base[i][j] = x;
                idx[i][j] = k;
                break;
            } else {
                if(idx[i][j] < k) {
                    swap(idx[i][j], k);
                    swap(base[i][j], x);
                }
                x ^= base[i][j];
            }
        }
      }

    }

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
      int l, r;
      scanf("%d%d", &l, &r);
      int res = 0;
      for(int j = 20; j >= 0; j--) {
        if(idx[r][j] >= l) {
          if((res ^ base[r][j]) > res){
              res ^= base[r][j];
          }
        }
      }
      printf("%d \n", res);
    }
    
    return 0;
}   
