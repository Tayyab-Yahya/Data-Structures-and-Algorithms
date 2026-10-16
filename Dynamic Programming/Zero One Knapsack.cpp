// DP Pattern: 0/1 Knapsack

// One of the DP patterns is 0/1 Knapsack.
// Knapsack means a bag into which, we can put items.
// 0/1 Knapsack means you can either add a thing into the knapsack or you can completely skip that particular item based on the available space in the knapsack. Like a pen, a laptop etc.
// There is nothing like adding a part (fraction) of some item into our knapsack. Like half of salt jar etc.

// 0/1 Knapsack is one of the most important patterns of dynamic programming.

// To solve a 0/1 Knapsack problem, we will be using three approaches:
    // 1) Recursion (Brute force)
    // 2) Memoization DP
    // 3) Tabulation DP (Most optimized approach)

#include <iostream>
#include <vector>
using namespace std;

// TC = O(2^n)
// SC = O(n) => Recursion Call-stack
double knapsack01_Rec(vector<vector<int>>& items, int W, int n) {
    if(n == 0 || W == 0) return 0;

    int val = items[n-1][0], wt = items[n-1][1];
    
    if(wt <= W) {
        int include = val + knapsack01_Rec(items, W - wt, n-1);
        int exclude = knapsack01_Rec(items, W, n-1);
        return max(include, exclude);
    } else {
        return knapsack01_Rec(items, W, n-1);
    }
}

// TC = O(n*W)
// SC = O(n*W) + O(n) => Recursion Call-stack
double knapsack01_MemDP(vector<vector<int>>& items, int W, int n, vector<vector<int>> &dp) {
    if(n == 0 || W == 0) return 0;

    if(dp[n][W] != -1) return dp[n][W];

    int val = items[n-1][0], wt = items[n-1][1];
    
    if(wt <= W) {
        int include = val + knapsack01_MemDP(items, W - wt, n-1, dp);
        int exclude = knapsack01_MemDP(items, W, n-1, dp);
        return dp[n][W] = max(include, exclude);
    } else {
        return dp[n][W] = knapsack01_MemDP(items, W, n-1, dp);
    }
}

// TC = O(n*W)
// SC = O(n*W)
double knapsack01_TabDP(vector<vector<int>>& items, int W, int n) {
    vector<vector<int>> dp(n+1, vector<int> (W+1, 0));

    for(int i=1; i<=n; i++) { // i items
        for(int j=1; j<=W; j++) { // j-sized knapsack
            int val = items[i-1][0];
            int wt = items[i-1][1];

            if(wt <= j) {
                dp[i][j] = max(val + dp[i-1][j-wt], dp[i-1][j]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp[n][W];
}

int main() {
    vector<vector<int>> items = {
        {20, 2},
        {30, 3},
        {50, 4},
        {60, 5},
        {100, 9}
    }; // {val, wt}

    int W = 10;
    vector<vector<int>> dp(items.size()+1, vector<int> (W+1, -1));

    // cout << knapsack01_MemDP(items, W, items.size(), dp) << endl;

    cout << knapsack01_TabDP(items, W, items.size()) << endl;
    
    return 0;
}