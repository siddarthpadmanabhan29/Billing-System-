-- How the Schema Relation is Performed

CREATE TABLE IF NOT EXISTS Items (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  price REAL
);
CREATE TABLE IF NOT EXISTS Bills (
  id INTEGER PRIMARY KEY AUTOINCREMENT, 
  total REAL, 
  tax REAL, 
  date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE IF NOT EXISTS Customers (
  id INTEGER PRIMARY KEY AUTOINCREMENT, 
  name TEXT NOT NULL, 
  email TEXT, 
  phone TEXT
);
CREATE TABLE IF NOT EXISTS CreditCards (
  id INTEGER PRIMARY KEY AUTOINCREMENT, 
  customer_id INTEGER, 
  cardNumber TEXT, 
  expiration TEXT, 
  FOREIGN KEY(customer_id) REFERENCES customers(id)
);

-- Including Sample Data
INSERT INTO Items (name, quantity, price) VALUES (Pizza, 2, 14.99);
INSERT INTO Items (name, quantity, price) VALUES (Pillows, 5, 35.17);

INSERT INTO Customers (name, email, phone) VALUES (?, ?, ?);
