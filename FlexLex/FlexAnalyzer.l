%option noyywrap
%option c++
%x SERVER ERROR TAIL

%{
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <map>
	#include <ctime>
	#include <FlexLexer.h>
    #include <sstream>

	using namespace std;
	
	class AppClass {
	private:
		string tmpStr;
		string nameServer;
		map<string, int> statistic;
	public:
		AppClass();
		~AppClass();
		int getLen();
		void ClearCash();
		void AddStr(string& tmp);
		void setServerName(string& tmp);
		bool checkPort(string& portNumber);
		void saveStatistic();
		void printStatistic(ofstream& output);
		const string getStr();
	};
	
	AppClass::AppClass() : nameServer(), tmpStr() {}
	
	AppClass::~AppClass() {
        nameServer.clear();		
        statistic.clear();
		tmpStr.clear();
	}

	void AppClass::AddStr(string& tmp) {
		tmpStr += tmp;
	}
		
	void AppClass::ClearCash() {
        nameServer.clear();
		tmpStr.clear();
	}
	
	void AppClass::setServerName(string& tmp) {
		nameServer = tmp;
	}

	int AppClass::getLen() {
		return tmpStr.length();
	}

    bool AppClass::checkPort(string& portNumber) {
	    int port;
	    portNumber.erase(0, 1);
	    istringstream ist(portNumber);
	    ist >> port;
	    if (port > 1 && port < 65536)
		    return true;
	    else
		    return false;
    }

	void AppClass::saveStatistic() {
		if (statistic.find(nameServer) == statistic.end())
			statistic.insert(pair<string, int>(nameServer, 1));
		else
			statistic[nameServer]++;
	}

	void AppClass::printStatistic(ofstream& output) {
		auto it = statistic.begin();
		for (; it != statistic.end(); it++)
			output << "Server name: \"" << it->first << "\" encountered " << it->second << endl;
	}

	const string AppClass::getStr() {
		return tmpStr;
	}

	AppClass FlexAnalyzer;
	ifstream input;
	ofstream output;
	yyFlexLexer ftp(&input, &output);
%}

letter [A-Za-z]
digit  [0-9]
term   (({letter}|{digit})+)

%%
<INITIAL>{
	irc\:\/\/ {
		string tmp = yytext;
		FlexAnalyzer.ClearCash();
		FlexAnalyzer.AddStr(tmp);
		BEGIN(SERVER);
	}
	. {
		string tmp = yytext;
		FlexAnalyzer.ClearCash();
		FlexAnalyzer.AddStr(tmp);
		BEGIN(ERROR);
	}
	\n {
		string tmp = yytext;
		FlexAnalyzer.ClearCash();
		FlexAnalyzer.AddStr(tmp);
		BEGIN(INITIAL);
		return 0;
	}
	<<EOF>> {
		return -1;
	}
}

<SERVER>{
	{term} {
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		FlexAnalyzer.setServerName(tmp);
		BEGIN(TAIL);
	}
	. {
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		BEGIN(ERROR);
	}
	\n {
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		BEGIN(INITIAL);
		return 0;
	}
	<<EOF>> {
		return -1;
	}
}

<TAIL>{
	(\:{term})?(\/{term})?(\?{term})?(\n) {
		bool check = false;
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		if (FlexAnalyzer.getLen() <= 80)
			check = true;
		if (check && tmp[0] == ':')
			check = FlexAnalyzer.checkPort(tmp);
		if (check) {
			FlexAnalyzer.saveStatistic();
			BEGIN(INITIAL);
			return 1;
		}
		else {
			BEGIN(INITIAL);
			return 0;
		}
	}
	. {
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		BEGIN(ERROR);
	}
	<<EOF>> {
		return -1;
	}
}

<ERROR>{
	\n {
		string tmp = yytext;  
		FlexAnalyzer.AddStr(tmp);
		BEGIN(INITIAL);
		return 0;
	}
    . {
		string tmp = yytext;  
		FlexAnalyzer.AddStr(tmp);
	};
    <<EOF>> {
		return -1;
	}
}
%%

int main(int argc, char* argv[]) {
	std::ofstream statistic;
    if(argc > 2) {
        input.open(argv[1]);
        output.open(argv[2]);
        statistic.open(argv[3]);     
    } 
    else {
        cout << "Not enough arguments!" << endl;
        return 1;
    }
    if(!(input.is_open() && output.is_open() && statistic.is_open())){
    	cout << "Error of openning files!" << endl;
        return -1;
    }
    clock_t _clock = clock();
	time_t _time = time(0);
	//--------------------------------------------------------------------
	int result = 0;
	while (result != -1) {
		result = ftp.yylex();
		switch (result) {
			case 1:
				output << "Acceptable string! " << FlexAnalyzer.getStr();
				continue;
			case 0:
				output << "Unacceptable string! " << FlexAnalyzer.getStr();
			case -1:
				break;
		}
	}
	FlexAnalyzer.printStatistic(statistic);
	statistic << "\nElapsed time: " << time(0) - _time << " seconds (" << clock() - _clock << " clock ticks)." << endl;
	input.close();
	output.close();
	statistic.close();
	return 0;
}
