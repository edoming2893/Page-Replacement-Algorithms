
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <sstream>


using namespace std;

template < typename T > std::string to_string( const T& n ) {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}


int FIFOalgorithm(string* arr, int numframes){
    
    // number of page faults
    // starting at 1 since my array starts at 0 it will be off by 1 if i start at 0
    int pfaults = 0;
    // represent frames using a vector
    vector <string> frames;
    

    
    // First we will gothrough the list
    // list has maximum of 100 items so we will go throught the entire thing
    for(int i = 0 ; i< 100 ; i++){
        
        // check if the number is already in the frames
        
        if( std::find(frames.begin(), frames.end(), arr[i]) == frames.end() ){
            //increment page fault
            pfaults++;
            
            // check if frames are empty
            if(frames.size() == 0 ){
                frames.push_back(arr[i]);

            }
            // frames not empty but not full so we keep adding pages
            else if (frames.size() < numframes){
                frames.push_back(arr[i]);

            }
            // frames are completely full we must remove a frame
            else if (frames.size() == numframes){
                // remove vector from the top since it is First IN First OUT
                frames.erase(frames.begin());
                // now we add the element to the bottom of the queue
                frames.push_back(arr[i]);
                
            }
        }
        
    }
    
    cout << "Total Number of Page Faults for FIFO Algorithm:     " << pfaults << endl << endl;
    return pfaults;
}


int LRUalgorithm(string* arr, int numframes){
    
    // replace the page that has not been used the longest
    
    // number of page faults
    // starting at 1 since my array starts at 0 it will be off by 1 if i start at 0
    int pfaults = 0;
    
    // represent frames using a vector which will contain the sting and an int
    // the int will be use for "time alive" for LRU
    vector<std::pair<string, int> > frames;
    
    // go thought the string
    for(int i = 0 ; i< 100 ; i++){

        // *******************************************************************
        // if all frames are empty add fault and just add to frames
        if(frames.size() == 0){
            pfaults++;
            frames.push_back(std::make_pair(arr[i], 0) );
        }
        
        // *******************************************************************
    
        // vector not empty but not full add to another frame
        else if(frames.size() < numframes){
            
            bool present = false;
            
            // check to see if page number is already on there
            for(int k=0 ; k< frames.size() ; k++){
                if (frames[k].first == arr[i]) {
                    present = true;
                    // reset time of frame
                    frames[k].second = 0;
                    
                }
            }
            
            // if page number not in vector just add it
            if(present == false){
                pfaults++;
                frames.push_back(std::make_pair(arr[i], 0) );
            }
            
        }
        
        
     
         
        // *******************************************************************
        // vector is full remove frame and add in its place
        else if(frames.size() == numframes)
        {
    
            int maxage = 0;
            int index = 0;
            bool present= false;
            
            // check to see if page number is already on there
            for(int j=0 ; j< frames.size() ; j++){
                if (frames[j].first == arr[i]){
                    present = true;
                    // reset its time to 0
                    frames[j].second = 0;
                }
            }
            // if page number not in vector
            if(present == false){
                pfaults++;
                
                // find the oldest page number which is the least used
                for(int t= 0 ; t< frames.size() ; t++){
                    // if the age of the page in frame[t] is older than maxage
                    // index is 't' ; that is index is now the index of the least used
                    // frame allocated
                    if(maxage < frames[t].second)
                        index = t;
                }
                frames[index].first = arr[i];
                frames[index].second = 0;
    
            }
            
            // update the age of the frames
            for (int u=0; u< frames.size(); u++){
                frames[u].second = frames[u].second + 1;
            }
        }
        
    }
    
    cout << "Total Number of Page Faults for LRU Algorithm:     " << pfaults << endl << endl;
    return pfaults;
}

