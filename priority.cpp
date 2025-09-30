#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    bool isCompleted;
};

int main()
{
    int n;
    cout << "Masukkan jumlah proses: ";
    cin >> n;

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
        cout << "  Masukkan Priority (angka kecil lebih tinggi): ";
        cin >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = false;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n)
    {
        int highestPriorityIndex = -1;
        int highestPriority = 1e9;

        for (int i = 0; i < n; ++i)
        {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted)
            {
                if (processes[i].priority < highestPriority)
                {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex == -1)
        {
            currentTime++;
        }
        else
        {
            processes[highestPriorityIndex].remainingTime--;
            currentTime++;

            if (processes[highestPriorityIndex].remainingTime == 0)
            {
                Process &p = processes[highestPriorityIndex];
                p.completionTime = currentTime;
                p.turnaroundTime = p.completionTime - p.arrivalTime;
                p.waitingTime = p.turnaroundTime - p.burstTime;
                totalTurnaroundTime += p.turnaroundTime;
                totalWaitingTime += p.waitingTime;

                p.isCompleted = true;
                completedProcesses++;
            }
        }
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.pid < b.pid; });

    cout << endl
         << "--- Hasil Penjadwalan Priority (Preemptive) ---" << endl;
    cout << "======================================================================================================================" << endl;
    cout << left << setw(10) << "Proses"
         << setw(15) << "Arrival Time"
         << setw(15) << "Burst Time"
         << setw(15) << "Priority"
         << setw(20) << "Completion Time"
         << setw(20) << "Turnaround Time"
         << setw(15) << "Waiting Time" << endl;
    cout << "======================================================================================================================" << endl;

    for (const auto &p : processes)
    {
        cout << left << setw(10) << "P" + to_string(p.pid)
             << setw(15) << p.arrivalTime
             << setw(15) << p.burstTime
             << setw(15) << p.priority
             << setw(20) << p.completionTime
             << setw(20) << p.turnaroundTime
             << setw(15) << p.waitingTime << endl;
    }
    cout << "======================================================================================================================" << endl;

    float avgTurnaroundTime = totalTurnaroundTime / n;
    float avgWaitingTime = totalWaitingTime / n;

    cout << fixed << setprecision(2);
    cout << "Rata-rata Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Rata-rata Waiting Time:    " << avgWaitingTime << endl;

    return 0;
}
