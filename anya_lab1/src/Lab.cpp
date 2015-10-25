#include "Lab.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////  DATE
Date::Date() {
	day = 1;
	month = 1;
	year = 1970;
}

Date::Date(int d, int m, int y) {
	if (isCorrect(d, m, y)) {
		day = d;
		month = m;
		year = y;
	} else {
		exit(EXIT_FAILURE);
	}
}

Date::Date(const Date &date) {
	day = date.day;
	month = date.month;
	year = date.year;
}

Date::~Date() {
	// ignored
}

bool Date::isCorrect(int day, int month, int year) {

	if (year <= 0 || month <= 0 || day <= 0) {
		return false;
	}

	if ((month == 1) || (month == 3) || (month == 5) || (month == 7)
			|| (month == 8) || (month == 10) || (month == 12)) {
		if (day <= 31) {
			return true;
		}
	}

	if ((month = 4) || (month = 6) || (month = 9) || (month = 11)) {
		if (day <= 30) {
			return true;
		}
	}

	if (month == 2) {
		bool isLeapYear = (year % 4) == 0;
		if (isLeapYear && day < 30) {
			return true;
		} else if (day < 29) {
			return true;
		}
		return true;
	}

	return false;
}

Date& Date::Set_Day(int d) {
	if (isCorrect(d, month, year))
		day = d;
	else
		exit(1);
	return *this;
}

Date& Date::Set_Month(int m) {
	if (isCorrect(day, m, year))
		month = m;
	else
		exit(EXIT_FAILURE);
	return *this;
}

Date& Date::Set_Year(int y) {
	if (isCorrect(day, month, y))
		year = y;
	else
		exit(EXIT_FAILURE);
	return *this;
}

ostream& operator<<(ostream &_cout, Date &date) {
	if (date.getDay() < 10)
		_cout << " 0" << date.day << ".";
	else
		_cout << date.day << ".";

	if (date.getMonth() < 10)
		_cout << "0" << date.month << ".";
	else
		_cout << date.month << ".";

	if (date.getYear() < 1000) {
		_cout << "0";
		if (date.year < 100) {
			_cout << "0";
			if (date.year < 10)
				_cout << "0" << date.year;
			else
				_cout << date.year;
		} else
			_cout << date.year;
	} else
		_cout << date.year;
	return _cout;
}

istream& operator>>(istream &_cin, Date &date) {
	_cin >> date.day >> date.month >> date.year;
	if (!date.isCorrect(date.day, date.month, date.year))
		exit(EXIT_FAILURE);
	return _cin;
}

////////////////////////////////////////////////////////////////////////////////////////////// EXECUTANT
Executant::Executant() {
	firstName = NULL;
	lastName = NULL;
	birthDay = Date();
}

Executant::Executant(char* fn, char* ln, Date d) {
	firstName = new char[strlen(fn) + 1];
	strcpy(firstName, fn);
	lastName = new char[strlen(ln) + 1];
	strcpy(lastName, ln);
	birthDay = Date(d);
}

Executant::Executant(const Executant& e) {
	firstName = new char[strlen(e.firstName) + 1];
	strcpy(firstName, e.firstName);
	lastName = new char[strlen(e.lastName) + 1];
	strcpy(lastName, e.lastName);
	birthDay = Date(e.birthDay);
}

Executant::~Executant() {
	if (firstName) {
		delete[] firstName;
	}
	if (lastName) {
		delete[] lastName;
	}
}

Date Executant::Get_Date() {
	return birthDay;
}

char* Executant::Get_First_Name() {
	return firstName;
}

char* Executant::Get_Last_Name() {
	return lastName;
}

Executant& Executant::Set_Date(Date d) {
	d = Date(d);
	return *this;
}

Executant& Executant::Set_First_Name(char* fn) {
	if (firstName) {
		delete[] firstName;
	}
	firstName = new char[strlen(fn) + 1];
	strcpy(firstName, fn);
	return *this;
}

Executant& Executant::Set_Last_Name(char* ln) {
	if (lastName) {
		delete[] lastName;
	}
	lastName = new char[strlen(ln) + 1];
	strcpy(lastName, ln);
	return *this;
}

ostream& operator<<(ostream &_cout, Executant &executant) {
	_cout << executant.firstName << " " << executant.lastName << ", "
			<< executant.birthDay;
	return _cout;
}

istream& operator>>(istream &_cin, Executant &executant) {
	_cin >> executant.firstName >> executant.lastName >> executant.birthDay;
	return _cin;
}

