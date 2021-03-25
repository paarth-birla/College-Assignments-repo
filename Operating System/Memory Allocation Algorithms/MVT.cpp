#include<bits/stdc++.h>
using namespace std;

int main()
{
    int ms,mp[10],i, temp,n=0;
    char ch = 'y';

    cout << "Enter the total memory available (in Bytes) -- ";
    cin >> ms;
    temp=ms;
    for(i=0;ch=='y';i++,n++)
    {
        cout << "Enter memory required for process " << i+1 << " (in Bytes)-- ";
        cin >> mp[i];
        if(mp[i]<=temp)
        {
            cout << "\nMemory is allocated for Process " << i+1;
            temp = temp - mp[i];
        }
        else
        {
            cout << "\n Memory is full";
            break;
        }
        cout << "\nDo you want to continue(y/n) -- ";
        cin >> ch;
    }
    cout << "\n\nTotal Memory Available -- " << ms;
    cout << "\n\n\tPROCESS\t\t MEMORY ALLOCATED ";
    for(i=0;i<n;i++)
        cout << "\n \t" << i+1 << "\t\t" << mp[i];
    cout << "\n\nTotal Memory Allocated is " << ms-temp;
    cout << "\nTotal External Fragmentation is " << temp;
} 