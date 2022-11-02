```
#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
```

```
int decrease_count(int count)
{
    if (available_resources < count)
        return -1;
    else
    {
        available_resources -= count;
        return 0;
    }
}

/* increase available resources by count */
int increase_count(int count)
{
    available_resources += count;
    return 0;
}
```
a. Identify the data involved in the race condition
Ans. available_resources

b.  Identify the location (or locations) in the code where the race condition occur
Ans. available_resources -= count; 
     available_resources += count;

c. Using a semaphore or mutex lock, fix the race condition. It is permissible to modify the decrease count() function so that the calling process is blocked until sufficient resources are available

A semaphore is simply an integer variable that is shared between threads. This variable is used to solve the critical section problem and to achieve process synchronization in the multiprocessing environment. All modifications to the integer value of the semaphore in the wait() and signal() operations must be executed atomically. The implementation of mutex locks suffers from busy waiting. The definitions of wait() and signal() semaphore operations suffer form the same problem. To overcome this problem, we can modify the definition of the wait() and signal() operations. 

```
  typedef struct 
  {
    int value;
    struct process *list;
  } semaphore;
  ```
  
  ```
  wait(semaphore *S) {
    S->value--;
    if (S->value < 0) {
      add this process to S->list;
      sleep();
    }
  }
  ```
  
  ```
  signal(semaphore *S) {
    S->value++;
    if (S->value <= 0) {
      remove a process P from S->list;
      wakeup(P);
    }
  }
```