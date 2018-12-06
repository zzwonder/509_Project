#pragma once
#include "stdafx.h"
#define MAXNV 403
#define MAXNC 2403

#define UNITP -1
#define ASSIGNED 1
#define UNASSIGNED 0

#define TRUE 1
#define FALSE -1
#define UNDECIDED 0
using namespace std;
struct variable{
	int id;
	int state;
	bool can_flip;
	vector<int> support; //clauses satisfied by this variable
	vector<int> clauses;
	int assigned_type;
	variable(){
		state = UNDECIDED;
		can_flip = 1;
		assigned_type = UNASSIGNED;
	}
	variable(int cid) {
		id = cid;
		state = UNDECIDED;
		can_flip = 1;
		assigned_type = UNASSIGNED;

	}
};