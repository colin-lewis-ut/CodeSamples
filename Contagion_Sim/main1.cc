#include <iostream>
#include "person.hh"

using namespace std;

int main() {
	Person joe;
	int step = 0;
	bool toggle = 0;
	while (toggle == 0){
		step +=1;
		joe.update();
		float bad_luck = (float) rand()/(float) RAND_MAX;
		if (bad_luck>1.0){
		   joe.infect(5);
		}

		joe.status_string();
		toggle = joe.is_stable();
	}
	cout << "The contagion lasted " << step << " days" << endl;
	return 0;
}
