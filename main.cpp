#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Dominion {
    public:
	Dominion() {
		rank = -1;
		parent = this;
	}
    Dominion (int r, Dominion * par) {
		rank = r;
		parent = par;
    }

	int rank;
	Dominion* parent;
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
			int** months = new int* [numberOfMonarchies];
            // parse each monarchy
            for(int k = 0; k < numberOfMonarchies; k++) {  
                infile >> instring;
                int numberOfDominions = stoi(instring);
				months[k] = new int[numberOfDominions];
                for(int j = 0; j < numberOfDominions; j++) {
                    infile >> instring;
					months[k][j] = stoi(instring);
                }
            }
			Dominion*** galaxy = new Dominion**[n];
			for (int i = 0; i < n; i++) {
				galaxy[i] = new Dominion*[m];
				for (int j = 0; j < m; j++) {
					galaxy[i][j] = new Dominion[k];
				}
			}
			

        }
    }
    return 0;
}

void makeSet(Dominion x, int place) {
	x.parent = &x;
	x.rank = 0;
}
void makeUnion(Dominion x, Dominion y) {
	link(findSet(x), findSet(y));
}
void link(Dominion x, Dominion y) {
	if (x.rank > y.rank) {
		y.parent = &x;
	}
	else {
		x.parent = &y;
		if (x.rank == y.rank) {
			y.rank = y.rank + 1;
		}
	}
}
Dominion findSet(Dominion x) {
	if (&x != x.parent) {
		x.parent = &findSet(*x.parent);
	}
	return *x.parent;
}
