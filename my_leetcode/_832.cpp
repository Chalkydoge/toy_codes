/*
给定一个二进制矩阵 A，我们想先水平翻转图像，然后反转图像并返回结果。

水平翻转图片就是将图片的每一行都进行翻转，即逆序。例如，水平翻转 [1, 1, 0] 的结果是 [0, 1, 1]。

反转图片的意思是图片中的 0 全部被 1 替换， 1 全部被 0 替换。例如，反转 [0, 1, 1] 的结果是 [1, 0, 0]。
*/

class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        int m = A.size(), n = A[0].size();
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n / 2; ++j){
                swap(A[i][j], A[i][n - 1 - j]);
            }
        }

        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                A[i][j] = 1 ^ A[i][j];
            }
        }
        return A;
    }
};
