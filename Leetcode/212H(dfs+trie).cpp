const int N = 3e5 + 10;
int trie[N][26];
int good[N * 26];
int id = 1;
int n, m;
bool is[20][20];
set<int> take;
void add(string& word, int & idx) {
    int root = 1;
    for(int i = 0; i < word.size(); i++) {
        int d = word[i] - 'a';
        if(trie[root][d] == 0) {
            trie[root][d] = id + 1;
            id = id + 1;
        }
        root = trie[root][d];
    }
    good[root] = idx;
}

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& a, vector<string>& words) {
        n = a.size(); m = a[0].size();
        id = 1;
        take.clear();
        memset(trie, 0, sizeof trie);
        memset(good, -1, sizeof good);
        for(int i = 0; i < words.size(); i++) {
            add(words[i], i);
        }
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                dfs(a, i, j, 1);
            }
        }
        
        vector<string> res;
        for(auto it : take) {
            res.push_back(words[it]);
        }
        return res;
    }
    
    void dfs(vector<vector<char>>& a, int r, int c, int trieIndex) {   
        if(good[trieIndex] != -1) {
            take.insert(good[trieIndex]);
        }
        if(r < 0 || r >= n || c < 0 || c >= m || is[r][c]) {
            return;
        }
        int d = a[r][c] - 'a';
        if(trie[trieIndex][d] != 0) {
            is[r][c] = true;
            dfs(a, r + 1, c, trie[trieIndex][d]);
            dfs(a, r - 1, c, trie[trieIndex][d]);
            dfs(a, r, c + 1, trie[trieIndex][d]);
            dfs(a, r, c - 1, trie[trieIndex][d]);
            is[r][c] = false;
        }
    }
};
