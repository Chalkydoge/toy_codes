class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int, int> word_mask;
        for(auto& str: words){
            int mask = 0;
            for(auto& c: str){
                int bias = c - 'a';
                mask |= (1 << bias);
            }
            ++word_mask[mask];
        }

        int n = puzzles.size();
        vector<int> ans(n, 0);

        int cnt = 0;
        for(const auto& p: puzzles){
            int puzzle_mask = 0;
            int first_char = 0;
            bool first = true;

            for(const auto& c: p){
                int bias = c - 'a';
                puzzle_mask |= (1 << bias);
                if(first){
                    first_char = c - 'a';
                    first = false;
                }
            }

            int tmp = 0;
            // 1001 => 1001 & 1000 = 1000(subset)
            // 1001 & 0111 => 0001(subset)
            for(int state = puzzle_mask; state != 0; state = puzzle_mask & (state - 1)){
                if(word_mask.count(state)){
                    if((state >> first_char) & 0x1 == 0x1){
                        tmp += word_mask[state];
                    }
                }
            }
            ans[cnt++] = tmp; 
        }

        return ans;
    }
};
