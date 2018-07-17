#include <iostream>
#include <vector>
#include "population.hh"

using namespace std;

int main() {
	int days = 0;
	Population Pop(20);
	Pop.print_pop();
	Pop.random_infection();
	do{
		Pop.print_pop();
		Pop.update();
		days += 1;
	}while (Pop.count_infected() > 0);
	Pop.print_pop();
	cout << "the infection lasted " << days << " days." << endl;
	return 0 ;
}

			                  
