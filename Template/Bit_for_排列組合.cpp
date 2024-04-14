
int m = nums.size();
for(int k = 1; k <= m; k++){
    int state = (1<<k) -1;
    LL sum = 0;
    while(state < (1<<m)){
        LL product = 1;
        for(int i = 0; i < m; i++){
            if((state >> i)&1) {
                product = product * coins[i] / gcd(product, coins[i]);
            }
        }
        sum += (mid/product);
        
        int c = state&-state;
        int r = state + c;
        state = (((r^state)>>2)/c ) | r;
    }
    
    // do something
}

/*
int c = state & -state;：這一行程式碼使用了位元運算中的位與（AND）操作符號 &，將 state 和 state 的補數 -state 進行位元與運算。補數的計算是取反加一的操作，即 ~state + 1。位元與操作會將 state 中最右邊的 1 保留下來，其他位元都設為 0。這樣就得到了 c，它是 state 中最右邊的 1 所在的位元位置。

int r = state + c;：這一行程式碼將 state 和 c 相加，這樣就將 state 中最右邊的 1 變成了 0，而其右邊的 0 也都變成了 1。

state = (((r ^ state) >> 2) / c) | r;：這一行程式碼是將 state 中除了最右邊的 1 之外的其他位元都進行 XOR 運算，然後右移 2 位再除以 c（也就是最右邊的 1 所在的位元位置），最後再與 r 進行位或運算。這樣做的目的是為了將 state 中原本的 1 移動到新的位置，並且保持其他位元不變。

綜合以上三步，這段程式碼的作用是將具有特定數量的位元為1的二進位數字 state 轉換成下一個具有相同位元為1數量的二進位數字。因此，這樣的程式碼可以用來生成具有特定特徵的二進位數字的排列組合，例如只有兩個1的排列組合。
*/
