#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;



struct process{
	int no;
	int scheduled;
	int arrival;
	int burst;
	int priority;
	int waiting;
	int turnaround;
};

void display(process *q,int n,int simple=0);

static int cmp_process_arrival(const void *p1, const void *p2)
{
   /* The actual arguments to this function are addresses of process elements */
   process *a = (process *) p1;
   process *b = (process *) p2;
   if(a->arrival < b->arrival) return -1;
   else if(a->arrival == b->arrival) return 0;
   else return 1;
   
}

void calc_times(process *q, int n)
{
	int current = 0;
	for (int i=0;i<n;i++)
	{
		current = (q[i].arrival>current?q[i].arrival:current);
		q[i].waiting = current - q[i].arrival;
		q[i].turnaround = q[i].waiting+q[i].burst;
		current+=q[i].burst;

	}
}

process getMinPriority(process *q,int n, int arrival,int priority)
{
	
	int min = -1;
	for(int i=0;i<n;i++)
	{
		if(q[i].scheduled)continue;
		if(q[i].arrival <= arrival && q[i].priority <= priority)
		{
			min = i;
			priority = q[i].priority;
		}		
	}
	if(min == -1)
	{
		for(int i=0;i<n;i++)
		{
			if(!q[i].scheduled){
				arrival = q[i].arrival;
				return getMinPriority(q,n,arrival,priority);	
			} 
		}
	}
	q[min].scheduled=1;
	return q[min];
}


process* schedule (process* q, int n)
{
	
	process *order = new process[n];
	int current = q[0].arrival;
	for(int i =0;i<n;i++)
	{
		order[i] = getMinPriority(q,n,current,INT_MAX);
		current += order[i].burst;
	}
	return order;
}



void display(process *q,int n,int simple)
{	
	float avgwait=0,avgturn=0;
	cout<<"Process\tArrival\tBurst\tPriority\t";
	if(!simple)
	cout<<"Start\tWaiting\tTurnaround";cout<<"\n";
	int current = 0;
	for(int i=0;i<n;i++)
	{
		current = (q[i].arrival>current?q[i].arrival:current);
		cout<<"P"<<q[i].no<<"\t"<<q[i].arrival<<"\t"<<q[i].burst<<"\t"<<q[i].priority;
		if(!simple){
		cout<<"\t"<<current<<"\t"<<q[i].waiting<<"\t"<<q[i].turnaround;
			avgwait += q[i].waiting;	
			avgturn += q[i].turnaround;
			current+=q[i].burst;
		}
		cout<<endl;
		
	}
	if(!simple){
		cout<<"Average waiting time: "<<avgwait/(float)n<<endl;
		cout<<"Average turnaround time: "<<avgturn/(float)n<<endl;
	}
	
}



int main()
{
	int n;
	cout<<"Enter number of processes: ";
	cin>>n;
	process q[n];
	cout<<"Enter arrival,burst times and priority of each process:\n";
	for(int i=0;i<n;i++)
	{	
		q[i].no = i;
		q[i].scheduled = 0;
		cin>>q[i].arrival>>q[i].burst>>q[i].priority;
	}
	//sort based on arrival
	qsort(q,n,sizeof(process),cmp_process_arrival);
	process *order= schedule(q,n);
	calc_times(order,n);
	cout<<"Processes:\n";
	display(q,n,1);
	cout<<"Priority Scheduling order:\n";
	display(order,n);
	delete [] order;
	//display(q,n);
	return 0;

}
