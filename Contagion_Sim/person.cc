#include <iostream>
#include <string>
#include "person.hh"

//Class definition of 'Person'
using namespace std;
Person :: Person(){
    status = 0;
	//clean = 0, infected = n (days remaining), recovered = -1, immune = -2, infection staged = -3, infection candidate = -4
}

//returns status
int Person :: getstatus(){
	int t = status;
	return t;
}

//sets 'Person' status based on call in population
void Person :: setstatus(int n){
	status = n;
}

//legacy method used for troubleshooting
void Person :: status_string(){
	if (status == 0){
		cout << "suceptible" << endl;
	}
	else if (status == -1){
		cout<< "recovered" << endl;
	}
	else if (status == -2){
		cout << "vaccinated" << endl;
	}
	else {
		cout << "infected for " << status << " more days" << endl;
	}
}

//iterates 'Person's condition
void Person :: update(){
	if (status > 1){
		status = status - 1;
	}
	else if (status == 1){
		status = -1;
	}
	else {}
}

//Infects 'Person'
bool Person :: infect(int n){
	if (status == 0 || status == -3){
		status = n;
		return true;
	}
	else cout << "Immune" << endl;
	return false;
}

//Tracks stability
bool Person :: is_stable() {
	bool stable = 0;
	if (status == -1 || -2){ 
		stable = 1;
	}
return stable;
}





