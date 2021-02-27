class Solution {
public:
    int longestSubstring(string s, int k) {
        int n = s.size();
        if(n < k){
            return 0;
        }
        int ans = 0;

        // 枚举窗口内可以出现的字符种类数 I
        for(int i = 1; i <= 26; ++i){
            int hash[26];
            memset(hash, 0, sizeof(hash));
            
            int left = 0, j = 0;
            // right = 右边界, 子字符串的最右侧选择
            for(int right = 0; right < n; ++right){
                if(hash[s[right] - 'a'] == 0){
                    ++j;
                }
                ++hash[s[right] - 'a'];
                // J > I 意味着出现的字符种类更多了, 需要移除部分字符
                while(j > i){
                    hash[s[left] - 'a']--;
                    if(hash[s[left] - 'a'] == 0){
                        --j;
                    }
                    ++left;
                }
                // 在保证范围内出现字符种类固定的情况下, 检查是否满足要求
                bool flag = true;
                for(int t = 0; t < 26; ++t){
                    if(hash[t] > 0 && hash[t] < k){
                        flag = false;
                    }
                }
                if(flag){
                    ans = max(ans, right - left + 1);
                }
            }
        }

        return ans;
    }
};
