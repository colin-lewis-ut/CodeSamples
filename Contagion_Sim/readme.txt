to compile the final (best) form of my simulation:
icpc -c person.cc
icpc -c population.cc
icpc -g -o Sim.o maint.cc population.cc person.cc

to compile main4, a previous iteration of the final project:
icpc -c person.cc
icpc -c population4.cc
icpc -g -o Sim4.o main4.cc population4.cc person.cc
