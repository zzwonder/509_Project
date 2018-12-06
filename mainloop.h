#pragma once
//#define RANDOM
//#define TWO_OCCUR
#define WEIGHT
bool unit_propagation();
int back_track();
int pick_variable();
bool push_assignment(int choice, int assigntype, bool canfilp);
void insert_unit_clause(int i);
void dbll_mainloop();
extern bool fail;
extern bool timeout;
extern ofstream logout;