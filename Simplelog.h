#pragma once
#include<stdafx.h>

using namespace std;

class log {
public:
	log(Json::Value root);
	string printpath;
	bool printLog();
	void setprintpath(string path);


};

log::log(Json::Value root) {
	printpath = "./data/log.txt";
	
}
