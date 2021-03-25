#include <bits/stdc++.h>
using namespace std;

int main() 
{
      int arrival_time[100], burst_time[100], e[100], i, s, count = 0, t, n, wt = 0, end;
     cout << "Enter the number of process : ";
     cin >> n;
 
      for(i=0;i<n;i++)
      {
           cout << "Enter the arrival time of process " << i+1 << " : ";
           cin >> arrival_time[i];
           cout << "Enter the burst time of process " << i+1 << " : ";
           cin >> burst_time[i];
           e[i] = burst_time[i];
      }     
      burst_time[99] = 99999;  
      for(t = 0; count != n; t++)
      {
            s = 99;
            for(i = 0; i < n; i++)
            {
                  if(arrival_time[i] <= t && burst_time[i] < burst_time[s] && burst_time[i] > 0)
                  {
                        s = i;
                  }
            }
            burst_time[s]--;
            if(burst_time[s] == 0)
            {
                  count++;
                  end = t + 1;
                  wt = wt + end - arrival_time[s] - e[s];
            }
      }
      float avg_wt = wt / n; 
      
      cout << "Average waiting time is : " << avg_wt <<endl;
    
      return 0;
}