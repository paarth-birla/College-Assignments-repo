#include<bits/stdc++.h> 
using namespace std;

int pageFaults(int pages[], int n, int capacity) 
{ 
    unordered_set<int> s; 
  
    unordered_map<int, int> indexes; 
  
    int page_faults = 0; 
    for (int i=0; i<n; i++) 
    { 
        if (s.size() < capacity) 
        { 
            if (s.find(pages[i])==s.end()) 
            { 
                s.insert(pages[i]); 
                page_faults++; 
            } 
            indexes[pages[i]] = i; 
        } 
  
        else
        { 
            if (s.find(pages[i]) == s.end()) 
            { 
                int lru = INT_MAX, val; 
                for (auto it=s.begin(); it!=s.end(); it++) 
                { 
                    if (indexes[*it] < lru) 
                    { 
                        lru = indexes[*it]; 
                        val = *it; 
                    } 
                } 
                s.erase(val); 
                s.insert(pages[i]); 
                page_faults++; 
            } 
            indexes[pages[i]] = i; 
        } 
    } 
  
    return page_faults; 
} 
  
int main() 
{ 
    int i;
    int no_of_frames;
    cout << "Enter the capacity of Frame : ";
    cin >> no_of_frames;

    int no_of_pages;
    cout << "\nEnter the number of pages : ";
    cin >> no_of_pages;

    int pages[no_of_pages];
    cout << "\nEnter the Pages : ";
    cout << "\n";
    for(i=0;i<no_of_pages;i++)
    {
        cin >> pages[i];
    } 

    int page_faults, page_hit;
    float hit_ratio;

    page_faults = pageFaults(pages, no_of_pages, no_of_frames);
    page_hit = no_of_pages - page_faults;
    hit_ratio = ((float)page_hit/(float)no_of_pages);

    cout << "\nTotal Number of Page Faults : " << page_faults;
    cout << "\nTotal Number of Page Hits : " << page_hit;
    cout << "\nHit Ratio : " << hit_ratio;
    return 0; 
} 