/*
维护一个'窗口' 计算超额的收入, 保留最大值即可。
*/


class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int res = 0;
        int n = grumpy.size();
        int sum = 0;
        for(int i = 0; i < n; ++i){
            if(grumpy[i] != 1){
                sum += customers[i];
            }
        }

        for(int i = 0; i <= n - X; ++i){
            int tmp = sum;
            for(int j = 0; j < X; ++j){
                if(grumpy[i + j] == 1){
                    tmp += customers[i + j];
                }
            }
            res = max(tmp, res);
        }

        return res;
    }
};
