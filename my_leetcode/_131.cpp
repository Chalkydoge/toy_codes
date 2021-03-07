class Solution {
public:
    vector<vector<string>> ans;
    int dp[1000][1000];

    void dfs(string& s, int idx, vector<string> tmp){
        int n = s.size();
        if(idx == n){
            ans.push_back(tmp);
            return;
        }

        for(int len = 1; len <= n; ++len){
            if(idx + len > n)
                break;
            if(dp[idx][idx + len - 1]){
                string str = s.substr(idx, len);
                tmp.push_back(str);
                dfs(s, idx + len, tmp);
                tmp.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        int n = s.size();
        memset(dp, 1, sizeof(dp));

        for(int i = n - 1; i >= 0; --i){
            for(int j = i + 1; j < n; ++j){
                dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
            }
        }
        dfs(s, 0, {});
        return ans;
    }
};
