#include "stdafx.h"
#include "puzzle.h"
int num_clause_generated = 0;
bool exceed(int a) {
	return (a > 5 || (a < 1));
}

int puzzle_transform(int literal) {
		int v = abs(literal);
		int a1 = v / 100;
		int a2 = (v / 10) % 10;
		int a3 = v % 10;
		if (exceed(a1) || exceed(a2) || exceed(a3)) return 0;
		return (25 * (a1 - 1) + 5 * (a2 - 1) + (a3))*(v / literal);
}

void imply_output(ofstream &fout, vector<int> pre,vector<int> res) {
	fout << "s ";
	num_clause_generated++;
	for (int i = 0; i < pre.size(); i++) {
		int k = puzzle_transform(pre[i]);
		if (k == 0) continue;
		fout << (int)(-1)*puzzle_transform(pre[i])<<" ";
	}
	for (int i = 0; i < res.size(); i++) {
		int k = puzzle_transform(res[i]);
		if (k == 0) continue;
		fout << puzzle_transform(res[i]) << " ";
	}
	fout << "0" << endl;
}

void create_puzzle()
{
	ofstream fout;
	fout.open("../benchmarks/puzzle.txt");
	fout << "c this is Einstein's Puzzle." << endl;
	imply_output(fout, {}, { 525});//1
	imply_output(fout, {}, { 131 });//1
	imply_output(fout, {}, { 221 });//2
	imply_output(fout, {}, { 341 });//3
	imply_output(fout, {}, { 411 }); //9
	imply_output(fout, {}, {555 });//13
	for (int x = 1; x <= 5; x++) { //5
		imply_output(fout, { x * 100 + 35 }, { x * 100 + 45 });
	}
	for (int x = 1; x <= 5; x++) { //6
		imply_output(fout, { x * 100 + 51 }, { x * 100 + 22 });
	}
	for (int x = 1; x <= 5; x++) { //7
		imply_output(fout, { x * 100 + 34 }, { x * 100 + 52 });
	}
	for (int x = 1; x <= 5; x++) { //8
		imply_output(fout, { x * 100 + 13 }, { x * 100 + 42 });
	}
	for (int x = 1; x <= 5; x++) { //12
		imply_output(fout, { x * 100 + 54 }, { x * 100 + 43 });
	}
	for (int x = 1; x <= 5; x++) {     //4
		for (int y = 1; y <= 5; y++) {
			for (int z = 1; z <= 5; z++) {
				imply_output(fout, { 100 * x + 35,100 * y + 32,100 * x + 10 + z }, { 100 * y + 10 + z + 1 });
			}
		}
	}//lasthere
	for (int x = 1; x <= 5; x++) {//10
		for (int y = 1; y <= 5; y++) {
			for (int z = 1; z <= 5; z++) {
				imply_output(fout, { 100 * x + 53,100 * y + 23,100 * x + 10 + z }, { 100 * y + 10 + z - 1 ,100 * y + 10 + z + 1 });
			}
		}
	}
	for (int x = 1; x <= 5; x++) {//11
		for (int y = 1; y <= 5; y++) {
			for (int z = 1; z <= 5; z++) {
				imply_output(fout, { 100 * x + 24,100 * y + 52,100 * x + 10 + z }, { 100 * y + 10 + z - 1 ,100 * y + 10 + z + 1 });
			}
		}
	}
	for (int x = 1; x <= 5; x++) {//14
		for (int z = 1; z <= 5; z++) {
			imply_output(fout, { 410 + z,100 * x + 33 }, { 100 * x + 10 + z - 1 ,100 * x + 10 + z + 1 });
		}
	} // last here
	for (int x = 1; x <= 5; x++) {//15
		for (int y = 1; y <= 5; y++) {
			for (int z = 1; z <= 5; z++) {
				imply_output(fout, { 100 * x + 53,100 * y + 44,100 * x + 10 + z }, { 100 * y + 10 + z - 1 ,100 * y + 10 + z + 1 });
			}
		}
	}
	for (int x = 1; x <= 5; x++) {// or 
		for (int y = 1; y <= 5; y++) {
			imply_output(fout, {}, { 100 * x + 10 * y + 1, 100 * x + 10 * y + 2,100 * x + 10 * y + 3,100 * x + 10 * y + 4,100 * x + 10 * y + 5 });
		}
	}
	for (int x = 1; x <= 5; x++) { // one person can not have cat and dog at the same time
		for (int y = 1; y <= 5; y++) {
			for (int i = 1; i <= 5; i++) {
				for (int j = 1; j <= 5; j++) {
					if (i == j) continue;
					imply_output(fout, {}, { -1*(100 * x + 10 * y + i), -1*(100 * x + 10 * y + j) });
				}
			}
		}
	}
	for (int y = 1; y <= 5; y++) { // a dog cannot owned by two person
		for (int i = 1; i <= 5; i++) {
			for (int x1 = 1; x1 <= 5; x1++) {
				for (int x2 = 1; x2 <= 5; x2++) {
					if (x1 == x2) continue;
					imply_output(fout, {}, { -(100 * x1 + 10 * y + i), -(100 * x2 + 10 * y + i) });
				}
			}
		}
	}
	fout << "p cnf 125 " << num_clause_generated << endl;
	fout.close();
}
