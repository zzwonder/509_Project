#pragma once
using namespace std;
extern variable Vars[MAXNV];
extern clause Clauses[MAXNC];
void read_case(string firename);
void output(string filename);
struct datasize {
	string type;
	int nvars;
	int nclauses;
	datasize(){}
};
extern datasize Dsize;