#include "stdafx.h"
using namespace std;
stack<int> Assignment;
set<int> Active_clauses;
list<int> Unit_list;
bool fail,timeout;
ofstream logout;
void dbll_mainloop() {
//	logout << "Number of clauses: " << Dsize.nclauses << endl;
	for (int i = 1; i <= Dsize.nclauses; i++) {
		Active_clauses.insert(i);
		insert_unit_clause(i);
	}
	fail = timeout = 0;
	while (!Active_clauses.empty()) {
//		cout << "here" << endl;
		if (!unit_propagation())
		{
			int choice = back_track();
			logout << "back track= " << choice << endl;
			if (choice == 0) {
				fail = 1;
				break;
			}
			push_assignment(choice,ASSIGNED,0);
			for (int i = 1; i <= Dsize.nclauses; i++) {
				insert_unit_clause(i);
			}
			continue;
		}
		if (Active_clauses.empty()) break;
		int choice = pick_variable();
		push_assignment(choice,ASSIGNED,1);
	}
}

int find_unit_variable(int front) {
	for (int i = 0; i < Clauses[front].vars.size(); i++) {
		int var = abs(Clauses[front].vars[i]);
		if (Vars[var].state == UNDECIDED) {
			return Clauses[front].vars[i];
		}
	}
	return 0;
}

bool conflict_in_find_literal_in_clause(int choice, int clause) {
	for (int i = 0; i < Clauses[clause].vars.size(); i++) {
		if (abs(Clauses[clause].vars[i]) == abs(choice)) {
			if ((Clauses[clause].vars[i] + choice) != 0) return false;
		}
	}
	return true;
}

bool conflict(int var) {
	return (var==(int)abs(var)*Vars[abs(var)].state);
}

bool unit_propagation() {
	while (!Unit_list.empty()) {
//		cout << "not empty" << endl;
		int front = Unit_list.front();
//		cout << "front in list=" << front<<endl;
		Unit_list.pop_front();
		if (Clauses[front].active_vars != 1 || (!Active_clauses.count(front))) continue;
		assert(Clauses[front].active_vars == 1);
		int var = find_unit_variable(front);
		logout << "In unit pro: " << "clause " << front << " is unit";
	//	cout << "find unit variable=" << var << endl;
		if (var == 0) {
			continue;
		}
		if (!push_assignment(var, UNITP, 0)){
			Unit_list.clear();
			return false;
		}
	}
	//TODO: unit propagate as many as possible. Return false if find conflict
	/*1.delete a unit clause in front of the list
	5.return false if conflict happens
	*/
	return true;
}



int back_track() {
	bool fail = false;
	while (!Assignment.empty()) {
		int var = Assignment.top();
		logout << "top of assignment=" << var<<endl;
		Assignment.pop();
//		cout<<"size="<<Vars[var].support.size()<<endl;
		for (int i = 0; i < Vars[var].support.size(); i++) {
			int supclause = Vars[var].support[i];
			Clauses[supclause].support_vars--;
			if (Clauses[supclause].support_vars == 0) {
				assert(!Active_clauses.count(supclause));
				Active_clauses.insert(supclause);
				if (supclause == 1500) logout << "adding 1500 back by " << var << endl;
			}
		}
		Vars[var].support.clear();
		for (int i = 0; i < Vars[var].clauses.size(); i++) {
			int clause = Vars[var].clauses[i];
			Clauses[clause].active_vars++;
			if (Clauses[clause].active_vars == 1) {
	//			cout << "push unit" << clause << endl;
				Unit_list.push_front(clause);
			}
		}
		int old_state = Vars[var].state;
		Vars[var].assigned_type = UNASSIGNED;
		Vars[var].state = UNDECIDED;
		
		if (Vars[var].can_flip==1) {
			logout << var << "can flip" << endl;
//			Vars[var].state = -old_state;
			Vars[var].can_flip = 0;
			logout << "flip to" << -(int)old_state*var << endl;
			return -(int)old_state*var;
		}
		else {
			Vars[var].can_flip = 1;
		}
//		cout << "loop end" << endl;
	}
	return 0;
	/*
	TODO:
	1.back track to the last assignment which can be filp in the stack
	2.return 0 if failed.
	3.deal with active clauses, variables' support and unit list.
	4.clear all x's attributes about assignments
	*/
}

int pick_variable() {
#ifdef RANDOM
	return random_pick();
#endif
#ifdef TWO_OCCUR
	return two_occur();
#endif // TWO_OCCUR

#ifdef WEIGHT
	return weight_pick();
#endif
	return 0;
	//	TODO: 1.pick a variable by heuristic 
}

bool push_assignment(int choice,int assignedtype,bool canflip) {
	bool success = 1;
	int var = abs(choice);
	if (assignedtype == ASSIGNED) logout << "pick value:";
	logout << "push assignment: var is "<<var <<" choice is "<<choice<< endl;
	assert(Vars[var].state == UNDECIDED);
	Vars[var].state = (int)abs(choice) / choice;
	Vars[var].can_flip = canflip;
	Vars[var].assigned_type = assignedtype;
	Assignment.push(var);

	for (int i = 0; i < Vars[var].clauses.size(); i++) {

		int clause = Vars[var].clauses[i];
		Clauses[clause].active_vars--;
		if (!conflict_in_find_literal_in_clause(choice,clause)) {
	//		cout << "not conflict" << endl;
			Clauses[clause].support_vars++;
			Vars[var].support.push_back(clause);
	//		cout << "push" << clause << " to " << var << " 's support" << endl;
			if (Active_clauses.count(clause)){
				Active_clauses.erase(clause);
			}
		}
		else {
		//	cout << "conflict" << endl;
			if (Clauses[clause].active_vars == 1 && (Active_clauses.count(clause))) {
	//			cout << "push unit " << clause << endl;
				Unit_list.push_front(clause);
			}
			else if (Clauses[clause].active_vars == 0 && (Clauses[clause].support_vars == 0)) {
				logout<<"conflict at clause "<<clause<<" and assignment "<<choice<<endl;;
				success = 0;
//				cout << "fail" << endl;
			}
		}
	}
	return success;
	/* TODO: 1.assign the value of the variable and other attributes
      2.for all clauses cc contains x, 
		if active == 1 push cc to List, 
		write other attributes of cc. 
		delete active clauses
	*/
}

void insert_unit_clause(int i) {
	//logout << "now at " << i << endl;
	if ((Clauses[i].active_vars == 1) && (Active_clauses.count(i))) {
//		logout << "insert unit clause " << i << endl;
		Unit_list.push_front(i);
	}
}