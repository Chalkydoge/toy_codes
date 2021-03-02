class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = 0;
        if(m != 0)
            n = matrix[0].size();
        pre.resize(m + 1, vector<int>(n + 1));
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                pre[i][j] = matrix[i - 1][j - 1] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
            }
        }

        // for(int i = 1; i <= m; ++i){
        //     for(int j = 1; j <= n; ++j){
        //         cout << pre[i][j] << '\t';
        //     }
        //     cout << endl;
        // }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return pre[row2 + 1][col2 + 1] - pre[row1][col2 + 1] - pre[row2 + 1][col1]  + pre[row1][col1];
    }
private:
    vector<vector<int>> pre;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