//////////////////////////////////////////////////////////////////////////////////////////////  CUSTOMER
Customer::Customer() {
	service = (Service) 0;
	address = NULL;
}

Customer::Customer(Service s, char* a) {
	service = s;
	address = new char[strlen(a) + 1];
	strcpy(address, a);
}

Customer::Customer(const Customer& c) {
	service = c.service;
	address = new char[strlen(c.address) + 1];
	strcpy(address, c.address);
}

Customer::~Customer() {
	if (address) {
		delete[] address;
	}
}

Service Customer::Get_Service() {
	return service;
}

char* Customer::Get_Address() {
	return address;
}

Customer& Customer::Set_Service(Service s) {
	service = s;
	return *this;
}

Customer& Customer::Set_Address(char* a) {
	if (address) {
		delete[] address;
	}
	address = new char[strlen(a) + 1];
	strcpy(address, a);
	return *this;
}

ostream& operator<<(ostream &_cout, Customer &customer) {
	_cout << customer.address << ", " << customer.service;
	return _cout;
}

istream& operator>>(istream &_cin, Customer &customer) {
	_cin >> customer.address; //  >> customer.service;
	return _cin;
}

///////////////////////////////////////////////////////////////////////////////////////////// ORDER

double Order::prices[5] = { 0.1, 0.2, 0.3, 0.4, 0.0 };

Order::Order() {
	date = Date();
	price = 0.0;
}

Order::Order(const Executant& e, const Customer& c, Date d) {
	executant = Executant(e);
	customer = Customer(c);
	date = Date(d);

	price = prices[(int) customer.Get_Service()];
}

Order::Order(const Order& o) {
	executant = Executant(o.executant);
	customer = Customer(o.customer);
	date = Date(o.date);
	price = o.price;
}

Order::~Order() {
	// ignored
	// memory leak - prices
}

Customer Order::Get_Customer() {
	return customer;
}

Executant Order::Get_Executant() {
	return executant;
}

Date Order::Get_Date() {
	return date;
}

double Order::Get_Price() {
	return price;
}

Order& Order::Set_Customer(const Customer& c) {
	customer = Customer(c);
	return *this;
}

Order& Order::Set_Executant(const Executant& e) {
	executant = Executant(e);
	return *this;
}

Order& Order::Set_Date(Date d) {
	date = Date(d);
	return *this;
}

ostream& operator<<(ostream &_cout, Order &order) {
	_cout << order.customer << ", " << order.executant << ", " << order.price
			<< ", " << order.date;
	return _cout;
}

istream& operator>>(istream &_cin, Order &order) {
	// empty
	return _cin;
}

////////////////////////////////////////////////////////////////////////////////////////////////BUREAU
static const int MAX_ORDERS_QUANTITY = 10;

Bureau::Bureau() {
	name = NULL;
	orders = new Order[MAX_ORDERS_QUANTITY];
	ordersQuantity = 0;
}

Bureau::Bureau(char *n) {
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	orders = new Order[MAX_ORDERS_QUANTITY];
	ordersQuantity = 0;
}

Bureau::Bureau(const Bureau& b) {
	name = new char[strlen(b.name) + 1];
	strcpy(name, b.name);
	orders = new Order[MAX_ORDERS_QUANTITY];
	for (int i = 0; i < b.ordersQuantity; i++) {
		orders[i] = Order(b.orders[i]);
	}
	ordersQuantity = b.ordersQuantity;
}

Bureau::~Bureau() {
	if (orders) {
		delete[] orders;
	}
	if (name) {
		delete[] name;
	}
}

Bureau& Bureau::Set_Name(char *n) {
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	return *this;
}

char* Bureau::Get_Name() {
	return name;
}

Order* Bureau::Get_Orders() {
	return orders;
}

void Bureau::addOrder(const Order& ord) {
	orders[ordersQuantity] = Order(ord);
	ordersQuantity++;
}

double Bureau::totalOrdersSum() {
	double total = 0.0;
	for (int i = 0; i < ordersQuantity; i++) {
		total += orders[i].Get_Price();
	}
	return total;
}

void Bureau::info() {
	cout << "Name: " << name << endl;
	cout << "Sum: " << Bureau::totalOrdersSum() << endl;
}

ostream& operator<<(ostream &_cout, Bureau &b) {
	_cout << b.name << ", " << b.ordersQuantity;
	for (int i = 0; i < b.ordersQuantity; i++) {
		_cout << b.orders[i] << endl;
	}
	return _cout;
}

istream& operator>>(istream &_cin, Bureau &b) {
	// empty
	return _cin;
}
