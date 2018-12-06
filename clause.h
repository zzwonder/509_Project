#pragma once
#include "stdafx.h"
using namespace std;
struct clause
{
	vector<int> vars;
	int active_vars;
	int support_vars;
	clause(){
		support_vars = 0;
	}
};