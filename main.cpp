#include "stdafx.h"


int main(int argc, char** argv)
{
	cout << "begin" << endl;
//	create_random_benchmarks(); return 0;
	logout.open("D:/zzw/509_Project/solutions/log.txt");
	string input_dir = argv[1];
	string input_no = argv[2];
	string input_address = input_dir + "/" + input_no;
	read_case("D:/zzw/509_Project/benchmarks/"+input_address+".txt");
	dbll_mainloop();
	output(input_dir,input_no);
//	output("add.txt");
	cout << "finished" << endl;
    return 0;
}

