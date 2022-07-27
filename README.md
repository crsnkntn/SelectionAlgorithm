# Basic Selection Algorithm
I wrote this in order to explore templates. This is a precursor to the EconomySimulation project also found on my github. Looking back, the structure of the Thing/FitnessGauge system is faulty. The Thing should not have ownership of its fitness score or chosen string, instead the Thing should be more of a container for a certain state; this state is then used by the Selection Mechanism to calculate scores and fitness. I do not feel a need to change it because this works perfectly fine.
This short project shows a population of small genomes that, every iteration, each choose a string from a long list; choosing a wrong string disallows that genome from replicating. The point is just to explore how long it takes for the population to converge when tinkering with the mutation rate, population size, and genome size.

There is also a python script for filling a txt file with random numbers since C is not good at creating genuinely random numbers.
