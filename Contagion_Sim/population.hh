#ifndef POP_H
#define POP_H
#include <vector>
#include "person.hh"
using namespace std;

//Function header for Population class
class Population{
	private:
		int count;
		float prob;
	public:
		vector<Person> populace;
		Population();
		Population(int n); 
		void set_probability(float probability);
		void random_infection();
		void random_vaccine(int m);
		void update();
		int count_infected();
		void update_spread();
		void print_pop();
		int survivors();
};
#endif
