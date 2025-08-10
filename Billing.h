#pragma once
#include <string>
#include <sqlite3.h>

struct itemProduct {
	std::string name;
	int quantity;
	double price;
};

struct customers {
	std::string name;
	std::string email;
	std::string phoneNumber;
};

struct creditCard {
	int customer_id;
	std::string cardNumber;
	std::string expiration;
};

class Billing
{
private:
	sqlite3* db;
	const double taxRate = 0.05;
	void initializeDatabase();

public:
	Billing();
	~Billing();

	void addItemProduct();
	void addCreditCard();
	void addCustomer();
	void billReceipt();
	void run();



};
