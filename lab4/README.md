# Lab Assignment 4 - Scheduling your task	


### **Learning Outcome:**

1.	Scheduling your process with Real Time Scheduler on Linux
		

### In this assignment, 

1. Change your laboratory assignment 3 code to schedule your task which adheres to RM scheduling policy
How to approach the problem.

2. Use the Linux **sched_ setparam** and **sched_setschduler** API. Get the details of those API from your manual.

3. Note that you should first design your task based on theory where the inequality U <= URM is achieved. Then implement your task based on those parameters.

### Your report must include your design, code, output and discussion from your observation.

###Some info: *Linux has 99 (1-99) real time priority levels. At present Linux has 2 Real Time priority level implemented in the mainstream Linux Kernel, namely SCHED_FIFO and SCHED_RR (Round Robin). You need to understand how they work, then used SCHED_FIFO to achieve Rate Monotonic behavior for this assignment.*
