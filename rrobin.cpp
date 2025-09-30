#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrival(const Process &a, const Process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

int main()
{
    int n;
    int timeQuantum;

    cout << "Masukkan jumlah proses: ";
    cin >> n;

    cout << endl
         << "Masukkan Time Quantum: ";
    cin >> timeQuantum;

    vector<Process> processes(n);
    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;

    for (int i = 0; i < n; ++i)
    {
        processes[i].pid = i + 1;
        cout << endl
             << "Proses " << processes[i].pid << endl;
        cout << "  Masukkan Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "  Masukkan Burst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrival);

    queue<int> readyQueue;
    int currentTime = 0;
    int completedProcesses = 0;
    int currentProcessIndex = 0;

    if (!processes.empty() && processes[0].arrivalTime == 0)
    {
        readyQueue.push(0);
        currentProcessIndex = 1;
    }

    while (completedProcesses < n)
    {
        if (readyQueue.empty())
        {
            currentTime = processes[currentProcessIndex].arrivalTime;
            while (currentProcessIndex < n && processes[currentProcessIndex].arrivalTime <= currentTime)
            {
                readyQueue.push(currentProcessIndex++);
            }
            continue;
        }

        int processId = readyQueue.front();
        readyQueue.pop();

        Process &p = processes[processId];

        int timeToRun = min(p.remainingTime, timeQuantum);

        int timeBeforeRun = currentTime;
        currentTime += timeToRun;
        p.remainingTime -= timeToRun;

        while (currentProcessIndex < n && processes[currentProcessIndex].arrivalTime <= currentTime)
        {
            readyQueue.push(currentProcessIndex++);
        }

        if (p.remainingTime == 0)
        {
            p.completionTime = currentTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            totalTurnaroundTime += p.turnaroundTime;
            totalWaitingTime += p.waitingTime;
            completedProcesses++;
        }
        else
        {
            readyQueue.push(processId);
        }
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.pid < b.pid; });

    cout << endl
         << "--- Hasil Penjadwalan Round Robin ---" << endl;
    cout << "======================================================================================================" << endl;
    cout << left << setw(10) << "Proses"
         << setw(15) << "Arrival Time"
         << setw(15) << "Burst Time"
         << setw(20) << "Completion Time"
         << setw(20) << "Turnaround Time"
         << setw(15) << "Waiting Time" << endl;
    cout << "======================================================================================================" << endl;

    for (const auto &p : processes)
    {
        cout << left << setw(10) << "P" + to_string(p.pid)
             << setw(15) << p.arrivalTime
             << setw(15) << p.burstTime
             << setw(20) << p.completionTime
             << setw(20) << p.turnaroundTime
             << setw(15) << p.waitingTime << endl;
    }
    cout << "======================================================================================================";

    float avgTurnaroundTime = totalTurnaroundTime / n;
    float avgWaitingTime = totalWaitingTime / n;

    cout << fixed << setprecision(2);
    cout << endl
         << "Rata-rata Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Rata-rata Waiting Time:    " << avgWaitingTime << endl;

    return 0;
}
