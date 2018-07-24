#include <iostream>
#include <vector>
#include <fstream>
#include "population.hh"

using namespace std;

int main() {
	srand(time(NULL)); //
	float prob;
	float percent;
	int popsize = 100;
	int vaccinated;
	bool infect_success = false;

	cout << "Enter the probability of infection" << endl;
	cin >> prob;
	cout << "Enter population % vaccinated" << endl;
	cin >> percent;

        //Preliminary values
	vaccinated = percent * popsize;
	Population Pop(popsize);
	Pop.set_probability(prob);
	Pop.random_vaccine(vaccinated);

        //Start infection
	Pop.print_pop();
	Pop.random_infection();
	int days = 0;

        //Main simulation loop
	do{
		Pop.print_pop();
		Pop.update_spread(); //core function of the sim; detailed in population.cc
		days += 1;
		if (days > 1000) break;
	}while (Pop.count_infected() > 0);
	Pop.print_pop();
	for (int i = 0; i < popsize; i ++){
		cout << Pop.populace[i].getstatus() << endl;
	}

	cout << "the infection lasted " << days << " days." << endl;

        //prints output to file

	ofstream myfile;
	myfile.open ("results.txt", ios::app);
	int surv = Pop.survivors();
	myfile << popsize << "," << prob << "," << vaccinated << "," << days << "," << surv << endl;
	myfile.close();
	return 0;
}

			                  
