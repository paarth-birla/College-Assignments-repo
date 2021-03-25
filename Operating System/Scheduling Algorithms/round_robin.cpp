#include<bits/stdc++.h>
using namespace std;

void find_waiting_time(int process[], 
					int wt_time[], int n, 
					int burst_time[], 
					int quantum, 
					int completion_time[], 
					int arrival_time[])
{
    int rem_time[n];

    for(int i = 0; i < n; i++)
        rem_time[i] = burst_time[i];

    int t = 0;
    int arrival = 0;
    while(true)
    {
        bool done = true;
        for(int i = 0; i < n; i++)
        {
        if(rem_time[i] > 0)
        {
            done = false;
            if(rem_time[i] > quantum && 
            arrival_time[i] <= arrival)
            {
            t += quantum;
            rem_time[i] -= quantum;
            arrival++;
            }
            else
            {
            if(arrival_time[i] <= arrival)
            {
                arrival++;
                t += rem_time[i];
                rem_time[i] = 0;
                completion_time[i] = t; 
            }
            }
        }
        }

        if(done==true) 
        break;
    } 
}

void find_turnaround_time(int process[], 
						int wt_time[], int n, 
						int burst_time[], 
						int tat_time[], 
						int completion_time[], 
						int arrival_time[])
{
    for(int i = 0; i < n; i++)
    {
        tat_time[i] = completion_time[i] - 
                    arrival_time[i];
        wt_time[i] = tat_time[i] - 
                    burst_time[i];
    }
}

void find_avg_waiting_time(int process[], int n, 
				int burst_time[], 
				int quantum, 
				int arrival_time[])
{
    int wt_time[n];
    int tat_time[n];
    int completion_time[n];
    int total_wt = 0, total_tat = 0;
    find_waiting_time(process, wt_time, 
                    n, burst_time, 
                    quantum, 
                    completion_time, 
                    arrival_time); 
    find_turnaround_time(process, wt_time, 
                        n, burst_time, 
                        tat_time, 
                        completion_time, 
                        arrival_time);
    cout << setw(9) << "PROCESS" << 
            setw(14) << "ARRIVAL TIME" << 
            setw(12) << "BURST TIME" << 
            setw(17) << "COMPLETION TIME" <<
            setw(18) << "TURN AROUND TIME" <<
            setw(16) << "WAITING TIME\n";

    for (int i = 0; i < n; i++) 
    { 
        total_wt = total_wt + wt_time[i]; 
        total_tat = total_tat + tat_time[i]; 
        cout << setw(6) << i + 1 << 
                setw(11) << arrival_time[i] << 
                setw(12) << burst_time[i] << 
                setw(17) << completion_time[i] <<
                setw(15) << tat_time[i] <<
                setw(16) << wt_time[i] << endl; 
    } 

    cout << "\nAVERAGE WAITING TIME : " <<
            (float)total_wt / (float)n;
}

// Driver code
int main()
{
    int quantum[2];
    for(int i=0;i<2;i++)
    {
        cout << "Enter quantum time for case " << i+1 << " : ";
        cin >> quantum[i];
    }
    cout << "\n\n";

    int n;
    cout << "Enter the number of process : ";
    cin >> n;
    cout << "\n";

    int arrival_time[n];
    int process[n];
    int burst_time[n];

    for(int i=0;i<n;i++)
    {
        process[i] = i+1;
        cout << "Enter arrival time for process " << i+1 << " : ";
        cin >> arrival_time[i];
        cout << "Enter burst time for process " << i+1 << " : ";
        cin >> burst_time[i];
        cout << "\n";
    }

    cout << "\n\n";
    cout << "====================================================\n";
    cout << "RESULTS OF CASE 1\n";
    cout << "quantum time for case 1 : " << quantum[0];
    cout << "\n";
    find_avg_waiting_time(process, n, burst_time, quantum[0], arrival_time);

    cout << "\n\n";
    cout << "====================================================\n";
    cout << "RESULTS OF CASE 2\n";
    cout << "quantum time for case 2 : " << quantum[1];
    cout << "\n";
    find_avg_waiting_time(process, n, burst_time, quantum[1], arrival_time);
    return 0;
}
