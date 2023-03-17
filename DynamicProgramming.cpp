#include "Item.cpp"
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

// Knapsack class represents the knapsack problem
class DynamicProgramming {
public:
  void solve(long long NUM_ITEMS, long long MAX_WEIGHT, vector<Item> & items) {
    // Initialize the memoization table for dynamic programming
    vector<vector<long long>> memo(NUM_ITEMS + 10, vector<long long>(MAX_WEIGHT + 10, 0));
    vector<vector<long long>> keep(NUM_ITEMS + 10, vector<long long>(MAX_WEIGHT + 10, 0));
    // Fill the memoization table using a bottom-up approach
    for (long long i = 1; i <= NUM_ITEMS; i++) {
      for (long long j = 1; j <= MAX_WEIGHT; j++) {
        if (j < items[i - 1].weight) {
          // If the item doesn't fit, use the value without the item
          memo[i][j] = memo[i - 1][j];
          keep[i][j] = 0;
        } else {
          // Choose the maximum value between using the item and not using it
          if (memo[i - 1][j] > memo[i - 1][j - items[i - 1].weight] + items[i - 1].value) {
            memo[i][j] = memo[i - 1][j];
            keep[i][j] = 0;
          } else {
            memo[i][j] = memo[i - 1][j - items[i - 1].weight] + items[i - 1].value;
            keep[i][j] = 1;
          }
        }
      }
    }
    // Print the maximum value found
    cout << memo[NUM_ITEMS][MAX_WEIGHT] << endl;
    // Print the binary string showing which items are being taken
    long long w = MAX_WEIGHT;
    for (long long i = NUM_ITEMS; i > 0; i--) {
      if (keep[i][w]) {
        cout << "1";
        w -= items[i - 1].weight;
      } else {
        cout << "0";
      }
    }
    cout << endl;
    
  }
};
