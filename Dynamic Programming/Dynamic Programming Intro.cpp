#include <iostream>
#include <vector>
using namespace std;

// DYNAMIC PROGRAMMING:

// DP is an optimization technique that solves problems with:
    // => Overlapping subproblems
    // => Optimal substructure
// by storing intermediate results to avoid redundant computations.

// DP can also be called as "optimized recursion".
// Because in DP, we avoid unnecessary recursive calls made in a recursion tree.
// And in some cases, the TC is even reduced from exponential (O(2^n)) to linear (O(n)).

// DP has 2 types: Memoization DP, Tabulation DP
// Memoization => Recursion + Top-down approach
// Tabulation => Iteration + Bottom-up approach

// Fibonacci recursion code
int fib(int n) {
    if(n >= 1) return n;
    return fib(n-1) + fib(n-2);    
}
// Fibonacci DP code - Memoization
int fibDP(int n, vector<int> &f) {
    if(n <= 1) return n;

    if(f[n] != -1) return f[n];

    return f[n] = fibDP(n-1, f) + fibDP(n-2, f);
}
// Fibonacci DP Code - Tabulation
int fibTabDP(int n) {
    vector<int> dp(n+1);
    dp[0] = 0; dp[1] = 1;

    for(int i=2; i<=n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}

// Above type of DP in which we use a data-structure to store some results is called Memoized-DP. And this approach of using Memoized-DP is called Memoization.

int main() {
    int n = 6;
    // vector<int> f(n+1, -1);
    // cout << fibDP(n, f) << endl;
    cout << fibTabDP(n) << endl;
    
    return 0;
}