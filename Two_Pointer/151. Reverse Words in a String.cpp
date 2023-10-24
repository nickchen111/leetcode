/*
151. Reverse Words in a String
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    string reverseWords(string s) {
        string temp = "";
        string res = "";
        //找前後的空格往後或往前不是空格的那些欄位
        int left = 0;
        while(s[left] == ' '){
            left++;
        }
        int right = s.size()-1;
        while(s[right] == ' '){
            right--;
        }

        //開始整理答案字串
        while(left <= right){
            if(s[left] != ' '){
                temp+=s[left];
            }
            else{
                //代表之前已經處理過了 是很多段空格的情況
                if(s[left-1] == ' '){
                    left++;
                    continue;
                }
                else{
                    res = temp + ' '+ res;
                    temp = "";
                }
            }
            left++;
        }
        res = temp + ' ' + res;
        res.pop_back();

        return res;
    }
};

/*
分三段處理
1.找到非空白的頭尾段
2.在合法的頭尾段開始從左遍歷到右邊
如果遇到的是非空白 就不斷加入temp
如果遇到空白還要分兩種情況 一種是第一次遇到 一種是之前已經遇到
3.在遇到第一次遇到的空白時 需將 每一次的temp加到結果的前面 才會是reverse的
*/
