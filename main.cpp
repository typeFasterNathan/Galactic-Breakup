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
    Dominion (int r) {
		rank = r;
		parent = this;
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
			bool oneMonarchy = true;
			int monthsUnified;
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
			for (int x = 0; x < n; x++) {
				galaxy[i] = new Dominion*[m];
				for (int y = 0; y < m; y++) {
					galaxy[x][y] = new Dominion[k];
				}
			}
			if (checkUnified(galaxy, n, m, k) == true) {
				monthsUnified++;
			}
			
			cout << monthsUnified << endl;
        }
    }
    return 0;
}

void makeSet(int place, int n, int m, int k, Dominion ***galaxy) {
	int x = place % n;
	int y = place / n;
	int z = place / (n*m);
	galaxy[x][y][z].rank = 0;
	if (x- 1 >=0){
		if (galaxy[x - 1][y][z].rank != -1) {
			makeUnion(galaxy[x - 1][y][z], galaxy[x - 1][y][z]);
		}
	}
	if (x + 1 < n){
		if (galaxy[x + 1][y][z].rank != -1) {
			makeUnion(galaxy[x + 1][y][z], galaxy[x - 1][y][z]);
		}
	}
	if (y - 1 >= 0) {
		if (galaxy[x][y-1][z].rank != -1) {
			makeUnion(galaxy[x][y][z], galaxy[x][y - 1][z]);
		}
	}
	if (y + 1 < m) {
		if (galaxy[x][y + 1][z].rank != -1) {
			makeUnion(galaxy[x][y][z], galaxy[x][y + 1][z]);
		}
	}
	if (z - 1 >= 0) {
		if (galaxy[x][y][z - 1].rank != -1) {
			makeUnion(galaxy[x][y][z],
				galaxy[x][y][z - 1]);
		}
	}
	if (z + 1 < k) {
		if (galaxy[x][y][z + 1].rank != -1) {
			makeUnion(galaxy[x][y][z],
				galaxy[x][y][z + 1]);
		}
	}

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
bool checkUnified(Dominion*** galaxy, int n, int m, int k) {
	Dominion temp;
	for (int x = 0; x < n; x++) {
		for (int y; y < m; y++) {
			for (int z = 0; z < k; z++) {
				if (temp.rank != 0) {
					if (&findSet(galaxy[x][y][z]) != &findSet(temp)) {
						return false;
					}
				}
				temp = galaxy[x][y][z];
			}
		}
	}
	return true;
}