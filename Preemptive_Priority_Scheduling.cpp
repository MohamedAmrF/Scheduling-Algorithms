#include<iostream>
#include <queue>
#define TIMELINE_MAX 1000
using namespace std;

struct process
{
    int pid;
    int priority;
    int burstTime;
    int arrivalTime;

    // stats
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
    int BURSTTIMECONST;
    bool firsTime = true;

    bool operator > (const process& rhs) const {
        if (priority == rhs.priority)
        {
            if (burstTime == rhs.burstTime)
            {
                return arrivalTime < rhs.arrivalTime;
            }
            return burstTime < rhs.burstTime;
        }
        return priority < rhs.priority;
    }

    bool operator < (const process& rhs) const {
        if (priority == rhs.priority)
        {
            if (burstTime == rhs.burstTime)
            {
                return arrivalTime > rhs.arrivalTime;
            }
            return burstTime > rhs.burstTime;
        }
        return priority > rhs.priority;
    }

};

void drawGanttChart(vector<int>& Chart)
{
    cout << "Gant Chart : \n";
    cout << "| ";
    cout << "P" << Chart[0] + 1;
    for (int i = 1; i < Chart.size(); i++)
    {
        if(Chart[i]==-1)
        {
            cout << " | W";
            continue;
        }
        if (Chart[i] == Chart[i - 1])
        {
            cout << "+";
        }
        else
        {
            cout << " | P" << Chart[i] + 1 << "";
        }
    }
    cout << " |";
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter The number of processes: ";
    cin >> n;
    vector<process>processes(n);
    vector<vector<process>>timestamped_processes(TIMELINE_MAX);
    int completed = 0, totalTime = 0;

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i;

        cout << "Process " << i + 1 << " : \n";
        cout << "Enter Priority, Burst Time, and Arrival Time respectively: ";
        cin >> processes[i].priority >> processes[i].burstTime >> processes[i].arrivalTime;
        processes[i].BURSTTIMECONST = processes[i].burstTime;
        timestamped_processes[processes[i].arrivalTime].push_back(processes[i]);
        totalTime += processes[i].burstTime;
    }

    vector<int>GanttChart;
    priority_queue<process, vector<process>, greater<process>>ready_queue;
    int waitcounter = 0;
    for (int i = 0; i < totalTime+waitcounter; i++)
    {
        if (i < TIMELINE_MAX) { // if currenttime(i) < number of process, then push the process in the ready queue.
            for (auto& temp : timestamped_processes[i])
            {
                //timestamped_processes[i].pop_back();
                if (!timestamped_processes[i].empty()) {
                    ready_queue.push(temp);
                    //cout << temp.pid << " is pushed \n";
                }
            }
        }
        if(ready_queue.empty())
        {
            GanttChart.push_back(-1);
            waitcounter++;
        }
        process& temp = processes[ready_queue.top().pid];

        if (temp.firsTime)
        {
            temp.startTime = i;
            temp.firsTime = false;
        }
        if (temp.burstTime > 0) {
            temp.burstTime--;
            GanttChart.push_back(temp.pid);
        }
        if (temp.burstTime == 0)
        {
            temp.completionTime = i + 1;
            temp.turnaroundTime = temp.completionTime - temp.arrivalTime;
            temp.waitingTime = temp.turnaroundTime - temp.BURSTTIMECONST;
            temp.responseTime = temp.startTime - temp.arrivalTime;
            processes[temp.pid] = temp;                                 // assign the temp process to the original vector of processes.
            //cout << temp.pid << " is popped \n";
            if (!ready_queue.empty())
                ready_queue.pop();
        }
    }

    int Avg_turnaroundTime = 0, Avg_waitingTime = 0, Avg_responseTime = 0;
    cout << "\n \n";
    for (int i = 0; i < n; i++)
    {
        cout << "-----------------------------------------------\n";
        cout << "PROCESS " << i + 1 << " : \n";
        cout << "Turn around time = " << processes[i].turnaroundTime << endl;
        cout << "Waiting time = " << processes[i].waitingTime << endl;
        cout << "Response time = " << processes[i].responseTime << endl;
        cout << "------------------------------------------------\n\n";
        Avg_turnaroundTime += processes[i].turnaroundTime;
        Avg_waitingTime += processes[i].waitingTime;
        Avg_responseTime += processes[i].responseTime;
    }

    cout << "\n\n*************************************************** \n";
    cout << "Average Turnaround time =  " << (double)Avg_turnaroundTime / n << "\n";
    cout << "Average Waiting time =  " << (double)Avg_waitingTime / n << "\n";
    cout << "Average Respoinse time =  " << (double)Avg_responseTime / n << "\n";
    cout << "***************************************************\n\n";

    drawGanttChart(GanttChart);

    cout << "\n\n";
    return 0;
}