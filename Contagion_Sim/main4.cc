#include <iostream>
#include <vector>
#include "population.hh"

using namespace std;

int main() {
	srand(time(NULL));
	float prob;
	float percent;
	int popsize = 1000;
	int vaccinated;
	bool infect_success = false;

	cout << "Enter the probability of infection" << endl;
	cin >> prob;
	cout << "Enter population % vaccinated" << endl;
	cin >> percent;

	vaccinated = percent * popsize;
	Population Pop(popsize);
	Pop.set_probability(prob);
	Pop.random_vaccine(vaccinated);
	Pop.print_pop();
	Pop.random_infection();

	int days = 0;
	do{
		Pop.print_pop();
		Pop.update_spread();
		days += 1;
	}while (Pop.count_infected() > 0);
	Pop.print_pop();
	cout << "the infection lasted " << days << " days." << endl;
	Pop.survivors();
	return 0;
}

			                  
