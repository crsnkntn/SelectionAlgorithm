#include "evolution.h"
#include <cstdio>


// StringThingPopulation File Structure is as follows:
//      numThings
//      thingSize
//      a_1_1 a_1_2 a_1_3 ... a_1_thingSize
//      .
//      .
//      .
//      a_numThings_1 a_numThings_2 a_numThings_3 ... a_numThings_thingSize

struct StringFitnessGauge {
    int fitnessScore;
    std::string fitness;
};

class StringThing : public Evolution::Thing<StringFitnessGauge> {
    private:
        std::vector<int> genes;

    public:
        StringThing (int thingSize, std::ifstream& fin) {
            int gene = 0;
            for (int j = 0; j < thingSize; j++) {
                fin >> gene;
                genes.push_back(gene);
            }
        }

        void mutate (int growth_max) override {
            int mutation_val = rand() % growth_max;
            int index = rand() % genes.size();

            if (rand() % 2 == 0) {
                genes[index] += mutation_val;
            }
            else {
                genes[index] -= mutation_val;
            }

            if (genes[index] == 0) {
                genes[index]++;
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const StringThing& thing);
};

std::ostream& operator<<(std::ostream& os, const StringThing& thing) {
    for (int i = 0; i < thing.genes.size(); i++)
        os << thing.genes[i] << " ";
    os << "\n";
    return os;
}

class StringSelector : public Evolution::Selector<StringFitnessGauge> {
    private:
        // implement the various fitness functions here
    public:
        StringFitnessGauge calculateFitness (StringThing* s, StringFitnessGauge g) {
            return {1, "Default"};
        }
};


int main (int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    if (argc < 4) {
        std::cout << "[ERROR] - Invalid Arguments" << std::endl;
        exit(1);
    }
    srand(4);
    std::vector<StringThing*> things;
    std::vector<StringFitnessGauge> words;

    // Read in the random numbers and words
    std::ifstream fin(argv[1]);
    int numThings = 0, thingSize = 0;
    fin >> numThings >> thingSize;
    for (int i = 0; i < numThings; i++) {
        things.push_back(new StringThing(thingSize, fin));
    }
    fin.close();

    fin.open(argv[2]);
    std::string word = "";
    while (fin >> word) {
        words.push_back({0, word});
    }
    fin.close();

    Evolution::Selector<Evolution::Thing<StringFitnessGauge>> selector(
        StringFitnessGauge {atoi(argv[3]), "TARGET_FITNESS"}, atoi(argv[4]),
        things.front(), things.back(),  words.front(), words.back()
    );

    for (int gen = 0; gen < atoi(argv[5]); gen++) {
        std::cout << "Generation " << gen << "\n"; 
        if (!selector.doGeneration()) {
            std::cout << "Convergence at " << gen << "\n";
        }
        selector.printPopulation();
    }
    selector.printPopulation();
    return 1;
}