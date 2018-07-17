#include <iostream>
#include "population.hh"
#include <algorithm>
#include <vector>
#include "time.h"
using namespace std;

Population :: Population(){
	cout << "default population set to ten" << endl;
	count = 10;
	prob = 1;
	vector<Person> temp(10);
	populace = temp;
}
Population :: Population(int n){
	count = n;
	prob = 1;
	vector<Person> temp(n);
	populace = temp;
}

void Population :: set_probability(float probability){
	prob = probability;
}

void Population :: random_infection(){
	bool success = false;
	while (success == false){
		float t = count * (float) rand()/(float)RAND_MAX;
		int c = t; //this assignment will always be within bounds of population, but may not be optimal method.
		success = populace[c].infect(5);
	}
}

void Population :: random_vaccine(int m){
	vector<int> previous(0);
	int tally = 0;
	while (tally < m){
		int select = (count) * (float) rand()/(float)RAND_MAX;
		if (find(previous.begin(), previous.end(), select) == previous.end()){
			populace[select].setstatus(-2);
			previous.push_back(select);
			tally ++;
		}
	}

}

void Population :: update(){
	for (int i = 0; i < populace.size(); i ++){
		populace[i].update();
	}
}

int Population :: count_infected(){
	int tally = 0;
	for (int i = 0; i < populace.size(); i ++){
		if (populace[i].getstatus() > 0){
			tally ++;
		}
	}
	return tally;
}

void Population :: update_spread(){
	for (int i = 0; i < populace.size(); i++){
		if (populace[i].getstatus() > 0){
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
			

			for (int j = 0; j < populace.size(); j++){
				if (populace[j].getstatus() == -4){
					float p = (float) rand()/(float)RAND_MAX;
					if (1-p <= prob){
						populace[j].setstatus(-3);
					}
					else populace[j].setstatus(0);
				}
			}
		}
		populace[i].update();
	}
	for (int k = 0; k < populace.size(); k++) {
		if (populace[k].getstatus() == -3) {
			 populace[k].infect(5);
		}
	}
}


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
int Population :: survivors(){
	int luckys = 0;
	int  vacc = 0;
	int recovered = 0;
	for (int i = 0; i < populace.size(); i ++){
		if (populace[i].getstatus() == 0) luckys ++;
		else if (populace[i].getstatus() == -2) vacc ++;
		else recovered ++;
		populace[i].setstatus(0);
	}
	cout << "spared: " << luckys << endl << " vaccinated: " << vacc << endl << " recovered: " << recovered << endl;
	return luckys;
}