int OPTalgorithm(string* arr, int numframes){
    
    // replace the page that has not been used the longest
    
    // number of page faults
    // starting at 1 since my array starts at 0 it will be off by 1 if i start at 0
    int pfaults = 0;

    vector<string> frames;
    
    // go thought the string
    for(int i = 0 ; i< 100 ; i++){

        // *******************************************************************
        // if all frames are empty add fault and just add to frames
        if(frames.size() == 0){
            pfaults++;
            frames.push_back(arr[i]);
        }
        
        // *******************************************************************
    
        // vector not empty but not full add to another frame
        else if(frames.size() < numframes){
            

            bool present = false;
            
            // check to see if page number is already on there
            for(int k=0 ; k< frames.size() ; k++){
                if (frames[k] == arr[i]) {
                    present = true;

                }
            }
            
            // if page number not in vector just add it
            if(present == false){
                pfaults++;
                frames.push_back(arr[i]);
            }
            
        }
        
        
     
         
        // *******************************************************************
        // vector is full remove frame and add in its place
        else if(frames.size() == numframes)
        {
            int farthest = 0;
            int indx;
            bool present = false;
            
            // check to see if page number is already on there
            for(int k=0 ; k< frames.size() ; k++){
                if (frames[k] == arr[i]) {
                    present = true;

                }
            }
            
            
            if (present == false){
                // now we will go through the entire vector and determine which frame
                // will be called the farthest from our current position in string
                pfaults++;
                
                for(int o = 0 ; o< frames.size() ; o++){
                    
                    // for each frame in vector we will see when it will be called in our string
                    // where i is where we are at in our string arr since we only care about the 'future'
                    for (int k = i ; k < 100 ; k++ ) {
                        
                        if(arr[k] == frames[o]){
                            // record index of when it occur at the string
                            indx = k;
                            if (farthest < k){
                                farthest = k;
                            }
                            
                        }
                        
                    }
                }
                
                // replace the page number with the 'farthest' frame called in the string
                frames[farthest] = arr[i];

            }

        }

        
    }
    
    cout << "Total Number of Page Faults for OPTIMAL Algorithm:     " << pfaults << endl << endl;
    return pfaults;
}



int main(int argc, const char * argv[]) {
    
    int numframes;
    bool flag = true;
    char type;
    char answ;
    
    // intializing out file txt
    ofstream myfile;
    myfile.open("Algorithm-Results.txt");
    myfile <<"Results for faults of varying algorithms: \n";
    
    /*
    // the command line argume for frame number
    int numframes = atoi(argv[1]);
    */
    string rstring[100];
    
    // using currentitme as seed for random genrator
    time_t t;
    srand((unsigned) time(&t));
    
    

    // making the page reference string list
    for (int i=0; i< 100; i++){
        rstring[i] = to_string( ( 1 + rand() % 49 ) );
    }
     

    
    while(flag){
        
        cout << "Is this a Default Run or a Costum Run?"<< endl;
        cout <<"Default Run: Run Algorithms for range of Page Frames from 0 to 30" << endl;
        cout <<"coustum run will be specified by user one at a time"<<endl<< endl;
        
        cout << "Enter D for default or C for custom Run:  ";
        cin >> type;
        cout << endl;
        
        if(type == 'D'){
            int fifofaults[30];
            int LRUalgoresults[30];
            int OPTalgoresults[30];
            
            
            for(int i= 0; i<30 ; i++){
                numframes = i +1;
                
                fifofaults[i]= FIFOalgorithm(rstring, numframes);

                LRUalgoresults[i] = LRUalgorithm(rstring,numframes);

                OPTalgoresults[i]= OPTalgorithm(rstring,numframes);
                
            }
            
            myfile <<"Results for FIFO Replacement Algorithm: \n";
            
            for(int i =0 ; i<30; i++){
                myfile << fifofaults[i]<<"\n";
            }
            
            myfile << "\n";
            
            myfile <<"Results for LRU Replacement Algorithm: \n";
            
            for(int i =0 ; i<30; i++){
                myfile << LRUalgoresults[i] <<"\n";
            }
            
            myfile << "\n";
            
            myfile <<"Results for Optimal Replacement Algorithm: \n";
            
            for(int i =0 ; i<30; i++){
                myfile << OPTalgoresults[i] <<"\n";
            }
            
            myfile << "\n";
            myfile.close();
            
            flag = false;
        }
        
        else if(type == 'C'){
            
            cout << "Sate The Number of Page Frames: ";
            cin >> numframes;
            cout << endl;
            
            FIFOalgorithm(rstring, numframes);

            LRUalgorithm(rstring,numframes);
            
            OPTalgorithm(rstring,numframes);
            
            cout << "Want to rung it again: answer Y for yes or N for no: ";
            cin >> answ;
            
            if(answ == 'N'){
                flag = false;
            }
            else{
                flag = true;
            }
            
            
        }
        else{
            cout << "WRONG CHOICE TRY AGAIN"<< endl;
        }
    }
    


    return 0;
}
