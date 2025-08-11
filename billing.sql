-- How the Schema Relation is Performed
-- This can be tested by using a DB file for SQLlite or any DBMS of your choice

-- Items Table
CREATE TABLE IF NOT EXISTS Items (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  price REAL
);

-- View Bills Table
CREATE TABLE IF NOT EXISTS Bills (
  id INTEGER PRIMARY KEY AUTOINCREMENT, 
  total REAL, 
  tax REAL, 
  date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Customers Table
CREATE TABLE IF NOT EXISTS Customers (
  id INTEGER PRIMARY KEY AUTOINCREMENT, 
  name TEXT NOT NULL, 
  email TEXT, 
  phone TEXT
);

-- Credit Cards Table
CREATE TABLE IF NOT EXISTS CreditCards (
  id INTEGER PRIMARY KEY AUTOINCREMENT, 
  customer_id INTEGER, 
  cardNumber TEXT, 
  expiration TEXT, 
  FOREIGN KEY(customer_id) REFERENCES customers(id)
);

-- Including Sample Data of Each Statement
-- Items Sample for SQL Insertion
INSERT INTO Items (name, quantity, price) VALUES (Pizza, 2, 14.99);
INSERT INTO Items (name, quantity, price) VALUES (Pillows, 5, 35.17);

-- Bills Sample for SQL Insertion
INSERT INTO Bills (total, tax) VALUES (256.77, 12.84);
INSERT INTO Bills (total, tax) VALUES (8367.99, 418.40);

-- Customers Sample for SQL Insertion
INSERT INTO Customers (name, email, phone) VALUES (Dave Johnson, davejohnson@gmail.com, 617-234-1234);
INSERT INTO Customers (name, email, phone) VALUES (Camila Neal, camilaneal@hotmail.com, 555-653-5678);

-- Credit Cards Smaple for SQL Insertion
INSERT INTO CreditCards (customer_id, cardNumber, expiration) VALUES (1, 74938472349, 05/10);
INSERT INTO CreditCards (customer_id, cardNumber, expiration) VALUES (2, 21343214321, 12/25);




