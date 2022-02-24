#pragma once
#include<map>
#include<vector>
#include<string>
#include"Constants.h"
using namespace std;

class GetArgs
{
public:
	GetArgs();
	~GetArgs();

	void InitArgs(int argc, char* argv[], map<string, string>& args);
	string GetArg(map<string, string>& argv, string key);
	void ParseArgs(int argc, char** argv);
};

