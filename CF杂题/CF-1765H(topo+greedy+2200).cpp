
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
#define PII pair<long long, int>


template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int N = 2010;
vector<int> g[N];
pair<int, int> e[N];
int in[N];
int n, m;

struct Node {
    int v1, v2, idx;
    /*bool operator <(const Node& other) {
        if(v1 == other.v1) {
            return v2 < other.v2;
        }
        return v1 > other.v1;
    }*/
};

class Compare{
    public:
        bool operator()(const Node& node1, const Node& node2) {
            if(node1.v1 == node2.v1) {
                return node1.v2 > node2.v2;
            }
            return node1.v1 < node2.v1;
        }
};

void solve() {
    cin >> n >> m;
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[v].push_back(u);
        e[i] = {u, v};
    }
    
    
    /*priority_queue<Node, vector<Node>, Compare> qq;
    qq.push({2,3, 0});
    qq.push({2, 1, 1});
    qq.push({3, 2, 2});
    while(qq.size()) {
        Node no = qq.top(); qq.pop();
        cout << no.v1 << " " << no.v2 << " " << no.idx << endl;
    }*/
    
    vector<int> res(n);
    for(int i = 0; i < n; i++) {
        memset(in, 0, sizeof in);
        for(int j = 0; j < m; j++) {
            in[e[j].first]++;
        }
        
        /*cout << i << "  " << endl;
        for(int j = 0; j < n; j++) {
            cout << in[j] << " ";
        }
        cout << endl << endl;*/
        
        priority_queue<Node, vector<Node>, Compare> q;
        
        for(int j = 0; j < n; j++) {
            if(in[j] == 0) {
                if(j == i) {
                    //q.push({p[j], 1, j});
                } else {
                    q.push({p[j], 0, j});
                }
            }
        }
        
        //we always place the targetNode at the end, so we can actually not add it to the heap
        
        int ans = n;
        while(q.size() > 0) {
            Node node = q.top(); q.pop();
            
            if(node.v1 < ans) { //can not place any more
                break;
            }
            
            for(int& nxt : g[node.idx]) {
                in[nxt]--;
                if(!in[nxt]) {
                    if(nxt == i) {
                        
                    } else {
                        q.push({p[nxt], 0, nxt});
                    }
                }
            }
            ans--;
        }
        res[i] = ans;
        
    }
    
    for(int x : res) cout << x << " ";
    cout << endl;
    
}   


int main()
{   
    int t = 1;
    //cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}

