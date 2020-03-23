#ifndef APPCLASS_H
#define APPCLASS_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include "AppClass_sm.h"

using namespace std;

#ifdef CRTP
class AppClass : public AppClassContext<AppClass>
#else
class AppClass
#endif
{
private:
	AppClassContext _fsm;
	bool isAcceptable;
	string tmpStr;
    string nameServer;
    string PortNumber;
    map <string, int> statistic;
public:
	AppClass(); 
	~AppClass() {}; 
	bool CheckString(string& tmp);
    void AppendStr(char tmp);
	void AppendServer(char tmp);
	void AppendPort(char tmp);
	void setAcceptable();
	void UpdateStatistic();
	void ClearCash();
	bool NotTooLong();
	bool checkPort();
	string& getStr();
	void printStatistic(ofstream& output);
};
#endif
