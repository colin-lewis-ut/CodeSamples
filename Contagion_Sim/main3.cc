#include <iostream>
#include <vector>
#include "population.hh"

using namespace std;

int main() {
	srand(time(NULL));
	float prob;
	cout << "Enter the probability of infection" << endl;
	cin >> prob;
	int days = 0;
	Population Pop(200);
	Pop.set_probability(prob);
	Pop.print_pop();
	Pop.random_infection();
	do{
		Pop.print_pop();
		Pop.update_spread();
		days += 1;
	}while (Pop.count_infected() > 0);
	Pop.print_pop();
	cout << "the infection lasted " << days << " days." << endl;
	return 0 ;
}

			                  
