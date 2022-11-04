//https://www.geeksforgeeks.org/use-posix-semaphores-c/
//https://www.geeksforgeeks.org/semaphores-in-process-synchronization/
//https://github.com/aitalshashank2/starve-free-reader-writers-problem

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;

struct PCB
{
    PCB *next;
    // All the other details of a process that a PCB contains
}

struct Queue
{

    ProcessControlBlock *front, *rear;

    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    // Function that pushes a PCB at the rear end of the queue
    void push(int pID)
    {
        ProcessControlBlock *pcb = new ProcessControlBlock();
        pcb->ID = pID;
        if (rear == nullptr)
        {
            front = pcb;
            rear = pcb;
        }
        else
        {
            rear->next = pcb;
            rear = pcb;
        }
    }

    // Function that pops a PCB from the front end of the queue
    ProcessControlBlock *pop()
    {
        if (front == nullptr)
        {
            return nullptr;
        }
        else
        {
            ProcessControlBlock *pcb = front;
            front = front->next;
            if (front == nullptr)
            {
                rear = nullptr;
            }
            return pcb;
        }
    }
};

struct Semaphore
{

    int semaphore = 1; // The actual value of the semaphore
    Semaphore()
    {
        semaphore = 1;
    }
    Semaphore(int s)
    {
        semaphore = s;
    }

    // A queue to store the waiting processes
    Queue *FIFO = new Queue();

    // A function to implement the 'wait' functionality of a semaphore
    void wait(int pID)
    {
        semaphore--;

        // If all resources are busy, push the process into the waiting queue and 'block' it
        if (semaphore < 0)
        {
            FIFO->push(pID);
            ProcessControlBlock *pcb = FIFO->rear;
            block(pcb);
        }
    }

    // A function to implement the 'signal' functionality of a semaphore
    void signal()
    {
        semaphore++;

        // If there are any processes waiting for execution, pop from the waiting queue and wake the process up
        if (semaphore <= 0)
        {
            ProcessControlBlock *pcb = FIFO->pop();
            wakeup(pcb);
        }
    }
};

Semaphore sem;

int decrease_count(int count)
{
    if (available_resources < count)
        return -1;
    else
    {
        sem->wait(processID);
        available_resources -= count;
        sem->signal(processID);
        return 0;
    }
}

/* increase available resources by count */
int increase_count(int count)
{
    sem->wait(processID);
    available_resources += count;
    sem->signal(processID);
    return 0;
}
