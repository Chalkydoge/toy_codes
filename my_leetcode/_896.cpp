class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        bool up = true;
        bool down = true;
        int n = A.size();
        for(int i = 1; i < n; ++i){
            if(A[i] > A[i - 1]){
                up = false;
            }
            else if(A[i] < A[i - 1]){
                down = false;
            }
        }
        return up | down;
    }
};
