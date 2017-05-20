//Preemptive SJF

#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

struct process{
	int no,remaining,arrival,finish,burst,waiting,turnaround;
}*q;

struct order{
    int pno,time;    
};

int g_index = 0;
int n;

vector<order>gantt;

static int cmp_arrive(const void *p1, const void *p2)
{
   /* The actual arguments to this function are addresses of process elements */
   process *a = (process *) p1;
   process *b = (process *) p2;
   if(a->arrival < b->arrival) return -1;
   else if(a->arrival == b->arrival) return 0;
   else return 1;
   
}

void printGantt()
{
    cout<<"\nGantt Chart:\n";
    for(int i=0;i<g_index;i++)
    {
        cout<<"\tP"<<gantt[i].pno+1;     
    }   
    cout<<endl;
    for(int i=0;i<g_index;i++)
    {
        cout<<"\t@"<<gantt[i].time;     
    }  
    cout<<"\n";
}

void display()
{	
	int avgw=0,avgt=0;
	cout<<"\nProcess\tArrival\tBurst\t";
	cout<<"Finish\tWaiting\tTurnaround";cout<<"\n";	
	for(int i=0;i<n;i++)
	{
        q[i].waiting = q[i].finish - q[i].arrival - q[i].burst;
        q[i].turnaround = q[i].finish - q[i].arrival;
        avgt+=q[i].turnaround;
        avgw+=q[i].waiting;
		cout<<"P"<<q[i].no+1<<"\t"<<q[i].arrival<<"\t"<<q[i].burst;		
		cout<<"\t"<<q[i].finish<<"\t"<<q[i].waiting<<"\t"<<q[i].turnaround;			
		cout<<endl;
		
	}
    cout<<"Average waiting time: "<<avgw/(float)n<<endl;
	cout<<"Average turnaround time: "<<avgt/(float)n<<endl;
	
}

process * getShortestJob(int &curr)
{    
    int min_time = INT_MAX,index=-1;
    for(int i=0;i<n;i++)
    {
        if(q[i].remaining < min_time && q[i].arrival <= curr && q[i].remaining>0)                   
        {
            min_time = q[i].remaining;
            index = i;
        }        
    }
    if(index==-1)return NULL;
    return &q[index];
}

bool isRemaining()
{
        for(int i=0;i<n;i++)
        {
            if(q[i].remaining>0)
            {
                return true;                
            }            
        }
        return false;
}

int main()
{	
    cout<<"Enter number of processes: ";
	cin>>n;
	q = new process[n];
	cout<<"Enter arrival and burst times of each process:\n";
	for(int i=0;i<n;i++)
	{	
		q[i].no = i;		
		cin>>q[i].arrival>>q[i].burst;
        q[i].remaining = q[i].burst;
	}    
	//sort based on arrival
	qsort(q,n,sizeof(process),cmp_arrive);
	int curr = q[0].arrival;    
    process *p = NULL;
    while(isRemaining())
    {        
        p = getShortestJob(curr);           
        if(p!=NULL)   
        {    
            p->remaining--;    
            if(p->remaining == 0)
            {
                p->finish = curr+1;
            }
            if(g_index==0 || (gantt[g_index-1].pno!=p->no)) 
            {   
                order g;
                g.pno = p->no;
                g.time= curr;
                gantt.push_back(g);
                g_index++; 

            }                                    
                  
        }
        curr++;
        
    }    
    printGantt();
    display();
	cout<<endl;
    return 0;

}
