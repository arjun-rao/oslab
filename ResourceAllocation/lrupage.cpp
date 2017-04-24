#include <iostream>


using namespace std;

int main(){
        int n, r, pagefaults = 0, nextToReplace = 0;
        cout << "Enter the number of page frames\n";
        cin >> n;
        int frames[n];
        int last_used[n];

        cout<<"Enter the number of page requests\n";
        cin >> r;

        for(int i = 0; i < n; i++ ){
                frames[i] = -1;
                last_used[i] = 999; // last_used 999 iterations ago
        }

        for(int i = 0; i < r; i++){
                int request, foundPos;
                cin >> request;
                bool flag = false;
                cout << request << ": ";

                for(int j = 0; j < n; j++){
                        last_used[j]++;   // increment each frame by 1, thus increasing its age (when last used)
                }

                // Checks if request exists in page frames
                for(int j = 0; j < n; j++){
                    if(frames[j] == request){
                            foundPos = j;
                            flag = true;
                            for(int k = 0; k < n; k++){
                                cout << frames[k] << " ";
                            }
                            cout << endl;
                    }
                }
                if(flag){
                        last_used[foundPos] = 0; // changes last_used to 0 cause accessed just now
                        continue;
                }

                pagefaults++;
                int max = 0, pos = 0; // max contains the age of oldest frame i.e least recently used
                for(int j = 0; j < n; j++){
                        if( last_used[j] > max ){
                                max = last_used[j];
                                pos = j;
                        }
                }
                nextToReplace = pos; // replaces oldest frame
                frames[nextToReplace] = request;
                last_used[nextToReplace] = 0;  // initalises age of newly put in frame to 0

                for(int j = 0; j < n; j++){
                        cout<<frames[j]<<" ";
                }
                cout<<endl;
        }
        cout<<"Number of Page Faults: "<< pagefaults << endl;
}