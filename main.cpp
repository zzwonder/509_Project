#include "stdafx.h"


int main()
{
	cout << "begin" << endl;
//	create_random_benchmarks();
//	return 0;
	logout.open("../solutions/log.txt");
	read_case("../benchmarks/v400_c2400/1.txt");
//	read_case("../benchmarks/add.txt");
	dbll_mainloop();
	output("1.txt");
//	output("add.txt");
	cout << "finished" << endl;
//	int x;
//	cin >> x;
    return 0;
}

