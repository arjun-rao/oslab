#include <iostream>
#include <string>

using namespace std;

struct process{
        int alloc[20];
        int max[20];
        int need[20];
        int isProcessed;
};

int main()
{
    int n, r;
    cout<<"No of Processes\n";
    cin >> n;
    cout<<"No of Resources\n";
    cin >> r;

    process q[n];
    int avail[r], total[r];

    for( int i = 0;  i < n; i++ )
        q[i].isProcessed = 0;

    cout<<"Enter total number of each resource\n";
    for( int i = 0;  i < r; i++ )
        cin >> total[i];

    cout<<"Enter max allocation matrix\n";
    for(int i = 0; i < n; i++)
        for( int j = 0; j < r; j++)
                cin >> q[i].max[j];

    cout<<"Enter allocated matrix\n";
    for(int i = 0; i < n; i++)
        for( int j = 0; j < r; j++)
                cin >> q[i].alloc[j];

    // Need Matrix
    for(int i = 0; i < n; i++)
        for( int j = 0; j < r; j++)
            q[i].need[j] = q[i].max[j] - q[i].alloc[j];

    // Available Vector
    for ( int i = 0; i < r; i++){
        avail[i] = total[i];
        for( int j = 0; j < n; j++)
        {
            avail[i] -= q[j].alloc[i];
        }
    }


    int i = 0, count;
    bool flag = false;
    while( i < n )
    {
            int select = -1;
            for(int process = 0; process < n; process++){
                count = 0;
                if(!q[process].isProcessed){
                    for(int res = 0; res < r; res++){
                        if( q[process].need[res] <= avail[res]){
                            count++;
                        }
                        else
                            break; //try for next process
                    }
                }
                if ( count == r )
                {
                    select = process;
                    flag = true;
                    break;
                }
            }
            if(flag){
                    flag = false;
                    q[select].isProcessed = 1;
                    cout << "P" << select << ", ";

                    for(int j = 0;j < r; j++){
                        avail[j] = avail[j] + q[select].alloc[j];
                    }
                    i++;
            }
            else{
                    cout<<"\nNo safe sequence exists"<<endl;
                    return 0;
            }
    }
    cout<<" is the safe sequence"<<endl;
}