to compile the final (best) form of the simulation with intel compiler:
icpc -c person.cc
icpc -c population.cc
icpc -g -o Sim.o maint.cc population.cc person.cc

