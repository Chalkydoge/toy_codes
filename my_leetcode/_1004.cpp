class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        int n = A.size();
        int left = 0, right = 0;
        int cnt = K;
        int res = 0;
        
        while(right < n){
            if(A[right] == 0){
                if(cnt > 0){
                    --cnt;
                    ++right;
                }
                else{
                    if(A[left] == 0){
                        ++cnt;
                    }
                    ++left;
                }
            }
            else{
                ++right;
            }
            res = max(res, right - left);
        }
        return res;
    }
};
