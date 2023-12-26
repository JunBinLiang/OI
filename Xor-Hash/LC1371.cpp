using ull = unsigned long long;
ull seed = 131;
ull rands(){ return seed = (seed << 15) + (seed << 8)+( seed >> 3);}


class Solution {
public:
    int findTheLongestSubstring(string s) {
        vector<ull> hmp(26);
        for(int i = 0; i < 26; i++) {
            hmp[i] = rands(); 
        }
        
        ull xo = 0;
        int res = 0;
        
        unordered_map<ull, int> f;
        f[0] = 0;
        
        for(int i = 1; i <= s.size(); i++) {
            char c = s[i - 1];
            if(isv(c)) {
                xo ^= hmp[c - 'a'];
            }
            
            if(f.find(xo) == f.end()) {
                f[xo] = i;
            } else {
                res = max(res, i - f[xo]);
            }
        } 
        
        return res;
        
    }
    
    bool isv(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
