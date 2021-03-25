// Datastructures used :
//  1) no_of_processes --> number of processes
//  2) no_of_resource --> number of types of resource used
//  3) available_resources --> array of length 'no_of_resource', available_resources[j] = k means that 'k' instances of resource type resource[j] 
//  4) max_resources --> matrix of dimensions [no_of_processes x no_of_resource], indicates that each process process[i] can store maximum number of resources of type resource[j]
//  5) allocate_resource --> matrix of dimensions [no_of_processes x no_of_resource], indicates type of resource allocated to each process, allocate_resource[i][j] = k, means process[i] is allocated with 'k' instances of resource[j]
//  6) need_resource --> matrix of dimensions [no_of_processes x no_of_resource], represents number of remaining resources for each process, need_resource[i][j] = k, means process[i] requires 'k' instances of resource[j]
//  7) safe_state --> array of length 'no_of_resource', stores boolean values indicating whether process has been allocated required resources or not
//  8) safe_sequence --> array of length 'no_of_resource', stores final sequence of safe state
// Banker's Algorithm is combination of Safety Algorithm and Resource Request Algorithm to control processes and avoid deadlock in system

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int no_of_processes, no_of_resource, i, j, k;

    cout << "Enter number of processes : ";
    cin >> no_of_processes;
    cout << "Enter number of resources : ";
    cin >> no_of_resource;

    int allocate_resource[no_of_processes][no_of_resource], max_resources[no_of_processes][no_of_resource];
    int available_resources[no_of_resource];

    for(i=0;i<no_of_processes;i++)
    {
        for(j=0;j<no_of_resource;j++)
        {
            cout << "Enter the instances of allocated resource of type " << char(65+j) << " for the Process " << i << " : ";
            cin >> allocate_resource[i][j];
        }
    }

    cout << "\n";
    for(i=0;i<no_of_processes;i++)
    {
        for(j=0;j<no_of_resource;j++)
        {
            cout << "Enter the instances of max resource of type " << char(65+j) << " for the Process " << i << " : ";
            cin >> max_resources[i][j];
        }
    }

    cout << "\n";
    for(j=0;j<no_of_resource;j++)
    {
        cout << "Enter the instances of available resource of type " << char(65+j) << " : ";
        cin >> available_resources[j];
    }

    cout << "\n";
    int safe_state[no_of_processes], safe_sequence[no_of_processes];
    int index = 0;

    for(k = 0; k < no_of_processes; k++)
    {
        safe_state[k] = 0;
    }

    int need_resource[no_of_processes][no_of_resource];
    for(i=0; i < no_of_processes; i++)
    {
        for(j=0; j< no_of_resource; j++)
        {
            need_resource[i][j] = max_resources[i][j] - allocate_resource[i][j];
        }
    }

    int y = 0;
    for(k=0; k<no_of_processes; k++)
    {
        for (i=0; i<no_of_processes; i++)
        {
            if(safe_state[i] == 0)
            {
                int flag = 0;
                for(j=0; j<no_of_resource; j++)
                {
                    if(need_resource[i][j] > available_resources[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0)
                {
                    safe_sequence[index++] = i;
                    for(y=0; y<no_of_resource; y++)
                    {
                        available_resources[y] += allocate_resource[i][y];
                    }
                    safe_state[i] = 1;
                }
            }
        }
        
    }

    cout << "============================================================\n\n";
    cout << "The SAFE SEQUENCE is : " << endl;
    for(i=0; i<no_of_processes-1; i++)
    {
        cout << "Process " << safe_sequence[i] << "-->";
    }
    cout << "Process " << safe_sequence[no_of_processes-1] << "\n";
    cout << "============================================================\n\n"; 

    return 0;
}

/*
Banker's Algorithm :
    used to avoid deadlocks and allocate resources safely to processes in system.

*/
/*
Safety Algorithm :
    used to check whether or not a system is in safe state or follows the safe sequence
    Algorithm :
        1)Let work and safe_state be two arrays of length 'no_of_resource' and 'no_of_processes'
            Initialize : work = available_resource
            safe_state[i] = 0, for all i
        2)Find an i such that
            safe_state[i] = 0
            need_resource[i][j] > work[j]
            goto step 4
        3)work[j] = work[j] + allocation[i][j]
          safe_state[i] = 1
          goto step 2
        4)if safe_state[i] = 1 for all i, SYstem is in SAFE STATE
*/

/*
Resource Request Algorithm :
    checks how a system will behave when a process makes each type of resource request in system
    Algorithm :
        let requesti be request array for processi
        requesti[j] = k, means processi wants 'k' instances of resource type resourcej
        1)if requesti <= need_resourcesi
            goto step 2
            otherwise raise error
        2)if requesti <= available_resourcesi
            goto step 3
            otherwise processi must wait
        3)have the system pretend to have allocated the requested resources to processi by modifying state
            available_resourcesi -= requesti
            allocate_resourcei += requesti
            need_resourcei -= requesti
*/