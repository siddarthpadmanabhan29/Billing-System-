# Billing-System-
Created a Billing System that stores payments and customer information into a SQL database using SQLite from libraries.

Overview:
This is a project that I did using C++ and a SQL library Database called SQLite which is designed to store, manage, and retrieve information. 
This includes information regarding customers, items, payments, and billings. 
Since the information is stored in a .db file which is created when the program is ran for the first time, everytime the program is ran, it will save the billing information from the last pickoff. 

Data Information:
Customer:
  Customer ID
  Name
  Email Address
  Phone Number
  Billing 

Item:
  Item ID
  Name
  Price
  Quantity

Bill Term:
  Bill ID
  Total
  Tax
  Date

Credit Card:
  Card Id
  Customer ID
  Card Number
  Expiration 

Use Cases:
Add Item to the Bill:
The user creates and adds an item to the bill receipt and entering the name, price, and quantity.

Add Customer:
The user can add customer information by including their name, email, and phone number.

Add Credit Card:
The user can add credit card to the acount by simply inputting customer id, card number, and expiration date

View Bill:
The user can view the bill of what is stored in the inventory which is retrieved and see calculated subtotal, taxes, and the total amount which formatted like a receipt. 

Exit Db System:
The user can simply exit the billing system where information is stored in the database which can be retrieved at anytime.

