#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define INT_MAX 32767

struct process{
	int no;
	int completed;
	int round;
	int arrival;
	int burst;
	int finish;
	int waiting;
	int turnaround;
};

void display(process *q,int n,int simple=0);

int rounds;

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
	
	for(int i=0;i<n;i++)
	{
		//waiting times
		q[i].waiting = q[i].finish - (q[i].arrival+q[i].burst);
		q[i].turnaround = q[i].waiting+q[i].burst;
		
	}
}

process getNext(process *q,int n, int& curr_time,int quantum,int& round)
{
	
	
	//cout<<"\nInGetNext:"<<curr_time<<"\t"<<round<<"\nSkipped";
	int selected = 0,flag = 0;
	for(int i=0;i<n;i++)
	{
		if(q[i].completed>=q[i].burst || q[i].round >= round){ 
			continue;
			//cout<<q[i].no<<"\t";
		}
		if(q[i].arrival <= curr_time && q[i].round < round)
		{
			//cout<<"\nSelected "<<q[i].no<<endl;
			selected = i;
			flag = 1;
			break;
		}
	}
	if(!flag){
		round++;
		return getNext(q,n,curr_time,quantum,round);
	}
	else{
		q[selected].round++;
		int exec = quantum;
		if(q[selected].completed+quantum>q[selected].burst)
		{	
			exec = (q[selected].completed+quantum)-q[selected].burst;
			q[selected].finish=curr_time+exec;
		}
		else if(q[selected].completed+quantum==q[selected].burst)
		{
			q[selected].finish=curr_time+exec;
		}
		q[selected].completed+=exec;
		curr_time+=exec;
		return q[selected];
	}
}

process *order;
int schedule (process* q, int n,int quantum, int maxtime)
{
	//cout<<"\nMaxtime:"<<maxtime<<" - "<<maxtime/(float)quantum;
    rounds = ceil(maxtime/(float)quantum);
	order = new process[rounds+1];
	//cout<<"\nRounds:"<<rounds<<endl;
	int currenttime = q[0].arrival;
	int i=0,round=0;
	int j = 0;
	do
	{
		process p = getNext(q,n,currenttime,quantum,round);
		//cout<<"\nP:"<<p.no<<endl;
		order[j++] = p;
		//cout<<"\nj:"<<j<<" time:"<<currenttime<<"Round:"<<round<<endl;
		
		// i=(i+1)%n;
		// if(q[i].round == round)round++;

	}
	while(j<=rounds);
	
	return j;
}

void display_order(int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<"P"<<order[i].no<<"\t";
	}
	cout<<endl;
}

void display(process *q,int n,int simple)
{	
	float avgwait=0,avgturn=0;
	cout<<"Process\tArrival\tBurst\t";
	if(!simple)
	cout<<"Finish\tWaiting\tTurnaround";cout<<"\n";
	for(int i=0;i<n;i++)
	{
		cout<<"P"<<q[i].no<<"\t"<<q[i].arrival<<"\t"<<q[i].burst;
		if(!simple){
		cout<<"\t"<<q[i].finish<<"\t"<<q[i].waiting<<"\t"<<q[i].turnaround;
			avgwait += q[i].waiting;	
			avgturn += q[i].turnaround;
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
	int n,quantum,maxtime=0;
	cout<<"Enter number of processes: ";
	cin>>n;
	process q[n];

	cout<<"Enter arrival and burst times of each process:\n";

	for(int i=0;i<n;i++)
	{	
		q[i].no = i+1;
		q[i].completed = 0;
		q[i].round = -1;
		q[i].finish = -1;
		cin>>q[i].arrival>>q[i].burst;
		maxtime+=q[i].burst;
	}
	cout<<"\nEnter quantum size:";
	
	cin>>quantum;
	
	//sort based on arrival
	qsort(q,n,sizeof(process),cmp_process_arrival);
	int on= schedule(q,n,quantum,maxtime);
	calc_times(q,n);
	cout<<"Processes:\n";
	display(q,n,1);
	cout<<"RR order\n";
	display_order(on);
	display(q,n);
	return 0;

}
