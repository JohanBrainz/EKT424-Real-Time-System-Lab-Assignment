# Lab Assignment 5 - Multithread Real Time Task


### **Learning Outcome:**

1. Create multithreads in a single process by means of PThread library API'.

2. Implement periodic threads with primitive linux functions like **sleep()**, **ulseep()**, **nanosleep()**.

3. Implement Real Time Scheduling of PThread threads.


In this assignment, we are shifting from multi process to multi threads. By means of the **pthread_create()** and **pthread_join()** OR **pthead_detached()** function (if you want to), create 3 different threads.

1. The first thread should mimics acquiring a temperature value from the equation below:

	``temperature = LOWER_TEMP_BOUND + (int)(UPPER_TEMP_BOUND * rand()/(RAND_MAX+1.0));``

and return the value to the calling main thread.

2. The second thread should mimics acquiring a pressure value from the equation below:

	``presure = LOWER_PRESURE_BOUND + (int)(UPPER_PRESURE_BOUND * rand()/(RAND_MAX+1.0));``

and return the value to the calling main thread.

3. The third thread should receive both of this value and display them to the screen.

4. The pressure and temperature value must be sampled at every 3.5 and 4 seconds respectively.

5. The third thread period is also 4 seconds and it should only be executed after both thread1 and 2 is executed. To achieved this requirement you will need to assign the priority and schedule the threads correctly.