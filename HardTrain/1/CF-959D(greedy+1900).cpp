#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


//5: 10
const int N = 2e6 + 10;
int a[N];
int n;
bool is[N], has[N];
vector<int> g[N];
void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    memset(is, false, sizeof is);
    memset(has, false, sizeof has);
    queue<int> q;
    for(int i = 2; i < N; i++) {
        if(is[i]) continue;
        q.push(i);
        for(int j = i; j < N; j += i) {
            is[j] = true;
            g[j].push_back(i);
        }
    }


    vector<int> res;
    bool ok = true;
    bool first = false;
    for(int i = 0; i < n; i++) {
        int v = a[i];

        if(ok) {
            for(int p : g[v]) {
                if(has[p]) {
                    ok = false;
                    first = true;
                }
                //has[p] = true;
            }
            
            if(ok) {
                for(int p : g[v]) {
                    has[p] = true;
                }
            }
        }
        
        if(ok) {
            res.push_back(v);
        } else {
            if(first) {
                first = false;
                for(int j = v; j < N; j++) {
                    bool no = false;
                    for(int p : g[j]) {
                        if(has[p]) {
                            no = true;
                            break;
                        }
                    }
                    if(!no) {
                        for(int p : g[j]) {
                            has[p] = true;
                        }
                        res.push_back(j);
                        break;
                    }
                }
                
            } else {
                while(has[q.front()] ) {
                    q.pop();
                }
                int x = q.front();
                res.push_back(x); 
                has[x] = true;
            }
        }
    }

    for(int i : res) {
        cout << i << " ";
    }
    cout << endl;
}   


int main()
{   

    int t = 1;
   // cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
