#include<bits/stdc++.h>
using namespace std;

int main()
{
    int ms, bs, nob, ef,n, mp[10],tif=0;
    int i,p=0;

    cout << "Enter the total memory available (in Bytes) -- ";
    cin >> ms;

    cout << "Enter the block size (in Bytes) -- ";
    cin >> bs;

    nob=ms/bs;
    ef=ms - nob*bs;

    cout << "\nEnter the number of processes -- ";
    cin >> n;
    for(i=0;i<n;i++)
    {
        cout << "Enter memory required for process " << i+1 << " (in Bytes)-- ";
        cin >> mp[i];
    }
    cout << "\nNo. of Blocks available in memory -- " << nob;
    cout << "\n\nPROCESS\tMEMORY REQUIRED\t ALLOCATED\tINTERNAL FRAGMENTATION";
    for(i=0;i<n && p<nob;i++)
    {
        cout << "\n " << i+1 << "\t\t" << mp[i];
        if(mp[i] > bs)
            cout << "\t\tNO\t\t ---";
        else
        {
            cout << "\t\tYES\t\t" << bs-mp[i];
            tif = tif + bs-mp[i];
            p++;
        }
    }
    if(i<n)
        cout << "\nMemory is Full, Remaining Processes cannot be accomodated";
    
    cout << "\n\nTotal Internal Fragmentation is " << tif;
    cout << "\nTotal External Fragmentation is " << ef;
}