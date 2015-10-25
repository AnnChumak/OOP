#include "Lab.h"

using namespace std;

int main() {
	cout << "Entering info about executant: \n";
	Date birthDay1;
	cout << "Please enter date of birth: ";
	cin >> birthDay1;
	char * firstName1 = new char[255];
	cout << "Please enter first name: ";
	cin >> firstName1;
	char * lastName1 = new char[255];
	cout << "Please enter last name: ";
	cin >> lastName1;
	Date executionDay = Date(1, 12, 20015);
	Executant executant1 = Executant(firstName1, lastName1, birthDay1);
	cout << executant1 << endl << endl;

	Executant executant2 = Executant();
	Executant executant3 = Executant(executant1);

	cout << "Entering info about customer: \n";
	int service;
	cout << "Please enter number of service: ";
	cin >> service;
	char *address = new char[255];
	cout << "Please enter address: ";
	cin >> address;
	Customer customer1 = Customer((Service) service, address);
	cout << customer1 << endl << endl;

	Customer customer2 = Customer();
	Customer customer3 = Customer(customer1);

	cout << "Entering info about order: \n";
	Date executionDate;
	cout << "Please enter execution date: ";
	cin >> executionDate;
	Order order1 = Order(executant1, customer1, executionDate);
	cout << order1 << endl << endl;

	Order order2 = Order();
	Order order3 = Order(order1);

	cout << "Entering info about bureau: \n";
	char * bName = new char[255];
	cout << "Please enter bureau name: ";
	cin >> bName;
	Bureau bureau1 = Bureau(bName);
	bureau1.addOrder(order1);
	bureau1.addOrder(order1);
	bureau1.addOrder(order1);

	Bureau bureau2 = Bureau();
	Bureau bureau3 = Bureau(bureau1);

	cout
			<< "\n\nInfo------------------------------------------------------------ \nFirst Bureau:"
			<< endl;
	cout << bureau1;
	bureau1.info();
	cout << "Third Bureau:" << endl;
	cout << bureau3;
	bureau3.info();
	cout << "Lab complete!";

	return 0;
}
