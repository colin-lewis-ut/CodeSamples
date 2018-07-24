#include <iostream>
#include "population.hh"
#include <algorithm>
#include <vector>
#include "time.h"
using namespace std;

//The whole burrito; this is where the good stuff is: 'Population' Def's

//default constructor
Population :: Population(){
	cout << "default population set to ten" << endl;
	count = 10;
	prob = 1;
	vector<Person> temp(10);//by default, a populaiton is a vector of 10 people; customizable below
	populace = temp;
}

//Custom definition
Population :: Population(int n){
	count = n;
	prob = 1;
	vector<Person> temp(n);
	populace = temp;
}


//sets probability of transmission based on input in 'main'
void Population :: set_probability(float probability){
	prob = probability;
}

//Chooses an patient zero independent of population size
void Population :: random_infection(){
	bool success = false;
	while (success == false){
		float t = count * (float) rand()/(float)RAND_MAX;
		int c = t; //this assignment will always be within bounds of population, but may not be optimal method.
		success = populace[c].infect(5);
	}
}

//Innoculates a percentage of the population based on a provided percentage
void Population :: random_vaccine(int m){
	vector<int> previous(0);
	int tally = 0;
	while (tally < m){
		int select = (count) * (float) rand()/(float)RAND_MAX;
		if (find(previous.begin(), previous.end(), select) == previous.end()){ //Prevents double innoculation, in order to achieve desired percentage
			populace[select].setstatus(-2);
			previous.push_back(select);
			tally ++;
		}
	}

}

//Upates each individual in the population by calling method in 'person'
void Population :: update(){
	for (int i = 0; i < populace.size(); i ++){
		populace[i].update();
	}
}

//returns the integer number of infected individuals
int Population :: count_infected(){
	int tally = 0;
	for (int i = 0; i < populace.size(); i ++){
		if (populace[i].getstatus() > 0){
			tally ++;
		}
	}
	return tally;
}

//Passes the contagion to neighbors and through random 'encounter' permutations.
void Population :: update_spread(){
	for (int i = 0; i < populace.size(); i++){
		if (populace[i].getstatus() > 0){ //Candidates are marked with -4
			if (populace[i-1].getstatus() == 0){
				populace[i-1].setstatus(-4);
			}

			if (populace[i+1].getstatus() == 0){
				populace[i+1].setstatus(-4);
			}

			for (int r = 0; r < 6; r++){//random encounters
				float rando = (float) rand()/(float) RAND_MAX;
				int contact = count * rando;
				if (populace[contact].getstatus() == 0){
					populace[contact].setstatus(-4);
				}
				contact = 0;
			}
			

			for (int j = 0; j < populace.size(); j++){ //infects the correct percentage of candidates for infection. selections are staged
				if (populace[j].getstatus() == -4){
					float p = (float) rand()/(float)RAND_MAX;
					if (1-p <= prob){
						populace[j].setstatus(-3);
					}
					else populace[j].setstatus(0);
				}
			}
		}
		populace[i].update();//updates the population BEFORE infecting next iteration, so as to preserve disease duration
	}
	for (int k = 0; k < populace.size(); k++) {//selected individuals are infected
		if (populace[k].getstatus() == -3) {
			 populace[k].infect(5);
		}
	}
}

//Provides a graphical representation of the population for the terminal
void Population :: print_pop(){
	for (auto member : populace){
		int s = member.getstatus();
		switch(s) {
			case(0): cout <<"?";
					 break;
		    case(-1):cout << "-";
					 break;
		    case(-2): cout <<"X";
					 break;
			default: cout << "+";
					 break;
			}
	}
	cout << endl;
}

//returns the number of unvaccinated individuals who reman at the end of the contagion; other stats written to terminal
int Population :: survivors(){
	int luckys = 0;
	int  vacc = 0;
	int recovered = 0;
	for (int i = 0; i < populace.size(); i ++){//tallies individual statuses while iterating through loop
		if (populace[i].getstatus() == 0) luckys ++;
		else if (populace[i].getstatus() == -2) vacc ++;
		else recovered ++;
		populace[i].setstatus(0);
	}
	cout << "spared: " << luckys << endl << " vaccinated: " << vacc << endl << " recovered: " << recovered << endl;
	return luckys;
}

