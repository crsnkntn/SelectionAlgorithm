#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <limits>

// TODO
//      add dtor and copy ctor to Thing
namespace Evolution {
    template <typename FitnessGauge>
    class Thing {
        private:
            FitnessGauge fitness;
    
        public:
            Thing () {}

            FitnessGauge getFitness () {
                return fitness;
            }

            void setFitness (FitnessGauge f) {
                fitness = f;
            }

            virtual void mutate (int growth_max);

            bool operator<(Thing& other) {
                return fitness < other.fitness;
            }
    };
    
    template <typename FitnessGauge>
    class Selector {
        private:
            FitnessGauge targetFitness;
            int mutation_rate;
            int growth_factor;
            typename std::vector<Evolution::Thing<FitnessGauge>*>::iterator population_front;
            typename std::vector<Evolution::Thing<FitnessGauge>*>::iterator population_back;
            typename std::vector<FitnessGauge>::iterator fitnessGauge_front;
            typename std::vector<FitnessGauge>::iterator fitnessGauge_back;

            virtual FitnessGauge calculateFitness (Thing<FitnessGauge> * s, FitnessGauge fg);

            void mutatePopulation () {
                for (auto i = population_front; i < population_back; i++) {
                    if (rand() % mutation_rate == 0)
                        *i.mutate(growth_factor);
                }
            }
        
        public:
            Selector (FitnessGauge tf, int gf, 
                typename std::vector<Evolution::Thing<FitnessGauge> *>::iterator pf,
                typename std::vector<Evolution::Thing<FitnessGauge> *>::iterator pb,
                typename std::vector<FitnessGauge>::iterator ff,
                typename std::vector<FitnessGauge>::iterator fb) 
                : targetFitness(tf), growth_factor(gf),
                    population_front(pf), population_back(pb),
                    fitnessGauge_front(ff), fitnessGauge_back(fb) {
                        if (pb - pf < 10) {
                            std::cout << "[ERROR] - Population of size " << pb - pf << " is too small." << std::endl;
                            exit(1);
                        }
                        mutation_rate = pb - pf / 10;
                    }

            ~Selector () {}

            Selector operator=(Selector& other) {
                targetFitness = other.targetFitness;
                growth_factor = other.growth_factor;
                mutation_rate = other.population_back - other.population_front / 10;
                population_front = other.population_front;
                population_back = other.population_back;
                fitnessGauge_front = other.fitnessGauge_front;
                fitnessGauge_back = other.fitnessGauge_back;
            }

            // Returns true if the population has converged to a single value
            bool doGeneration () {
                for (typename std::vector<Thing<FitnessGauge>*>::iterator i = population_front; 
                    i < population_back; i++) {
                        FitnessGauge bestFitnessMeasurement = (*i).getFitness();
                        for (std::vector<std::string>::iterator j = fitnessGauge_front; j < fitnessGauge_back; j++) {
                            FitnessGauge fitnessMeasurement = calculateFitness(*i, *j);
                            if (fitnessMeasurement - targetFitness < bestFitnessMeasurement)
                                bestFitnessMeasurement = fitnessMeasurement - targetFitness;
                        }
                        (*i).setFitness(bestFitnessMeasurement);
                }

                std::sort(population_front, population_back);
                typename std::vector<Thing<FitnessGauge>*>::iterator middle, front = population_front;
                middle += population_back - population_front;
                while (middle < population_back) {
                    *middle = *front;
                    middle++;
                    front++;
                }
                mutatePopulation();
                return true;
            }

            // Have a couple different printing settings
            void printPopulation () {
                for (auto i = population_front; i < population_back; i++) {
                    std::cout << *i << "\n";
                }
            }
    };
}
