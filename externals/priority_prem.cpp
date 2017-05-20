//Preemptive Priority

#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

struct process{
	int no,remaining,priority,arrival,end,burst,waiting,turnaround;
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

void display(process *q,int n)
{	
	int avgw=0,avgt=0;
	cout<<"\nProcess\tArrival\tBurst\t";
	cout<<"PRTY\tFinish\tWaiting\tTurnaround";cout<<"\n";	
	for(int i=0;i<n;i++)
	{
        q[i].waiting = q[i].end - q[i].arrival - q[i].burst;
        q[i].turnaround = q[i].end - q[i].arrival;
        avgt+=q[i].turnaround;
        avgw+=q[i].waiting;
		cout<<"P"<<q[i].no+1<<"\t"<<q[i].arrival<<"\t"<<q[i].burst<<"\t"<<q[i].priority;		
		cout<<"\t"<<q[i].end<<"\t"<<q[i].waiting<<"\t"<<q[i].turnaround;			
		cout<<endl;
		
	}
    cout<<"Average waiting time: "<<avgw/(float)n<<endl;
	cout<<"Average turnaround time: "<<avgt/(float)n<<endl;
	
}

process * getMinPriority(int &curr)
{    
    
    int minpriority = INT_MAX,index=-1;
    for(int i=0;i<n;i++)
    {
        if(q[i].priority < minpriority && q[i].arrival <= curr && q[i].remaining>0)                   
        {
            minpriority = q[i].priority;
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
	cout<<"Enter arrival,burst & priority times of each process:\n";
	for(int i=0;i<n;i++)
	{	
		q[i].no = i;		
		cin>>q[i].arrival>>q[i].burst>>q[i].priority;
        q[i].remaining = q[i].burst;
	}    
	//sort based on arrival
	qsort(q,n,sizeof(process),cmp_arrive);
	int curr = q[0].arrival;    
    process *p = NULL;
    while(isRemaining())
    {        
        p = getMinPriority(curr);           
        if(p!=NULL)   
        {    
            p->remaining--;    
            if(p->remaining == 0)
            {
                p->end = curr+1;
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
    display(q,n);
	cout<<endl;
    return 0;

}


