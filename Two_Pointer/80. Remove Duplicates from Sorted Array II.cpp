/*
80. Remove Duplicates from Sorted Array II
*/

//  TC:O(n) SC:O(1)
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() < 3) return nums.size();
        
        int count = 2;
        for(int i = 2; i < nums.size(); i++){
            if(nums[i] != nums[count-2]){
                nums[count] = nums[i];
                count++;
            }
        }
        return count;
    }
};
