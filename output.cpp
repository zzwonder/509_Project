#include "stdafx.h"

void output(string filename) {
	
	ofstream fout;
	fout.open("../solutions/sol_"+filename);
	cout << "file=" << filename << endl;
	if (!fout) {
		cout << "fail to open solution file" << endl;
	}
	cout << "output" << endl;
	if (timeout) {
		fout << "s " << Dsize.type << " -1" << " " << Dsize.nvars << " " << Dsize.nclauses << endl;
	}
	else if (fail) {
		cout << "fail" << endl;
		fout << "s " << Dsize.type << " 0" <<" "<<Dsize.nvars<<" "<<Dsize.nclauses<<endl;
	}
	else {
		fout << "s " << Dsize.type << " 1" << " " << Dsize.nvars << " " << Dsize.nclauses << endl;
		fout << "v ";
		for (int i = 1; i <= Dsize.nvars; i++) {
			if (Vars[i].state == UNDECIDED) {
				unsigned int tseed = time(NULL);
				srand(tseed);
				int sgn = (int)2 * (rand() % 2 - 0.5);
				fout << sgn * i << " ";
			}
			else fout << (int)(Vars[i].state) * i<<" ";
		}
	}
}