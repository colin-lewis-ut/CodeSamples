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
	vector<int> infect_queue(0);//emptied once per "day"
	for (int i = 0; i < populace.size(); i++){
		if (populace[i].getstatus() > 0){
			vector<int> infect_cand(0);//emptied after each i
			if (populace[i-1].getstatus() == 0 && find(infect_queue.begin(), infect_queue.end(), i-1) == infect_queue.end()){
				infect_cand.push_back(i-1);
			}
			if (populace[i+1].getstatus() == 0 && find(infect_queue.begin(), infect_queue.end(), i+1) == infect_queue.end()){
				infect_cand.push_back(i+1);
			}
			for (int r = 0; r < 6; r++){//random encounters
				int contact = (count-1) * (float) rand()/(float) RAND_MAX;
				if (populace[contact].getstatus() == 0 
					&& find(infect_queue.begin(), infect_queue.end(),contact) == infect_queue.end()
					&& find(infect_cand.begin(), infect_cand.end(),contact) == infect_cand.end()) 
				{
				
						infect_cand.push_back(contact);
				}
			}

			for (int j = 0; j < infect_cand.size(); j++){
				float p = (float) rand()/(float)RAND_MAX;
				if (1-p <= prob){
					infect_queue.push_back(infect_cand[j]);
				}
			}	
		populace[i].update();
		infect_cand.clear();
		}
	}
	for (int k = 0; k < infect_queue.size(); k++) {
		populace[infect_queue[k]].infect(5);
	}
	infect_queue.clear();
}

void Population :: update(){
	for (int i = 0; i < populace.size(); i ++){
		populace[i].update();
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
	}
	cout << "spared: " << luckys << endl << " vaccinated: " << vacc << endl << " recovered: " << recovered << endl;
	return 0;
}

