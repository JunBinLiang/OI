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
#include<fstream>


using namespace std;  
using ll = long long;
#define pb push_back

//ifstream fcin("test/input.txt");
//ofstream fcout("test/output.txt");

const int N = 2e5 + 10;
char s[N];
int a[N], nxt[N];
int in[N];
void solve() {
    vector<int> res;
    int n;
    scanf("%d", &n);
    scanf("%s", s);

    for(int i = 0; i <= n; i++) {
        in[i] = 0;
        a[i] = s[i] - '0';
    }

    for(int i = 0; i < n; i++) {
        scanf("%d", &nxt[i]);
        nxt[i]--;
        in[nxt[i]]++;
    }

    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(in[i] == 0) {
            q.push(i);
        }
    }

    while(q.size() > 0) {
        int u = q.front(); q.pop();
        if(a[u] == 1) {
            a[u] ^= 1;
            a[nxt[u]] ^= 1;
            res.push_back(u);
        }
        in[nxt[u]]--;
        if(in[nxt[u]] == 0) {
            q.push(nxt[u]);
        }
    }
    

    for(int i = 0; i < n; i++) {
        if(in[i] == 0) continue;
        vector<int> b;
        int u = i;
        int count = 0;
        while(in[u]) {
            if(a[u] == 1) count++;
            b.push_back(u);
            in[u]--;
            u = nxt[u];
        }
        
        if(count % 2 == 1) {
            cout << -1 << endl;
            return;
        }
        
        
        vector<int> e1, e2;
        int o = 0;
        int index = -1;
        for(int x = 0; x < b.size(); x++) {
            if(o == 1) index = x;
            if(a[b[x]] == 1) {
                o++;
            }
            if(o % 2 == 1) {
                e1.push_back(b[x]);
            }
            
        }
        
        o = 0;
        for(int x = 0; x < b.size(); x++) {
            int newi = (x + index) % b.size();
            if(a[b[newi]] == 1) o++;
            if(o % 2 == 1) {
                e2.push_back(b[newi]);
            }
        }

        if(e1.size() > e2.size()) swap(e1, e2);
        for(int e : e1) res.push_back(e);
    }



    //output
    cout << res.size() << endl;
    for(int i : res) {
        cout << i + 1 << " ";
    }
    cout << endl;
}

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}

