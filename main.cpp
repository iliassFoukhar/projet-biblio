#include "DynamicProgramming.cpp"
#include <vector>
using namespace std;



long long NUM_ITEMS, MAX_WEIGHT;

vector<Item> readInput(const char * path){
    // To enable reading from file
    freopen(path, "r", stdin);
    vector<Item> problem;

    cin >> NUM_ITEMS >> MAX_WEIGHT;
    for(int i = 0; i < NUM_ITEMS; i++){
        long long value, weight;
        cin >> value >> weight;
        Item curItem(weight, value);
        problem.push_back(curItem);
    }
    return problem;
}

int main(int argc, char** argv) {
    // To output results in file
    // const char * outputfile = (char*)"./ResultsDP/" + argv[2];
    freopen(argv[2], "w", stdout);
    // Create a knapsack with a random maximum weight
    DynamicProgramming dp;
    
    // Take path from input
    char * path = argv[1];
    
    // Generate a problem
    vector<Item> problem = readInput(path);

    // Solve the knapsack problem and print the result
    dp.solve(NUM_ITEMS, MAX_WEIGHT, problem);
    
    return 0;
}