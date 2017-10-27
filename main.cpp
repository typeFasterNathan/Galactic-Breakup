#include <iostream>
#include <fstream>

using namespace std;

class Monarchy {
    public:
    int numberOfDominions;
    int* dominions;
};

int main(int argc, char **argv) {
    if(argc != 2) {
        cout << "error: incorrect number of arguments" << endl;
    }

    string filename(argv[1]);
    ifstream infile(filename);
    if(infile.is_open()) {
        string instring;
        getline(infile, instring);
        int numberOfProblems = stoi(instring); 
        
        for (int i = 0; i < numberOfProblems; i++) {
            
            infile >> instring;     // parse first line of problem
            int n = stoi(instring);
            infile >> instring;
            int m = stoi(instring);
            infile >> instring;
            int k = stoi(instring);
            infile >> instring;
            int numberOfMonarchies = stoi(instring);
            
            for(int k = 0; k < numberOfMonarchies; k++) { 
                infile >> instring;
                int numberOfDominions = stoi(instring);
                for(int j = 0; j < numberOfDominions; j++) {

                }
            }
        }
    }
    return 0;
}




















