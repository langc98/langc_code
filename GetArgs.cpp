#include"GetArgs.h"
#include <iostream>

GetArgs::GetArgs()
{
}

GetArgs::~GetArgs()
{
}

void GetArgs::InitArgs(int argc, char* argv[], map<string, string>& args) {
	for (int i = 1; i < argc; i++) {
		string a(argv[i]);
		if (a[0] != '-') {
			continue;
		}
		int at = a.find("=");
		string key = a.substr(1, at - 1);
		string val = a.substr(at + 1);
		args[key] = val;
	}
}

string GetArgs::GetArg(map<string, string>& argv, string key) {
	if (argv.count(key) == 0) {
		cout << "ERROR: Illegal key: " << key.c_str() << endl;
		return "0";
		//exit(1);
	}
	return argv[key];
}


void GetArgs::ParseArgs(int argc, char** argv)
{
	map<string, string> args;
	InitArgs(argc, argv, args);

	Constants::NumOfNodes = atoi(GetArg(args, "n").c_str());
	Constants::Alg = atoi(GetArg(args, "alg").c_str());
	Constants::DataSet = atoi(GetArg(args, "data").c_str());
	Constants::K = atoi(GetArg(args, "k").c_str());
	Constants::IsMinDist = atoi(GetArg(args, "md").c_str());
	Constants::Eps = atof(GetArg(args, "eps").c_str());
}