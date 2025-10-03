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
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int startTime;
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
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = false;
        processes[i].startTime = -1;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n)
    {
        int shortestJobIndex = -1;
        int shortestTime = 1e9;

        for (int i = 0; i < n; ++i)
        {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted)
            {
                if (processes[i].remainingTime < shortestTime)
                {
                    shortestTime = processes[i].remainingTime;
                    shortestJobIndex = i;
                }
            }
        }

        if (shortestJobIndex == -1)
        {
            currentTime++;
        }
        else
        {
            if (processes[shortestJobIndex].startTime == -1)
            {
                processes[shortestJobIndex].startTime = currentTime;
            }

            processes[shortestJobIndex].remainingTime--;
            currentTime++;

            if (processes[shortestJobIndex].remainingTime == 0)
            {
                processes[shortestJobIndex].completionTime = currentTime;
                processes[shortestJobIndex].turnaroundTime = processes[shortestJobIndex].completionTime - processes[shortestJobIndex].arrivalTime;
                processes[shortestJobIndex].waitingTime = processes[shortestJobIndex].turnaroundTime - processes[shortestJobIndex].burstTime;
                totalTurnaroundTime += processes[shortestJobIndex].turnaroundTime;
                totalWaitingTime += processes[shortestJobIndex].waitingTime;

                processes[shortestJobIndex].isCompleted = true;
                completedProcesses++;
            }
        }
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.pid < b.pid; });

    cout << endl
         << "--- Hasil Penjadwalan SJF Preemptive (SRTF) ---" << endl;
    cout << "=======================================================================================================================" << endl;
    cout << left
         << setw(10) << "Proses"
         << setw(15) << "Arrival Time"
         << setw(15) << "Burst Time"
         << setw(15) << "Start Time"
         << setw(20) << "Completion Time"
         << setw(20) << "Turnaround Time"
         << setw(15) << "Waiting Time" << endl;
    cout << "=======================================================================================================================" << endl;

    for (const auto &p : processes)
    {
        cout << left
             << setw(10) << "P" + to_string(p.pid)
             << setw(15) << p.arrivalTime
             << setw(15) << p.burstTime
             << setw(15) << p.startTime
             << setw(20) << p.completionTime
             << setw(20) << p.turnaroundTime
             << setw(15) << p.waitingTime << endl;
    }
    cout << "=======================================================================================================================" << endl;

    cout << fixed << setprecision(2);
    cout << endl << "Rata-rata Turnaround Time: " << totalTurnaroundTime / n << endl;
    cout << "Rata-rata Waiting Time:   " << totalWaitingTime / n << endl;


    return 0;
}
