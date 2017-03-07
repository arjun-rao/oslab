#include <iostream>
#include <cstdlib>

using namespace std;

struct process{
	int no;
	int arrival;
	int burst;
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
	for(int i=0;i<n;i++)
	{
		cout<<"P"<<q[i].no<<" Burst:"<<q[i].burst<<endl;
	}
}



int main()
{
	int n;
	cout<<"Enter number of processes:";
	cin>>n;
	process queue[n];
	cout<<"Enter arrival and burst times of each process:\n";
	for(int i=0;i<n;i++)
	{	
		queue[i].no = i+1;
		cin>>queue[i].arrival>>queue[i].burst;
	}
	qsort(queue,n,sizeof(process),cmp_process);
	cout<<"FCFS order:\n";
	display(queue,n);
	return 0;

}
