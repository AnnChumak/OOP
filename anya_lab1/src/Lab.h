#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstring>
#include <ctype.h>
#include "stdlib.h"

//////////////////////////////////////////////////////////////////////// DATE
class Date {
private:
	int day;
	int month;
	int year;

	static bool isCorrect(int, int, int);

public:
	Date();
	Date(int, int, int);
	Date(const Date &);
	~Date();

	int getDay() {
		return day;
	}
	int getMonth() {
		return month;
	}
	int getYear() {
		return year;
	}

	Date& Set_Day(int);
	Date& Set_Month(int);
	Date& Set_Year(int);

	friend std::ostream& operator<<(std::ostream&, Date&);
	friend std::istream& operator>>(std::istream&, Date&);
};

//////////////////////////////////////////////////////////////////////// SERVICE
enum Service {
	CLEANING, WINDOWS, CHILD, SMALL_FIX, MIXED
};

//////////////////////////////////////////////////////////////////////// EXECUTANT
class Executant {
private:
	char* firstName;
	char* lastName;
	Date birthDay;
public:
	Executant();
	Executant(char*, char*, Date);
	Executant(const Executant&);
	~Executant();

	char* Get_First_Name();
	char* Get_Last_Name();
	Date Get_Date();

	Executant& Set_First_Name(char*);
	Executant& Set_Last_Name(char*);
	Executant& Set_Date(Date);

	friend std::ostream& operator<<(std::ostream&, Executant&);
	friend std::istream& operator>>(std::istream&, Executant&);
	Executant& operator=(const Executant& executant) {
		Set_Date(executant.birthDay);
		Set_First_Name(executant.firstName);
		Set_Last_Name(executant.lastName);
		return *this;
	}
};

//////////////////////////////////////////////////////////////////////// CUSTOMER
class Customer {
private:
	Service service;
	char* address;
public:
	Customer();
	Customer(Service, char*);
	Customer(const Customer&);
	~Customer();

	Customer& Set_Service(Service);
	Customer& Set_Address(char*);

	Service Get_Service();
	char* Get_Address();

	friend std::ostream& operator<<(std::ostream&, Customer&);
	friend std::istream& operator>>(std::istream&, Customer&);

	Customer& operator=(const Customer& customer) {
		Set_Address(customer.address);
		Set_Service(customer.service);
		return *this;
	}
};

//////////////////////////////////////////////////////////////////////// ORDER
class Order {
private:
	Executant executant;
	Customer customer;
	Date date;
	double price;
	static double prices[5];
public:
	Order();
	Order(const Executant&, const Customer&, Date);
	Order(const Order&);
	~Order();

	Order& Set_Executant(const Executant&);
	Order& Set_Customer(const Customer&);
	Order& Set_Date(Date);

	Executant Get_Executant();
	Customer Get_Customer();
	Date Get_Date();
	double Get_Price();

	friend std::ostream& operator<<(std::ostream&, Order&);
	friend std::istream& operator>>(std::istream&, Order&);
	Order& operator=(const Order& order) {
		customer = order.customer;
		date = order.date;
		executant = order.executant;
		price = order.price;
		return *this;
	}
};

//////////////////////////////////////////////////////////////////////// BUREAU
class Bureau {
private:
	char * name;
	Order* orders;
	int ordersQuantity;

	double totalOrdersSum();
public:
	Bureau();
	Bureau(char* name);
	Bureau(const Bureau&);
	~Bureau();

	Bureau& Set_Name(char*);

	char* Get_Name();
	Order* Get_Orders();

	void addOrder(const Order&);
	void info();

	friend std::ostream& operator<<(std::ostream&, Bureau&);
	friend std::istream& operator>>(std::istream&, Bureau&);
};
