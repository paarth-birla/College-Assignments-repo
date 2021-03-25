#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int process_no;
    int arrival_time;
    int burst_time;
    int priority;
};

Process process[50];

bool compare(Process a, Process b)
{
    if(a.arrival_time == b.arrival_time)
    {
        return a.priority < b.priority;
    }
    else
    {
        return a.arrival_time < b.arrival_time;
    }
}

void find_waiting_time(int wait_time[], int totalprocess)
{
    int temp[50];
    temp[0] = process[0].arrival_time;
    wait_time[0] = 0;

    for(int i=1;i<totalprocess;i++)
    {
        temp[i] = process[i-1].burst_time + temp[i-1];
        wait_time[i] = temp[i] - process[i].arrival_time;

        if (wait_time[i] < 0)
        {
            wait_time[i] = 0;
        }
    }
}


void find_avg_wait_time(int totalprocess)
{
    int wait_time[50];
    double avg_wait_time = 0;

    find_waiting_time(wait_time, totalprocess);

    for(int i=0;i<totalprocess;i++)
    {
        avg_wait_time += wait_time[i];
    }
    cout<<"Process"<<"\t\t\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"Priority"<<endl;

    for(int i=0;i<totalprocess;i++)
    {
        cout << "p" << i+1 << "\t" << process[i].process_no << "\t\t" << process[i].burst_time << "\t\t" << process[i].arrival_time << "\t\t" << wait_time[i] << "\t\t" << process[i].priority << endl;    
    }
    cout << "Average Waiting Time : " << avg_wait_time/float(totalprocess) << "\n";
}

int main()
{
    int no_of_process;
    cout << "Enter Number of Processes : ";
    cin >> no_of_process;

    for(int i=0;i<no_of_process;i++)
    {
        process[i].process_no = i+1;
        cout << "Enter arrival time for Process " << i+1 << " :";
        cin >> process[i].arrival_time;
        cout << "Enter burst time for Process " << i+1 << " :";
        cin >> process[i].burst_time;
        cout << "Enter priority for Process " << i+1 << " :";
        cin >> process[i].priority;
    }

    sort(process,process+no_of_process,compare);

    find_avg_wait_time(no_of_process);
    return 0;
}