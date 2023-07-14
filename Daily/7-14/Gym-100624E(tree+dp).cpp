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
#include <fstream>
 
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define vec vector
#define var auto
#define JBFOR(i, a, b) for (int i = a; i < b; ++i)
using namespace std;
 
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}



vector<string> splitstr(string str, string deli = " ") //copy from google
{
    vector<string> token;
    int start = 0;
    int end = str.find(deli);
    while (end != -1) {
        //cout << str.substr(start, end - start) << endl;
        token.push_back(str.substr(start, end - start));
        start = end + deli.size();
        end = str.find(deli, start);
    }
    //cout << str.substr(start, end - start);
    token.push_back(str.substr(start, end - start));
    return token;
}

const int N = 3000 + 10;
int id = 0;
map<string, int> f;
string root, t;

int dp[510][2020]; //maximum matching


struct Node {
    bool leaf = false;
    int ch[2];
    string v;
    void init() {
        leaf = false;
        ch[0] = ch[1] = -1;
    }
} tr[N];


int dfs(int u, int l) { //start from l, what is the maximum match
    if(l >= t.size()) {
      return l;
    }

    if(dp[u][l] != -1) {
      return dp[u][l];
    }
    
    if(tr[u].leaf) {
        string& s = tr[u].v;
        int j = l;
        for(int i = 0; i < s.size() && j < t.size(); i++) {
          if(s[i] == t[j]) {
            j++;
          }
        }
        dp[u][l] = j;
        return j;
    }
    
    int left = tr[u].ch[0], right = tr[u].ch[1];
    int bestMatch1 = dfs(left, l);
    int bestMatch2 = dfs(right, bestMatch1);
    return dp[u][l] = bestMatch2;
}

void solve() {
  int n;
  cin >> n;
  string line;
  getline(cin, line);
  
  f.clear();
  id = 0;
  
  //construct the tree
  for(int i = 0; i < n; i++) {
    getline(cin, line);
    vector<string> token = splitstr(line);
    if(token.size() == 5) {
        string& x = token[0];
        string& y = token[2];
        string& z = token[4];
        if(f.find(x) == f.end()) {
            tr[id].init();
            f[x] = id++;
        }
        if(f.find(y) == f.end()) {
            tr[id].init();
            f[y] = id++;
        }
        if(f.find(z) == f.end()) {
            tr[id].init();
            f[z] = id++;
        }
        
        int id1 = f[x], id2 = f[y], id3 = f[z];
        tr[id1].ch[0] = id2;
        tr[id1].ch[1] = id3;
        //cout << id1 << " " << id2 << endl;
        //cout << id1 << " " << id3 << endl;
    } else {
        string& x = token[0]; 
        string& v = token[2];
        if(f.find(x) == f.end()) {
            tr[id].init();
            f[x] = id++;
        }
        int id1 = f[x];
        tr[id1].v = v;
        tr[id1].leaf = true;
    }
  }
  

  cin >> root >> t;
  int rootId = f[root];
  //init dp
  for(int i = 0; i <= id; i++) {
    for(int j = 0; j <= t.size(); j++) {
      dp[i][j] = -1;
    }
  }

  int to = dfs(rootId, 0);
  if(to >= t.size()) printf("YES\n");
  else printf("NO\n");
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
