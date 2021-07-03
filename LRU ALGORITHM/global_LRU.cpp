// 18UCS124
// Mohit Agarwal
// global page replacement algorithm

#include <bits/stdc++.h>
using namespace std;

int memory_size,no_of_process,total_hit; 
vector<int> hit,reference_count,nvp;  
vector< vector<int> > pagetable;
vector< pair<int,int> > page_reference,memory;

void initialization();
void print(int process);
void global_page_replacement();

   
int main()
{
    int n;
    pair<int,int> page;
    
    cout<<"Enter Memory Size and no. of processes: ";
    cin >> memory_size;
    cin >> no_of_process; 

    cout<<"Enter no. of pages for "<<endl;    
    for(int i=0; i < no_of_process; i++){
        cout<<"process "<<i<<" : ";
        cin >> n; 
        nvp.push_back(n);
        reference_count.push_back(0);
    }
    
    cout<<"enter process no. and page no. (for termination enter -1 -1):"<<endl;

    cin >> page.first;
    cin >> page.second;    
    while((page.first != -1) && (page.second != -1))
	{
        page_reference.push_back(page);
        reference_count[page.first]++;
        cin >> page.first;
        cin >> page.second;        
    }
    
    cout << "global page replacement policy : " << endl; 
    global_page_replacement();    
    cout << endl;
    
    return 0;
}


void initialization()
{
    hit.clear(); 
    hit.assign(no_of_process,0);
 
    total_hit = 0;
    memory.clear();

    pagetable.clear();
    vector<int> p;    
    for(int i=0;i<no_of_process;i++)
	{
        p.assign(nvp[i],-1);
        pagetable.push_back(p);
        p.clear();
    }    
}

void print(int process)
{
    int num = nvp[process],i;
    cout<< "   ";
    cout << "\n";
    cout<< "   ";
    for(i=0; i < num; i++)
	{
        cout << "=>  " << pagetable[process][i] << "  ";
    }
    cout << "=>" << endl;
    cout<<"\t";
    cout <<endl;
    cout<<"\t";
    for(i=0; i < num; i++)
        cout << "   " << i << "   ";     
    cout << endl;    
}

void global_page_replacement()
{
    initialization();  
    vector<int> lru(memory_size,0); 
    int current_procedure,curr_vp,rep_proc,rep_vp,lru_page;
    pair<int,int> curr;
    for(int i=0;i<page_reference.size();i++)
	{
        current_procedure = page_reference[i].first;
        curr_vp = page_reference[i].second;
        if(pagetable[current_procedure][curr_vp] != -1)
		{  
            hit[current_procedure]++;   
            total_hit++;  
            lru[pagetable[current_procedure][curr_vp]] = i;  
        }
        else
		{ 
            cout << "\n" << endl;            
            cout << "page fault for process = " << current_procedure ; 
			cout << " virtual page = " << curr_vp ;
			cout << "\n show page table: \n" << endl;
            cout<<"\t";
            cout << "before fault:" << endl;
            print(current_procedure);
            cout << endl;
            if(memory.size() < memory_size)
			{ 
                pagetable[current_procedure][curr_vp] = memory.size();
                lru[memory.size()] = i;
                curr.first=current_procedure;
                curr.second=curr_vp;
                memory.push_back(curr);
            }
            else
			{
                lru_page = min_element(lru.begin(),lru.end()) - lru.begin();
                rep_proc = memory[lru_page].first;
                rep_vp = memory[lru_page].second;
                pagetable[current_procedure][curr_vp] = lru_page;
                pagetable[rep_proc][rep_vp] = -1;  
                memory[lru_page].first = current_procedure;
                memory[lru_page].second = curr_vp;
                lru[lru_page] = i;
            }
            cout<<"\t";
            cout << "after fault:" << endl;
            print(current_procedure);  
                for(int k=2; k < 70; k++)
                    cout << "|";
                cout << endl;
            
            cout << endl;  
        }
    }
    for(int j=0; j < no_of_process; j++)
        cout << "hit ratio of process " << j << " = " << ((float)hit[j])/reference_count[j] << endl;     
    cout << endl;
    cout << "total hit ratio = " << (float)total_hit/page_reference.size() << endl;
    cout << "\n" << endl;                               
}

 
