#include "stdafx.h"

void output(string input_dir,string input_no) {
	string sol_str = "D:/zzw/509_Project/solutions/";
#ifdef RANDOM
	sol_str += "random/";
#endif
#ifdef TWO_OCCUR
	sol_str += "2-occ/";
#endif
#ifdef WEIGHT
	sol_str += "weight/";
#endif
#ifdef WEIGHT_REV
	sol_str += "weight_rev/";
#endif
#ifdef COMB_WEIGHT
	sol_str += "comb_weight/";
#endif
	ofstream fout;
	fout.open(sol_str + input_dir +"/"+"sol_"+input_no+".txt");
	if (!fout) {
		cout << "first time fail to open: " << sol_str + input_dir + "/" + "sol_" + input_no + ".txt" << endl;
		_mkdir((sol_str+ input_dir).c_str());
		cout << "mkdir: " << sol_str + input_dir << endl;
		fout.open(sol_str + input_dir + "/" + "sol_" + input_no+".txt");
	}
	cout << "file=" << input_dir + "/" + "sol_" + input_no << endl;
	if (!fout) {
		cout << "fail to open solution file" << endl;
	}
	cout << "output" << endl;
	if (timeout) {
		fout << "s " << Dsize.type << " -1" << " " << Dsize.nvars << " " << Dsize.nclauses << endl;
		fout << "t TimeOut " << NumofAssign<<endl;
	}
	else if (fail) {
		cout << "fail" << endl;
		fout << "s " << Dsize.type << " 0" <<" "<<Dsize.nvars<<" "<<Dsize.nclauses<<endl;
		fout << "t "<<run_time << " "<< NumofAssign<<endl;
	}
	else {
		fout << "s " << Dsize.type << " 1" << " " << Dsize.nvars << " " << Dsize.nclauses << endl;
		fout << "t " << run_time << " "<< NumofAssign<<endl;
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