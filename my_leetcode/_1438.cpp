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
