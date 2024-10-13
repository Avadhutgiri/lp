#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int burst;
    int arrival;
    int priority; // Lower Number -> Higher Priority
};

// FCFS Algorithm
void FCFS(Process processes[], int n, int wt[], int ct[], int tat[]) {
    int wait = 0;
    for (int i = 0; i < n; i++) {
        wt[i] = max(0, wait - processes[i].arrival); 
        ct[i] = wait + processes[i].burst;
        tat[i] = ct[i] - processes[i].arrival;
        wait += processes[i].burst;
    }
}

// SJF (Preemptive) Algorithm
void SRTF(Process processes[], int n, int wt[], int ct[], int tat[]) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) remainingTime[i] = processes[i].burst;

    int currentTime = 0, completedTasks = 0, shortestTask = 0, minBurst = INT_MAX;
    bool taskActive = false;

    while (completedTasks != n) {
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival <= currentTime && processes[j].burst < minBurst && remainingTime[j] > 0) {
                shortestTask = j;
                minBurst = processes[j].burst;
                taskActive = true;
            }
        }

        if (!taskActive) {
            currentTime++;
            continue;
        }

        remainingTime[shortestTask]--;
        minBurst = remainingTime[shortestTask];
        if (minBurst == 0) minBurst = INT_MAX;

        if (remainingTime[shortestTask] == 0) {
            completedTasks++;
            taskActive = false;
            ct[shortestTask] = currentTime + 1;
            wt[shortestTask] = ct[shortestTask] - processes[shortestTask].arrival - processes[shortestTask].burst;
            tat[shortestTask] = ct[shortestTask] - processes[shortestTask].arrival;
            if (wt[shortestTask] < 0) wt[shortestTask] = 0;
        }

        currentTime++;
    }
}

// Priority (Non-Preemptive) Algorithm
void npPriority(Process processes[], int n, int wt[], int ct[], int tat[]) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) remainingTime[i] = processes[i].burst;

    int currentTime = 0, completedTasks = 0, HPT = 0, maxPriority = INT_MAX;
    bool taskActive = false;

    while (completedTasks != n) {
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival <= currentTime && remainingTime[j] > 0 && processes[j].priority < maxPriority) {
                HPT = j;
                maxPriority = processes[j].priority;
                taskActive = true;
            }
        }

        if (!taskActive) {
            currentTime++;
            continue;
        }

        currentTime += processes[HPT].burst;
        remainingTime[HPT] = 0;
        maxPriority = INT_MAX;
        taskActive = false;
        completedTasks++;
        wt[HPT] = currentTime - processes[HPT].arrival - processes[HPT].burst;
        ct[HPT] = currentTime;
        tat[HPT] = ct[HPT] - processes[HPT].arrival;
    }
}

// Round Robin (Preemptive) Algorithm
void RoundRobin(Process processes[], int n, int ts, int wt[], int ct[], int tat[]) {
    queue<int> RQ; // Ready Queue to hold process indices
    int currentTime = 0, completedTasks = 0;
    int remainingTime[n]; // Array to store remaining burst time for each process

    for (int j = 0; j < n; j++) {
        if (processes[j].arrival <= currentTime) {
            RQ.push(j);
        }
    }

    for (int i = 0; i < n; i++) remainingTime[i] = processes[i].burst;

    while (completedTasks != n) {
        int curr = RQ.front(); // Get process index
        RQ.pop();

        int cntr = 0; // Time spent on current process

        while (cntr != ts && cntr != remainingTime[curr]) {
            currentTime++;
            cntr++;

            for (int j = 0; j < n; j++) {
                if (processes[j].arrival == currentTime)
                    RQ.push(j);
            }
        }

        remainingTime[curr] -= cntr;

        if (remainingTime[curr] == 0) {
            ct[curr] = currentTime;
            tat[curr] = ct[curr] - processes[curr].arrival;
            completedTasks++;
            wt[curr] = ct[curr] - processes[curr].arrival - processes[curr].burst;
        } else {
            RQ.push(curr);
        }
    }
}

void printTable(Process proc[], int n, int wt[], int ct[], int tat[]) {
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

    for (int i = 0; i < n; i++) {
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
}

int main() {
    int choice, ts;
    Process proc[5] = {{1, 10, 0}, {2, 5, 2}, {3, 8, 4}, {4, 4, 5}, {5, 3, 7}};
    int n = sizeof(proc) / sizeof(proc[0]);
    int wt[n], ct[n], tat[n];

    while (true) {
        cout << "CPU Scheduling Algorithms\n";
        cout << "1. FCFS\n";
        cout << "2. SJF (Preemptive)\n";
        cout << "3. Priority (Non-Preemptive)\n";
        cout << "4. Round Robin (Preemptive)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                FCFS(proc, n, wt, ct, tat);
                printTable(proc, n, wt, ct, tat);
                break;
            case 2:
                SRTF(proc, n, wt, ct, tat);
                printTable(proc, n, wt, ct, tat);
                break;
            case 3:
                cout << "Enter priority for each process (lower is higher priority):\n";
                for (int i = 0; i < n; i++) {
                    cout << "Process " << proc[i].id << ": ";
                    cin >> proc[i].priority;
                }
                npPriority(proc, n, wt, ct, tat);
                printTable(proc, n, wt, ct, tat);
                break;
            case 4:
                cout << "Enter time quantum: ";
                cin >> ts;
                RoundRobin(proc, n, ts, wt, ct, tat);
                printTable(proc, n, wt, ct, tat);
                break;
            case 5:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
