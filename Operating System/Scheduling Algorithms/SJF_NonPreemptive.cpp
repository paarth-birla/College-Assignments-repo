#include<bits/stdc++.h>
using namespace std;

int main()
{
      int n, temp, tt=0, min, d, i, j;
      float avg_turnaround_time = 0, avg_wait_time=0, sum_turnaround_time=0, sum_wait_time=0;

      cout << "Enter number of process : ";
      cin >> n;
      int arrival_time[n], burst_time[n], e[n], tat[n], wait_time[n], process[n];
  
      for(i=0;i<n;i++)
      {
            process[i] = i+1;
            cout << "Enter arrival time of process " << i+1 << " : ";       
            cin >> arrival_time[i];
            cout << "Enter burst time of process " << i+1 <<" : ";     
            cin >> burst_time[i];
      }

      for(i=0;i<n;i++)
      {
         for(j=i+1;j<n;j++)
          {
                if(burst_time[i] > burst_time[j])
                {
                      temp = process[i];
                      process[i] = process[j];
                      process[j] = temp;

                      temp = arrival_time[i];
                      arrival_time[i] = arrival_time[j];
                      arrival_time[j] = temp;

                      temp = burst_time[i];
                      burst_time[i] = burst_time[j];
                      burst_time[j] = temp;
                }
          }
      }
      min = arrival_time[0];
      for(i=0;i<n;i++)
      {
            if(min > arrival_time[i])
            {
                  min = arrival_time[i];
                  d = i;
            }
      }
      tt = min;
      e[d] = tt + burst_time[d];
      tt = e[d];

      for(i=0;i<n;i++)
      {
            if(arrival_time[i] != min)
            {
                  e[i] = burst_time[i] + tt;
                  tt = e[i];
            }
      }
      for(i=0;i<n;i++)
      {

            tat[i] = e[i] - arrival_time[i];
            wait_time[i] = tat[i] - burst_time[i];
            sum_wait_time = sum_wait_time + wait_time[i];
      }
      avg_wait_time = sum_wait_time / n;
      cout << "Average Waiting time = " << avg_wait_time << endl;
    return 0;
}