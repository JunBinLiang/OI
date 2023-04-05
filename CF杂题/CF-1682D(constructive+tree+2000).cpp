#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector



//4 : 05
const int N = 2e5 + 10;
string s;
int n;
void solve() {
    scanf("%d", &n);
    cin >> s;
    int sum = 0;
    for(char c : s) {
        sum += (c - '0');
    }

    if(sum % 2 == 1) {
        cout << "NO" << endl;
        return;
    }

    int root = -1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            root = i;
            break;
        }
    }

    if(root == -1) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    
    vector<vector<int>> lines;
    for(int i = 0; i < n; i++) {
        if(s[(root + i) % n] == '1') {
            vector<int> c;
            lines.push_back(c);
            lines.back().push_back((root + i) % n);
        } else {
            lines.back().push_back((root + i) % n);
        }
    }

    for(auto& v : lines) {
        for(int i = 1; i < v.size(); i++) {
            cout << v[i - 1] + 1 << " " << v[i] + 1 << endl;
        }
    }
    
    int v1 = lines[0][0], v2 = lines[0].back();
    for(int i = 1; i < lines.size(); i++) {
        int last = lines[i].back();
        if(i == 1) {
            cout << v2 + 1 << " " << last + 1 << endl;
        } else {
            cout << v1 + 1 << " " << last + 1 << endl;
        }
    } 

}

int main()
{   

    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
