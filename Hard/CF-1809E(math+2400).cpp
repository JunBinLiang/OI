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
   
using namespace std;  
using ll = long long;
#define pb push_back
#define ve vector


//1:30
const int N = 1e4 + 5, M = 1010;
int a[N], ans[M][M];
int n, x, y;
void solve() {
    memset(ans, 0, sizeof ans);

    cin >> n >> x >> y;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(int s = 0; s <= x + y; s++) {
        int lb = 1e9, rb = 0;
        for(int i = 0; i <= min(x, s); i++) {
            if(i + y >= s) {
                lb = min(lb, i);
                rb = max(rb, i);
            }
        }
        int l = lb, r = rb;
        int lcompress = 1;
        
       // if(s == 5) {
            //cout <<"gg0   : " <<  l << "  " << r << endl;
       // }
        
        for(int i = 0; i < n; i++) {
            int v = a[i];
            int oldl = l, oldr = r;
            int oldsz = oldr - oldl + 1;
            l = max(lb, min(l - v, rb));
            r = min(rb, max(lb, r - v));
            int newsz = r - l + 1;
            
           // if(s == 5) {
               // cout <<"before   : " <<  lcompress <<"    |" << oldsz << " " << newsz << endl;
          //  }
            
            if(v > 0) {
                lcompress += (oldsz - newsz);
            }
            
            //if(s == 5) {
               // cout <<"gg1   : " <<  l << "  " << r <<"  " << lcompress << endl;
               // cout << oldl << "  " << oldr << endl << endl;
           // }
        }

        //update answer
        int add = 0;
        for(int i = lb; i <= rb; i++) {
            int j = s - i;
            if(lcompress > 0) {
                lcompress --;
                ans[i][j] = l;
            } else {
                add++;
                ans[i][j] = min(l + add, r);
            }
        }
    }

    for(int i = 0; i <= x; i++) {
        for(int j = 0; j <= y; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
    
}

int main() {
    solve();
    return 0;
}
