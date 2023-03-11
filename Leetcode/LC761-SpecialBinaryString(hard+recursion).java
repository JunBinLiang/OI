class Solution {
    public String makeLargestSpecial(String s) {
        return dfs(s);
    }
    
    public String dfs(String s) {
        if(s.length() == 0) {
            return s;
        }
        
        int cnt = 0;
        List<String> list = new ArrayList<>();
        boolean good = true;
        int p = 0;
        for(int i = 0; i < s.length(); i++) {
            if(s.charAt(i) == '1') cnt++;
            else cnt--;
            if(cnt < 0) {
                good = false;
            }
            if(cnt == 0) {
                String sub = s.substring(p, i + 1);
                list.add(sub);
                p = i + 1;
            }
        }
        
        
        if(!good) {
            return s;
        }
        
        if(list.size() == 1) {
            return "1" + dfs(s.substring(1, s.length() - 1)) + "0";
        }
        
        List<String> res = new ArrayList<>();
        for(String t : list) {
            res.add(dfs(t));
        }
        
        list = res;
        Collections.sort(list, Collections.reverseOrder());
        String t1 = String.join("", list);
        String t2 = "1" + dfs(s.substring(1, s.length() - 1)) + "0";
        if(t1.compareTo(t2) > 0) {
            return t1;
        } else {
            return t2;
        }
    }
}
