#include "stdafx.h"
int random_pick() {
	int n_activev = 0;
	for (int i = 1; i <= Dsize.nvars; i++) {
		if (Vars[i].state == UNDECIDED) {
			n_activev++;
		}
	}
	unsigned int tseed = time(NULL);
	srand(tseed);
	int ran = rand() % n_activev;
	for (int i = 1; i <= Dsize.nvars; i++) {
		if (Vars[i].state == UNDECIDED) {
			if (ran == 0) {
				int tf = 0;//rand() % 2;
			//	cout << "tf=" << tf << endl;
				return (int)(2 * (tf - 0.5)*i);
			}
			else ran--;
		}
	}
	return 0;
}

int two_occur() {
	int negcount[MAXNV];
	int poscount[MAXNV];
	for (int i = 1; i < MAXNV; i++) negcount[i] = poscount[i] = 0;
	set<int>::iterator i1 = Active_clauses.begin();
	set<int>::iterator i2 = Active_clauses.end();
	for (; i1 != i2; i1++) {	
		int ac = *i1;
		if (Clauses[ac].active_vars == 2) {
			for (int i = 0; i < Clauses[ac].vars.size();i++) {
				if (Vars[abs(Clauses[ac].vars[i])].state != UNDECIDED) continue;
				if (Clauses[ac].vars[i]>0) {
					poscount[Clauses[ac].vars[i]]++;
				}
				else if (Clauses[ac].vars[i]<0) {
					negcount[abs(Clauses[ac].vars[i])]++;
				}
			}
		}
	}
	int total_max = 0, choice = 0;
	for (int i = 1; i <= Dsize.nvars; i++) {
		if (total_max < poscount[i] + negcount[i]) {
			total_max = poscount[i] + negcount[i];
			choice = i;
		}
	}
	if (choice == 0) return random_pick();
	logout << "2 occur choises " << choice <<"with "<<poscount[choice]<<" vs "<<negcount[choice] <<endl;
	if (poscount[choice] < negcount[choice]) return -1 * choice;
	return choice;
}

int weight_pick() {
	double negweight[MAXNV];
	double posweight[MAXNV];
	for (int i = 1; i < MAXNV; i++) negweight[i] = posweight[i] = 0;
	set<int>::iterator i1 = Active_clauses.begin();
	set<int>::iterator i2 = Active_clauses.end();
	for (; i1 != i2; i1++) {
		int ac = *i1;
			for (int i = 0; i < Clauses[ac].vars.size(); i++) {
				if (Vars[abs(Clauses[ac].vars[i])].state != UNDECIDED) continue;
				if (Clauses[ac].vars[i]>0) {
					posweight[Clauses[ac].vars[i]]+=1/pow(2,Clauses[ac].active_vars);
				}
				else if (Clauses[ac].vars[i]<0) {
					negweight[abs(Clauses[ac].vars[i])] += 1 / pow(2, Clauses[ac].active_vars);
				}
		}
	}
	double total_max = 0;
	int choice = 0;
	for (int i = 1; i <= Dsize.nvars; i++) {
		if (total_max < posweight[i] + negweight[i]) {
			total_max = posweight[i] + negweight[i];
			choice = i;
		}
	}
	if (choice == 0) return random_pick();
	logout << "Weight occur choises " << choice << "with " << posweight[choice] << " vs " << negweight[choice] << endl;
	if (posweight[choice] < negweight[choice]) return -1 * choice;
	return choice;
}