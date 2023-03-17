#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "Item.cpp"
using namespace std;

// Global variables
long long MAX_WEIGHT; // maximum weight of the knapsack
long long NB_ITEMS; // number of items
long long NUM_GENERATIONS = 100; // number of generations
double MUTATION_RATE = 1; // probability of mutation
long long POP_SIZE = 100; // size of the population
vector<Item> items;
using namespace std;

// Individual class represents a candidate solution to the knapsack problem
class Individual {
public:
  std::vector<int> included; // items included in the solution
  long long fitness; // total value of the items
  long long weight; // total weight of the items
  Individual(long long num_items) {
    // Initialize the individual with random values
    this->fitness = 0;
    this->weight = 0;
    for (int i = 0; i < num_items; i++) {
      included.push_back(rand() % 2);
    }
    calculateFitness();
  }
  void calculateFitness() {
    // Calculate the fitness and weight of the individual
    this->fitness = 0;
    this->weight = 0;
    for (int i = 0; i < NB_ITEMS; i++) {
      if (included[i]) {
        this->fitness += items[i].value;
        this->weight += items[i].weight;
      }
    }
  }
};


class Population {
    public:
        std::vector<Individual> individuals;
        void initialize(long long num_items) {
        // Initialize the population with random individuals
        for (int i = 0; i < POP_SIZE; i++) {
            individuals.push_back(Individual(num_items));
        }
    }

    // void evaluateFitness() {
    //     // Calculate the fitness and weight of each individual
    //     for (int i = 0; i < individuals.size(); i++) {
    //         individuals[i].calculateFitness();  
    //     }
    //     return ;
    // }

    Individual selectParent() {
        // Select a parent using tournament selection
        std::vector<Individual> tournament;
        for (int i = 0; i < (POP_SIZE >= 10 ? POP_SIZE / 10 : 1); i++) {
            tournament.push_back(individuals[rand() % POP_SIZE]);
        }
        std::sort(tournament.begin(), tournament.end(), [](Individual a, Individual b) {
            return a.fitness > b.fitness;
        });
        return tournament[0];
    }

    void crossover(Individual &parent1, Individual &parent2, Individual &child) {
        // Create a child by crossover the parents at a random point
        long long crossover_point = rand() % NB_ITEMS;
        for (int i = 0; i < crossover_point; i++) {
            child.included[i] = parent1.included[i];
        }
        for (int i = crossover_point; i < NB_ITEMS; i++) {
            child.included[i] = parent2.included[i];
        }
    }
    
    void mutate(Individual &individual) {
    // Mutate the individual by flipping the value of a random item
        long long mutate_point = rand() % NB_ITEMS;
        individual.included[mutate_point] = !individual.included[mutate_point];
    }
    
    void createNextGeneration() {
        std::vector<Individual> new_individuals;
        
        while (new_individuals.size() < POP_SIZE) {
            // Select two parents using tournament selection
            Individual parent1 = selectParent();
            Individual parent2 = selectParent();
    
            Individual child(NB_ITEMS);
            crossover(parent1, parent2, child);
            

            // Mutate the child with a probability of MUTATION_RATE
            if (rand() < MUTATION_RATE * RAND_MAX) {
                mutate(child);
            }   

            // Add the child to the new population if it meets the constraints
            if (child.weight <= MAX_WEIGHT) {
                
                new_individuals.push_back(child);
            }
        }
        // Replace the current population with the new one
        individuals = new_individuals;
    }
    
    Individual getBest() {
    // Return the individual with the highest fitness
        std::sort(individuals.begin(), individuals.end(), [](Individual a, Individual b) {
            return a.fitness > b.fitness;
        });
        return individuals[0];
    }
};



vector<Item> readInput(const char * path){
    // To enable reading from file
    freopen(path, "r", stdin);
    vector<Item> problem;

    cin >> NB_ITEMS >> MAX_WEIGHT;

    for(int i = 0; i < NB_ITEMS; i++){
        long long value, weight;
        cin >> value >> weight;
        Item curItem(weight, value);
        problem.push_back(curItem);
    }
    return problem;
}


int main(int argc, char** argv) {
    // Create a list of items with random weights and values from a file
    freopen(argv[2], "w", stdout);
    char * path = argv[1];
    items = readInput(path);
    
    // Create the initial population
    Population population;
    population.initialize(items.size());
    
    // Evaluate the fitness of the individuals
    // population.evaluateFitness();
    
    // Run the genetic algorithm for the specified number of generations
    for (int i = 0; i < NUM_GENERATIONS; i++) {
        population.createNextGeneration();
        // population.evaluateFitness();
    }
    // Print the best solution found
    Individual best = population.getBest();
    cout  << best.fitness << endl;    
    for (int i = 0; i < NB_ITEMS; i++) {
        cout << best.included[i] << " ";
    }
    cout << endl;
    return 0;
}



