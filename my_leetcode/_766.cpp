/*
* 注意一点就可以了 判断条件就矩阵中所有的当前元素 = 左上角元素
*/

class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();

        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                if(matrix[i][j] != matrix[i - 1][j - 1]){
                    return false;
                }
            }
        }
        return true;
    }
};
