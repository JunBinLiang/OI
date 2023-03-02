#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define pb push_back
#define ve vector






//4:34 - 4:39 
void solve() {
    string s;
    cin >> s;
    int j = 0;
    int cnt = 0;
    map<char, int> f;
    int l = -1, r = -1;

    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '?') {
            cnt++;
        } else {
            f[s[i]]++;
        }

        if(i + 1 < 26) {
            continue;
        }

        if(f.size() + cnt == 26) {
            l = j; r = i;
        }

        if(s[j] == '?') {
            cnt--;
        } else {
            f[s[j]]--;
            if(f[s[j]] == 0) {
                f.erase(s[j]);
            }
        }
        j++;
    }
    
    if(l == -1) {
        cout << -1 << endl;
        return;
    }
    
   
    set<char> se;
    for(int i = 0; i < 26; i++) {
        char c = (char)(i + 'A');
        se.insert(c);
    }

    for(int i = l; i <= r; i++) {
        if(s[i] != '?')
            se.erase(s[i]);
    }

    for(int i = l; i <= r; i++) {
        if(s[i] == '?') {
            auto it = se.begin();
            s[i] = *it;
            se.erase(s[i]);
        }
    }
    
    for(char& c : s) {
        if(c == '?') c = 'A';
    }

    cout << s << endl;
}

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
