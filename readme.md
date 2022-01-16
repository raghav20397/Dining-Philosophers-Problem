In this assignment we had to solve the Dining Philosophers' Problem with its variations.

1. Deadlock possible.
 In the first part there was no variation and we just had to make a C program with deadlock avoidance. A deadlock can arise in the unique case if all the 5 philosophers get hungry and decide to eat ath the same time, and, simultaneously all of them pick the fork to their left; OR,  all of them pick the fork to their RIGHT (since a philosopher can pick up one fork at a time). We have avoided this deaadlock situation by introducing a simple prootocol. So deadlock is avoided in my solution as follows: all the philosophers except the first one pick up the left fork first and then the second fork, and then begin to eat from the plate, but the first philosopher takes the fork to his/her RIGHT FIRST and then the left fork, and then eats from the plate. This prevents deadlock by avoiding the deadlock chain. Even if all the philosophers start eating at the exact same time, the first philosopher will pick the right fork, and the second won't be able to pick their left fork as its being used by philosopher 1, thus breaking the chain before it starts, as philosopher 2 is put to wait().


2. Deadlock possible.
 In the second part, there is a modification to the problem, that philosophers need two forks and any one of the 4 sauce bowls available on the table to eat from the plate. Here, again a deadlock is possible, and it is somewhat similar to the first problem and caused by the forks primarily. We have avoided this by modifying the first solutions.
 Whenever a philosopher is hungry (except the first philosopher) they pick up the left fork first, then the right one and then searches from the available bowls, starting from the first bowl, if it is being used then he/she goes to the second bowl and so on, but it is not possible that two consequetive philosophers are eating as 2 forks are needed, so if the first bowl is being used they simply take the second bowl.
 This is not the same for first philosopher, he/she picks up the right fork first, then the left one and then searches from the available bowls STARTING FROM THE 4th sauce bowl, if its being used, then goes to 3rd bowl and so on. This avoids any 2 philosophers chosing the same bowl/searching from the same 2 bowls.

The most important thing used in both the programs is semaphore, which is basically a shared asset(integer) between threads and puts a check on threads if the asset is being used by another thread or not, it helps in achieving process synchronisation.


We run the code by linking it to pthread library by using -lpthread.


P.S: Ran both the programs for 10 minutes and no deadlock observed.
