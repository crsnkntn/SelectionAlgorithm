The header file evolution.h enables the creation of a population of Things which can be sorted and 
replicated based upon a Fitness Gauge. The Thing and Fitness Gauge are both template classes, which
allows a wide range of possible uses.

The Thing class requires the implementation of the mutate function and an overload of the less than operator. Thing contains its own fitness in order to easily sort them.

The FitnessGauge class should be an object which contains a fitness measurement and data relating to how this measurement was reached. An overload of the less than operator is also required.

The Selector class utilizes the sorting of Things in order to simulate a population changing over time according to the FitnessGauge of their environment.


As an example implementation of these classes is given in main.cpp, with the simulation of a 
population of Things which, in this case, contain a list of numbes. The list of numbers in the 
Thing class is systematically compared to the list of words given as the Fitness Gauge. Each list 
of numbers will result in a different score when compared to each word and the difference between 
this resultant score and the inputed target score is stored in the thing, along with the chosen 
word. These scores are used to sort the things. The sorting is done until every Thing in the 
population returns the same word. I am not exactly sure how this is useful yet, but it was vaguely 
inspired by Wordle.

To compile the main file put in:

g++ --std=c++11 main.cpp -o a <OUTPUT FILE> > <POPULATION FILE> <WORDS FILE> <TARGET FITNESS> 
<GROWTH MAX> <GENERATIONS>

Note: There is currently a linker error, working on fixing it

There is also a python script for filling a txt file with random numbers.
