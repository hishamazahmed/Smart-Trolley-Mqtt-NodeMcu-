# Smart-Trolley#Floor18#Group-4

We see long queues in the billing counters of the superstore. This queues uses a lot of time for the customers, reducing custom er
satisfaction as well as reduced superstore business. Moreover, they get confused about the total bill before going to the counters.

We came up with a solution prototype for this specific problem.  With this system, there is no need for customer to wait 
in the queue for the scanning for the product items for billing purpose. What we propose is that the customer scan the item in
the trolley and the bill is shown on a LCD in the trolley.When all required items have been scanned, the customer presses a button,
which sends the total bill information to the POS of the superstore.

Detailed Working Principle:

We are using UART RFID with Intel Edison. When a RFID tag is scanned in the Edison, a node.js script reads the RFID tag and sends
the UID to the Python Flask Server. The server checks the number in the mongoDB database. If the number is found, the price and 
item details are extracted and sent back as a response to the Edison. The item name and total bill is shown on the LCD in the 
trolley. 

The process is repeated for more items scanned. When the button is pressed, all the items details are sent to the POS system. 
The customer then proceeds to the billing counter and pays the total amount.
