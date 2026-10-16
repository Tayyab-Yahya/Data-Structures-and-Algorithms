#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// KNAPSACK:
// Knapsack means a type of bag in which we put items. And we try to get the maximum value out of the values.

// KNAPSACK PATTERNS:
// There are total 3 patterns:

    // 1- Fractional Knapsack (Greedy)
        // We put items into our knapsack in fractions like half jar of salt etc.

    // 2- 0-1 Knapsack        (DP)
        // We put items into our knapsack as whole like a pen or a laptop which will be placed or not in our knapsack.

    // 3- Unbounded Knapsack  (DP)
        // In unbounded knapsack, there is no limit on the quantity of the items we can put into our knapsack.

// Here, we'll discuss the fractional knapsack.

// Comparator
static bool compare(vector<int>& a, vector<int>& b) {
    double a1 = (1.0 * a[0]) / a[1];
    double b1 = (1.0 * b[0]) / b[1];
    return a1 > b1;
}

double fractionalKnapsack(vector<vector<int>>& items, int K) {
    
    // Sorting on the basis of wt/val using "compare" comparator
    sort(items.begin(), items.end(), compare);

    double result = 0.0;

    for(auto item : items) {
        int val = item[0], wt = item[1];
        
        if(wt <= K) {
            result += val;
            K -= wt;
        } else {
            result += (val / wt) * K;
            K = 0;
            break;
        }
    }

    return result;
}

int main() {
    vector<vector<int>> items = {
        {60, 10},
        {100, 20},
        {120, 30},
        {80, 40},
        {150, 15}
    }; // {val, wt}

    int K = 60;

    cout << fractionalKnapsack(items, K) << endl;
    
    return 0;
}