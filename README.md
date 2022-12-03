# Preemptive Priority Scheduling

- Simulates ***Preemptive Priority Scheduling*** Algorithm.
- Outputs ***Accounting*** information for each process.
- Draws ***Gantt Chart***.

## Input:
- On the first line enter the number of processes. ( n )
- On the next ***n*** lines enter the Priority, Burst Time, and Arrival Time respectively.

__Example__:
```
5
4 4 0
3 3 1
1 4 3
5 2 6
2 4 8
```
## Documentation:

- <code>drawGanttChart</code> function: Draws ***Gantt Chart*** from a vector of process ids (PIDs),Nth element corresponds to the process id that is drawn in Nth millisecond in the Gantt Chart.
- <code> vector<process>processes(n) </code>: Stores the processes in the order of their input by the user.
- <code> vector<vector<process>>timestamped_processes(TIMELINE_MAX) </code>: Each row is for a certain timestamp, and each column is for the processes that are ready at this time.
- <code>priority_queue<process, vector<process>, greater<process>>ready_queue</code>: The ready queue is implemented as a ***min heap***.