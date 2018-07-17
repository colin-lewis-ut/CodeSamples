#ifndef PERSON_H
#define PERSON_H
class Person{
	private:
		int status;
	public:
		Person();
		int getstatus();
		void setstatus(int n);
		void status_string();
		void update();
		bool infect(int n);
		bool is_stable();
	};
#endif
