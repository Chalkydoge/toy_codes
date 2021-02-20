static const auto io_speed_up=[]{
  ios::sync_with_stdio(false);
  cin.tie(0);
  return 0;
}();

/*
* 思路: 答案就是数组中众数 出现的最后位置 - 首次出现位置的最小值
* 所以只要利用哈希表在遍历数组的过程中记录: 1. 出现的次数 2. 出现的首次位置
* 当次数出现了更大值, 我们就相应的更新一次ans, 如果出现了同样多次的元素, 则采用其中距离差更小的元素。
*/
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> hash;
        unordered_map<int, int> start;
        int n = nums.size();
        int ans = n, max_cnt = 0;

        for(int i = 0; i < n; ++i){
            int cur = nums[i];
            if(start.find(cur) == start.end()){
                start[cur] = i;
            }
            ++hash[cur];
            if(hash[cur] > max_cnt){
                max_cnt = hash[cur];
                ans = i - start[cur] + 1;
            }
            else if(hash[cur] == max_cnt){
                ans = min(ans, i - start[cur] + 1);
            }
        }

        return ans;        
    }
};
