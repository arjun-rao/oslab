#include <iostream>


using namespace std;

int main(){
        int n, r, pagefaults = 0, nextToReplace = 0;
        cout<<"Enter the number of page frames\n";
        cin >> n;
        int frames[n];

        cout<<"Enter the number of page requests\n";
        cin >> r;

        for(int i = 0; i < n; i++){
                frames[i] = -1;
        }

        cout<<"Enter the page requests\n";
        for(int i = 0; i < r; i++){

            int request;
            cin >> request;
            bool flag = false;

            cout << request << ": ";

            // Checks if request exists in page frames
            for( int j = 0; j < n; j++){
                if(frames[j] == request){
                    flag = true;
                    for(int k = 0; k < n; k++){
                        cout << frames[k] << " ";
                    }
                    cout << endl;
                }
            }
            if(flag) continue; // no page fault

            frames[nextToReplace] = request;
            pagefaults++;
            nextToReplace = (nextToReplace + 1) % n;

            for( int j = 0; j < n; j++){
                    cout << frames[j] << " ";
            }
            cout<<endl;
        }
        cout<<"Number of Page Faults: "<< pagefaults << endl;
}