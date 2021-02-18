// 995. K 连续位的最小翻转次数

class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        int n = A.size();
        deque<int> dq;
        int ans = 0, revCnt = 0;

        for(int i = 0; i < n; ++i){
            if(!dq.empty() && (i - dq.front()) >= K){
                dq.pop_front();
            }
            // 需要反转
            if(A[i] == dq.size() % 2){
                // 越界, 直接判断
                if(i + K > n)   return -1;
                ++ans;
                dq.push_back(i);
            }
        }

        return ans;
    }
};
