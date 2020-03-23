#include "LexAnalyzer.h"
#include <iostream>
#include <sstream>

LexAnalyzer::LexAnalyzer() : templateRg("irc://([a-zA-Z0-9]+)(:[0-9]+)?(/[a-zA-Z0-9]+)?(\\?[a-zA-Z0-9]+)?"), str() {}

LexAnalyzer::~LexAnalyzer() {
	str.clear();
	statistic.clear();
}

bool LexAnalyzer::check() {
	bool result = false;
	if (str.length() <= 80) {
		smatch splitInGroup;
		result = regex_match(str, splitInGroup, templateRg, regex_constants::match_default);
		if (result && splitInGroup.size() > 2) {
			string portNumber = splitInGroup[2];
			if (portNumber[0] == ':' && !checkPort(portNumber))
				result = false;
		}
		if (result) {
			string serverName = splitInGroup[1];
			saveStatistic(serverName);
		}
	}
	return result;
}

void LexAnalyzer::CheckString(istream& input, ofstream& output) {
	getline(input, str);
	bool result = check();
	commit(result, output);
	str.clear();
}

void LexAnalyzer::CheckString(const string& line) {
	bool outCode = true;
	str = line;
	bool result = check();
	ofstream output;
	commit(result, output);
	str.clear();
}

bool LexAnalyzer::checkPort(string& portNumber) {
	int port;
	portNumber.erase(0, 1);
	std::istringstream ist(portNumber);
	ist >> port;
	if (port > 1 && port < 65536)
		return true;
	else
		return false;
}

void LexAnalyzer::saveStatistic(string& serverName) {
	//serverName.erase(0, 7);
	if (statistic.find(serverName) == statistic.end())
		statistic.insert(pair<string, int>(serverName, 1));
	else
		statistic[serverName]++;
}

void LexAnalyzer::commit(bool outCode, ofstream& output) {
	if (!output.is_open()) {
		if (outCode)
			cout << "Acceptable string! \"" << str << "\"\n";
		else
			cout << "Unacceptable string! \"" << str << "\"\n";
	}
	else
		if (outCode)
			output << "Acceptable string! \"" << str << "\"\n";
		else
			output << "Unacceptable string! \"" << str << "\"\n";
}

void LexAnalyzer::printStatistic(ofstream& output) {
	auto it = statistic.begin();
	for (; it != statistic.end(); it++)
		output << "Server name: \"" << it->first << "\" encountered " << it->second << endl;
}