#include<bits/stdc++.h>
using namespace std;

void waitingtime(int n, int *bt, int *wt)
{
    wt[0] = 0;
    for(int i=1;i<=n;i++)
    {
        wt[i] = bt[i-1] + wt[i-1];
    }
}

float avg_waittime(int n, int *bt)
{
    int wait_time[n], totalwaittime;
    totalwaittime = 0;
    waitingtime(n , bt, wait_time);
    for(int i=0;i<n;i++)
    {
        totalwaittime += wait_time[i];
    }
    return(float(totalwaittime/n));
}

void table(int n, int *bt)
{
    int wait_time[n];
    waitingtime(n, bt, wait_time);
    cout << "Processes  " << " Burst Time  " << " Waiting Time\n";
    for(int i=0;i<n;i++)
    {
        cout << "   " << i+1<<"\t\t"<<bt[i]<<"\t\t"<<wait_time[i]<<"\n";
    }
}

int main()
{
    int n;
    cout << "Enter number of processes : ";
    cin >> n;
    cout << "\n";
    int burst_time[n];
    
    for(int i=0;i<n;i++)
    {
        cout << "Enter burst time of process "<<i+1<<" :\n";
        cin >> burst_time[i];
    }
    table(n, burst_time);
    float output = avg_waittime(n, burst_time);
    cout << "\nAverage Waiting Time is " << output << " sec";
    return 0;
}