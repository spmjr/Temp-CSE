
A constant for the central message queue is established with a value of 1000. Upon execution, the system ensures the presence of two additional command-line arguments: one for the process identifier and another for the starting temperature.

The identifier for the central message queue is then configured. Likewise, identifiers for the individual external process message queues are determined, with each ID derived from the sum of the central queue's constant value (1000) and the respective process ID.

The program enters a cycle of communication as follows: it persists in a loop as long as the message indicating the central process's temperature stability is not equal to 1. During this loop, it executes two main actions:

It dispatches a message to the central message queue.
It awaits and gathers a response from the corresponding external message queue.
Should the retrieved message indicate that stability has been achieved (stability flag set to 1), the loop is terminated, and the final temperature is reported. Otherwise, the process recalculates a new temperature based on the received data and continues the loop.


# Temp-CSE<img width="433" alt="Screenshot 2023-11-06 at 9 29 45 PM" src="https://github.com/spmjr/Temp-CSE/assets/97638846/8dc25be5-d3d5-426b-96d7-d2fc1da5b5dc">
