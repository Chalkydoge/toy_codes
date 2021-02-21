
/* 分析: 数列的绝对值由最大值与最小值两部分决定.
*  维护一个子数组的最大元素与最小元素的位置, 考虑已有的一个子数组, 它的绝对值差值小于limit;
*  为了维护最大值,最小值, 使用两个单调队列, 维护下标(index)
*   如果当前加入的元素比队列中之前加入的更大/更小, 就进行调整(pop), 将队列对应数组子数组的左边界进行调整;
*   如果不影响则按照单调队列的构造方式加入队列;
*  最后比较队列中的最大值,最小值的差值, 符合要求则记录答案, 并且向右移动.
*  复杂度: O(N)
*/
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> min_q;
        deque<int> max_q;

        int n = nums.size();
        int left = 0, right = 0;
        int res = 0;
        max_q.push_back(0);
        min_q.push_back(0);

        while(right < n){
            int max_num = nums[max_q.front()];
            int min_num = nums[min_q.front()];
            if(max_num - min_num <= limit){
                res = max(res, right - left + 1);
                ++right;
                while(right < n && !min_q.empty() && nums[min_q.back()] >= nums[right]){ min_q.pop_back(); }
                min_q.push_back(right);
                while(right < n && !max_q.empty() && nums[max_q.back()] <= nums[right]) { max_q.pop_back(); }            
                max_q.push_back(right);
            }  
            else{
                left = min(min_q.front(), max_q.front()) + 1;
                while(!min_q.empty() && min_q.front() < left)   min_q.pop_front();
                while(!max_q.empty() && max_q.front() < left)   max_q.pop_front();
            }
        }

        return res;
    }
};
