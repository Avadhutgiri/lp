/*
Author: Shantanu Wable
*/

#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int burst;
    int arrival;
};

void RoundRobin(Process processes[], int n, int ts, int wt[], int ct[], int tat[])
{
    queue<int> RQ;                                 // Create a Ready Queue to hold process indices
    int currentTime = 0, completedTasks = 0;       // Initialize the current time and number of completed tasks
    int remainingTime[n];                          // Array to store remaining burst time for each process
    int curr;                                      // Variable to hold the current process index

    // Check for processes that have arrived at time 0 and push their indices to the Ready Queue
    for (int j = 0; j < n; j++)
    {
        if (processes[j].arrival <= currentTime)
        {
            RQ.push(j);
        }
    }

    // Initialize the remaining burst time for each process with its original burst time
    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burst;

    // Continue scheduling until all processes are completed
    while (completedTasks != n) {
        
        curr = RQ.front(); // Get the process index from the front of the Ready Queue
        RQ.pop(); // Remove the process from the front of the Ready Queue

        int cntr = 0; // Counter to keep track of time quantum spent on the current process

        // Execute the process for a time quantum (ts) or its remaining burst time (whichever is smaller)
        // Increment the counter for the time spent on the current process
        // Increment the current time
        
        while (cntr != ts && cntr != remainingTime[curr]) {
            
            currentTime++; 
            cntr++; 

            // Check if any new processes have arrived at the current time and add them to the Ready Queue
            for (int j = 0; j < n; j++) {
                if (processes[j].arrival == currentTime)
                    RQ.push(j);
            }
        }

        remainingTime[curr] -= cntr; // Reduce the remaining burst time of the current process by the time quantum spent on it

        // If the remaining burst time of the current process becomes zero, the process is completed
        // Set the completion time of the current process
        // Calculate the turnaround time for the current process
        // Increment the number of completed tasks
        
        if (remainingTime[curr] == 0) {
            ct[curr] = currentTime; 
            tat[curr] = ct[curr] - processes[curr].arrival; 
            completedTasks++; 
            wt[curr] = ct[curr] - processes[curr].arrival - processes[curr].burst;
        }
            
        else {
            // If the process is not completed, push it back to the Ready Queue to be scheduled later
            
            RQ.push(curr); 
        }
    }
}

int main() {
    
    Process proc[] = { {1, 8, 0}, {2, 2, 5}, {3, 7, 1 }, {4, 3, 6}, {5, 5, 8} };
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];
    for(int i=0;i<n;i++)
        wt[i] = 0;
    
    RoundRobin(proc, n, 3, wt, ct, tat);
    
    cout.width(5);
    cout << "ID";
    cout.width(5);
    cout << "AT";
    cout.width(5);
    cout << "BT";
    cout.width(5);
    cout << "CT";
    cout.width(5);
    cout << "TAT";
    cout.width(5);
    cout << "WT" << endl;
    
    for (int i = 0; i < n; i++)
    {
        cout.width(5);
        cout << proc[i].id;
        cout.width(5);
        cout << proc[i].arrival;
        cout.width(5);
        cout << proc[i].burst;
        cout.width(5);
        cout << ct[i];
        cout.width(5);
        cout << tat[i];
        cout.width(5);
        cout << wt[i] << endl;
    }

    return 0;
}
