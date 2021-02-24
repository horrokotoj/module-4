# Mutual Exclusion
## Explain the following concepts and relate them to the source code and the behaviour of the program.

### a) Critical section.
An operation or set of operations that risk a race condition.
### b) Mutual exclusion (mutex).

### c) Race condition.
### d) Data race.

## Locks and semaphores:
### a) What is the purose of mutex locks?
### b) If yoy had to make a choice between using a sempahore or a mutex to enforce mutex, what would you recommend and why?
### c) How do you consruct a spinlock using the atomic test-and-set instruction?

## Performance analysis:

### Discuss and analyze the results in test sumary table.

# Rendezvous
### Explain the concept of rendezvous.
### What will happen when you wait on a semaphore?
### What will happen when you signal on a semaphore?
### How can semaphores be used to enforce rendezvous between two threds?
### How are mutex locks different compared to semaphores?
### Why can’t mutex locks be used to solve the rendezvous problem?

# Bounded buffer

### What do we mean by a counting semaphore?
### What happens when you do wait on counting semaphore?
### What happens when you do signal on a countng semaphore?
### Explain how producers and consumers are synchronized in order to:
#### a) block consumers if the buffer is emtpy
#### b) block producers if the buffer is full.
### Explain why mutex locks cannot be used to synchronize the blocking of consumers and producers.
### Explain why you must ensure mutal exlusive (mutex) when updating the the buffer array and the in and out array indexes.
### Explain how you achive mutual exclusion (mutex) when updating the the buffer array and the in and out array indexes.