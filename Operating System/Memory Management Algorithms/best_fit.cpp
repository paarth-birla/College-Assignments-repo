#include<bits/stdc++.h> 
using namespace std; 

void bestFit(int blockSize[], int m, int processSize[], int n) 
{ 
	int allocation[n]; 
	memset(allocation, -1, sizeof(allocation)); 

	for (int i=0; i<n; i++) 
	{ 
		int bestIdx = -1; 
		for (int j=0; j<m; j++) 
		{ 
			if (blockSize[j] >= processSize[i]) 
			{ 
				if (bestIdx == -1) 
					bestIdx = j; 
				else if (blockSize[bestIdx] > blockSize[j]) 
					bestIdx = j; 
			} 
		} 

		if (bestIdx != -1) 
		{ 
			allocation[i] = bestIdx; 
			blockSize[bestIdx] -= processSize[i]; 
		} 
	} 

	cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 
	for (int i = 0; i < n; i++) 
	{ 
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
		if (allocation[i] != -1) 
			cout << allocation[i] + 1; 
		else
			cout << "Not Allocated"; 
		cout << endl; 
	} 
} 
int main() 
{ 
	int i;
    int no_of_blocks;
    cout << "Enter the no of Blocks : ";
    cin >> no_of_blocks;

    int no_of_process;
    cout << "\nEnter the no of Processes : ";
    cin >> no_of_process;

    int blocks[no_of_blocks];
    cout << "\nEnter the Block Sizes : ";
    cout << "\n";
    for(i=0;i<no_of_blocks;i++)
    {
        cin >> blocks[i];
    } 

    int process[no_of_process];
    cout << "\nEnter the Process Sizes : ";
    cout << "\n";
    for(i=0;i<no_of_process;i++)
    {
        cin >> process[i];
    }   

	bestFit(blocks, no_of_blocks, process, no_of_process); 

	return 0 ; 
} 
