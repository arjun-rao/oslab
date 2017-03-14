#include <iostream>
#include <cstdlib>

using namespace std;

struct process{
	int no;
	int arrival;
	int burst;
	int waiting;
	int turnaround;
};

static int cmp_process(const void *p1, const void *p2)
{
   /* The actual arguments to this function are addresses of process elements */
   process *a = (process *) p1;
   process *b = (process *) p2;
   if(a->arrival < b->arrival) return -1;
   else if(a->arrival == b->arrival) return 0;
   else return 1;
   
}


void display(process *q,int n)
{	
	float avgwait=0,avgturn=0;
	cout<<"Process\tArrival\tBurst\tWaiting\tTurnaround\n";
	for(int i=0;i<n;i++)
	{
		cout<<"P"<<q[i].no<<"\t"<<q[i].arrival<<"\t"<<q[i].burst<<"\t"<<q[i].waiting<<"\t"<<q[i].turnaround<<endl;
		avgwait += q[i].waiting;	
		avgturn += q[i].turnaround;
	}
	cout<<"Average waiting time: "<<avgwait/(float)n<<endl;
	cout<<"Average turnaround time: "<<avgturn/(float)n<<endl;
	
}



int main()
{
	int n;
	cout<<"Enter number of processes: ";
	cin>>n;
	process q[n];
	cout<<"Enter arrival and burst times of each process:\n";
	for(int i=0;i<n;i++)
	{	
		q[i].no = i+1;
		cin>>q[i].arrival>>q[i].burst;
	}
	qsort(q,n,sizeof(process),cmp_process);
	int current = q[0].burst;
	q[0].waiting = 0;
	q[0].turnaround = q[0].waiting+q[0].burst;
	for(int i=1;i<n;i++)
	{
		current = (q[i].arrival>current?q[i].arrival:current);
		//waiting times
		q[i].waiting = current-q[i].arrival;
		current += q[i].burst;
		q[i].turnaround = q[i].waiting+q[i].burst;
		
	}
	cout<<"FCFS order:\n";
	display(q,n);
	return 0;

}
