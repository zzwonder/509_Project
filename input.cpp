#include "stdafx.h"
using namespace std;
struct datasize Dsize;
struct variable Vars[MAXNV];
struct clause Clauses[MAXNC];
void read_case(string filename) {
	ifstream fin;
	fin.open(filename);
	cout << "open: " << filename << endl;
	if (!fin) {
		cout << "fail to open " <<filename<< endl;
	}
	char command;
	int snum = 0;
	for (int i = 1; i < MAXNV; i++) {
		Vars[i] = variable(i);
	}
	while (fin >> command) {
		if (command == 'c') {
			char ign[100];
			fin.getline(ign,100);
	//		cout << ign << endl;
		}
		else if (command == 'p') {
			fin >> Dsize.type >> Dsize.nvars >> Dsize.nclauses;
		}
		else if (command == 's') {
			snum++;
			int varno;
			fin >> varno;
			while (varno != 0) {
				Clauses[snum].vars.push_back(varno);
				Vars[abs(varno)].clauses.push_back(snum);
				fin >> varno;
			}
	//		cout << "clause " << snum << " has " << Clauses[snum].vars.size() << " variables" << endl;
//			logout << "clause " << snum << " has " << Clauses[snum].vars.size() << " variables" << endl;
			Clauses[snum].active_vars = Clauses[snum].vars.size();
		}
	}
	fin.close();
}