#include "Billing.h"
#include <iostream>
#include <iomanip>

using namespace std;

Billing::Billing() {
	int base = sqlite3_open("billing.db", &db);
	if (base) {
		cerr << "Unable to Open Database: " << sqlite3_errmsg(db) << endl;
		exit(1);
	}
	initializeDatabase();

}

Billing::~Billing() {
	sqlite3_close(db);
}

void Billing::initializeDatabase() {
	const char* itemTable =
		"CREATE TABLE IF NOT EXISTS Items("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"name TEXT NOT NULL, "
		"quantity INTEGER, "
		"price REAL);";
	const char* billTable = 
		"CREATE TABLE IF NOT EXISTS Bills ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"total REAL, "
		"tax REAL, "
		"date TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";
	const char* customerTable =
		"CREATE TABLE IF NOT EXISTS Customers ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"name TEXT NOT NULL, "
		"email TEXT, "
		"phone TEXT);";
	const char* creditCardTable =
		"CREATE TABLE IF NOT EXISTS CreditCards ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"customer_id INTEGER, "
		"cardNumber TEXT, "
		"expiration TEXT, "
		"FOREIGN KEY(customer_id) REFERENCES customers(id));";

	char* errMsg = nullptr;
	sqlite3_exec(db, itemTable, nullptr, nullptr, &errMsg);
	sqlite3_exec(db, billTable, nullptr, nullptr, &errMsg);
	sqlite3_exec(db, customerTable, nullptr, nullptr, &errMsg);
	sqlite3_exec(db, creditCardTable, nullptr, nullptr, &errMsg);


}

void Billing::addItemProduct() {
	itemProduct item;
	cout << "\nEnter Item Name: ";
	cin.ignore();
	getline(cin, item.name);
	cout << "Enter Item Quantity: ";
	cin >> item.quantity;
	cout << "Enter Item Price: ";
	cin >> item.price;

	string sql = "INSERT INTO Items (name, quantity, price) VALUES (?, ?, ?);";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, item.name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, item.quantity);
	sqlite3_bind_double(stmt, 3, item.price);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	cout << "Item Added to Database!\n";


}
void Billing::addCustomer() {
	customers c;
	cout << "\nEnter Customer Name: ";
	cin.ignore();
	getline(cin, c.name);
	cout << "Enter Customer Email: ";
	getline(cin, c.email);
	cout << "Enter Customer Phone Number: ";
	getline(cin, c.phoneNumber);


	string sql = "INSERT INTO Items (name, email, phone number) VALUES (?, ?, ?);";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, c.name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, c.email.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, c.phoneNumber.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	cout << "Customer Added to Database!\n";

}

void Billing::addCreditCard() {
	int customer_id;
	creditCard c;
	cout << "\nEnter Customer Credit Card ID: ";
	cin>> customer_id;
	cin.ignore();
	cout << "Enter Card Number: ";
	getline(cin, c.cardNumber);
	cout << "Enter Card Expiration (MM/YY): ";
	getline(cin, c.expiration);


	string sql = "INSERT INTO Items (name, email, phone number) VALUES (?, ?, ?);";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_int(stmt, 1, customer_id);
	sqlite3_bind_text(stmt, 2, c.cardNumber.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, c.expiration.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	cout << "Credit Card Added to Database!\n";

}



void Billing::billReceipt() {
	const char* sql = "SELECT name, quantity, price FROM Items;";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	double subtotal = 0;

	cout << "\n------------BILL RECEIPT------------\n";
	cout << left << setw(20) << "Item Name"
		<< setw(10) << "QTY"
		<< setw(10) << "Price"
		<< setw(10) << "Total\n";
	cout << "------------------------------------------\n";

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		int quantity = sqlite3_column_int(stmt, 1);
		double price = sqlite3_column_double(stmt, 2);
		double total = quantity * price;

		cout << left << setw(20) << name
			<< setw(10) << quantity
			<< "$" << setw(9) << fixed << setprecision(2) << price
			<< "$" << fixed << setprecision(2) << total << "\n";
		subtotal += total;
	}

	sqlite3_finalize(stmt);

	double tax = subtotal * taxRate;
	double grandTotal = subtotal + tax;

	string insertBill = "INSERT INTO Bills (total, tax) VALUES (?, ?);";
	sqlite3_prepare_v2(db, insertBill.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_double(stmt, 1, grandTotal);
	sqlite3_bind_double(stmt, 2, tax);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	cout << "----------------------------------------------\n";
	cout << left << setw(30) << "Subtotal:" << "$" << fixed << setprecision(2) << subtotal << "\n";
	cout << left << setw(30) << "Tax (5%)::" << "$" << fixed << setprecision(2) << tax << "\n";
	cout << left << setw(30) << "Total Amount:" << "$" << fixed << setprecision(2) << grandTotal << "\n";
	cout << "----------------------\n\n";



}

void Billing::run() {
	int c;

	do {
		cout << "======== Billing System DataBase ========\n";
		cout << "1. Add Item\n";
		cout << "2. Add Customer\n";
		cout << "3. Add Credit Card\n";
		cout << "4. View Bill\n";
		cout << "5. Exit\n";


		cout << "Choose an Option: ";
		cin >> c;

		switch (c) {
		case 1:
			addItemProduct();
			break;
		case 2:
			addCustomer();
			break;
		case 3:
			addCreditCard();
			break;
		case 4:
			billReceipt();
			break;
		case 5:
			cout << "Exiting... \n";
			break;
		default:
			cout << "Invalid choice.\n";
		}




	} while (c != 3);
}