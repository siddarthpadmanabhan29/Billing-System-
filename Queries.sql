-- Testing SQL Queries for Data Implementation 
Select Customers.name, CreditCards.cardNumber, Bills.total, Bills.date 
From Customers
Join CreditCards ON Customer.id = CreditCards.customer_id
Join Bills ON bils.id = (Select MAX(id) From Bills)
Where Bills.total > 100;
