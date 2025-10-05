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
    int startTime;
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
    }

    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;

    for (int i = 0; i < n; ++i)
    {
        processes[i].startTime = max(currentTime, processes[i].arrivalTime);
        processes[i].completionTime = processes[i].startTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        currentTime = processes[i].completionTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    cout << endl
         << "--- Hasil Penjadwalan FCFS ---" << endl;
    cout << "======================================================================================================================" << endl;
    cout << left << setw(10) << "Proses"
         << setw(15) << "Arrival Time"
         << setw(15) << "Burst Time"
         << setw(15) << "Start Time"
         << setw(20) << "Completion Time"
         << setw(20) << "Turnaround Time"
         << setw(15) << "Waiting Time" << endl;
    cout << "======================================================================================================================" << endl;

    for (const auto &p : processes)
    {
        cout << left << setw(10) << "P" + to_string(p.pid)
             << setw(15) << p.arrivalTime
             << setw(15) << p.burstTime
             << setw(15) << p.startTime
             << setw(20) << p.completionTime
             << setw(20) << p.turnaroundTime
             << setw(15) << p.waitingTime << endl;
    }
    cout << "======================================================================================================================" << endl;

    float avgTurnaroundTime = totalTurnaroundTime / n;
    float avgWaitingTime = totalWaitingTime / n;

    cout << fixed << setprecision(2);
    cout << endl
         << "Rata-rata Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Rata-rata Waiting Time:    " << avgWaitingTime << endl;

    return 0;
}
