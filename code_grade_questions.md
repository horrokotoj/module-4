# Mutual Exclusion
## Explain the following concepts and relate them to the source code and the behaviour of the program.

### a) Critical section.
```bash
An operation or set of operations that risk a race condition.
E.g. the incrementation.
```
### b) Mutual exclusion (mutex).
```bash
Only one thread should be allowed acces to the critical section at one time.
```
### c) Race condition.
```bash
If output is dependant of the sequence of execution.
```
### d) Data race.
```bash
When two instructions from different threads access the same memory location and:
 - at least one of these accesses is a write
 - and there is no synchronization that is mandating any particular order among these accesses.

 If there is not mutual exclusion in regards to the critical sections a data race will occure as the threads race towards incrementing.
```

## Locks and semaphores:
### a) What is the purpose of mutex locks?
```bash
To provide a lock which only the task locker can unlock.
```

### b) If you had to make a choice between using a sempahore or a mutex to enforce mutex, what would you recommend and why?
```bash
Mutex since a semaphore allows anyone to "open" the lock.
```

### c) How do you consruct a spinlock using the atomic test-and-set instruction?
```bash
If we put test-and-set as the condition in a while loop we will have implemented a spinlock.
```

## Performance analysis:

### Discuss and analyze the results in test summary table.
```bash
From slowest to quickest:
Spinlock has the worst throughput. This is probabley due to the fact that alot of resources are wasted looping to see if the lock is available. What we see is throughput and not latency. Latency is really spinlocks speciality. 
Pthred mutex has middle throughput. 
Atomic add/sub has the highest throughput. To only make the increment/decrement atomic (which the others also implement) is fastest. Since this just makes this section uninteruptable this means much lower overhead.
```

# Rendezvous
### Explain the concept of rendezvous.
```bash
To have a checkpoint to synchronize with other tasks.
```
### What will happen when you wait on a semaphore?
```bash
The thread waiting for a semaphore will not be running, instead it will be waiting in the ready queue. When you get the semaphore, its value will be decreased.
```
### What will happen when you signal on a semaphore?
```bash
The semaphore value will be increased and if there is a task waiting for the semaphore it will be signaled.
```
### How can semaphores be used to enforce rendezvous between two threads?
```bash
By having two semaphores where each thread waits for one semaphore and signals the other.
```
### How are mutex locks different compared to semaphores?
```bash
Mutex locks are bound to be unlocked by the same task that locked them. 
A semaphore is not limited to be initialized to one, meaning several tasks may use the same semaphore 
```
### Why can’t mutex locks be used to solve the rendezvous problem?
```bash
Since a mutex lock can not unlock another tasks lock it can not be implemented in the signaling way that we need for a lockstep.
```

# Bounded buffer

### What do we mean by a counting semaphore?
```bash
A semaphore not initialized to one.
```
### What happens when you do wait on a counting semaphore?
```bash
Decrease its value by one or wait if it is zero.
```
### What happens when you do signal on a countng semaphore?
```bash
Increase its value by one.
```
### Explain how producers and consumers are synchronized in order to:
(Using EMPTY semaphore & DATA semaphore)
#### a) block consumers if the buffer is emtpy
```bash
The consumer waits for the data semaphore which the producer signals.
```
#### b) block producers if the buffer is full.
```bash
The producer waits for the empty semaphore (initialized to the size of the buffer) which the consumer signals.
```
### Explain why mutex locks cannot be used to synchronize the blocking of consumers and producers.
```bash
Cannot signal another mutex lock like you do with semaphores.
```
### Explain why you must ensure mutal exlusive (mutex) when updating the buffer array and the in and out array indexes.
```bash
if read write happens at the same time strange things will happen.
```
### Explain how you achive mutual exclusion (mutex) when updating the buffer array and the in and out array indexes.
```bash
Using a binary semaphore which is waited for and signaled for in that order.
```
