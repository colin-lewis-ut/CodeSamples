#include <iostream>
#include <vector>
#include <fstream>
#include "population.hh"

using namespace std;

int main() {
	srand(time(NULL));
	float prob;
	float percent;
	int popsize = 100;
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
		if (days > 1000) break;
	}while (Pop.count_infected() > 0);
	Pop.print_pop();
	for (int i = 0; i < popsize; i ++){
		cout << Pop.populace[i].getstatus() << endl;
	}
	cout << "the infection lasted " << days << " days." << endl;
	ofstream myfile;
	myfile.open ("results.txt", ios::app);
	int surv = Pop.survivors();
	myfile << popsize << "," << prob << "," << vaccinated << "," << days << "," << surv << endl;
	myfile.close();
	return 0;
}

			                  
