#include "stdafx.h"
using namespace std;
bool neq3(int l[3]) {
	return (l[0] != l[1]) && (l[1] != l[2]) && (l[0] != l[2]);
}
void random_benchmarks(int n, int c) {
	string addpre = "../benchmarks/v" + std::to_string(n) + "_c" + std::to_string(c) + "/";
	ofstream bout;
	for (int i = 1; i <= 100; i++) {
		_mkdir(addpre.c_str());
		string fname = addpre + std::to_string(i)+".txt";
		cout << fname << endl;
		bout.open(fname);
		bout << "p cnf ";
		bout << std::to_string(n) << " " << std::to_string(c) << endl;
		for (int cn = 1; cn <= c; cn++) {
			bout << "s ";
			int l[3] = { 0,0,0 };
			while (!neq3(l)) {
				for (int j = 0; j < 3; j++) {
					l[j] = 1 + rand() % n;
					int sgn = 2 * (rand()%2 - 0.5);
					assert(sgn == 1 || (sgn == -1));
					l[j] = sgn*l[j];
		//			cout << "l[j]= " << l[j] << endl;
				}
			}
			bout << l[0] << " " << l[1] << " " << l[2] <<" 0"<< endl;
		}
		bout.close();
	}
}
void create_random_benchmarks() {
	for (int n = 100; n <= 400; n = n + 100) {
		for (int a = 0; a <= 15; a++) {
			int c = (3 + 0.2*a) * n;
			random_benchmarks(n, c);
		}
	}
}