#pragma once
#include <string>
#include <regex>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class GenDefault {
protected:
	string tmp_gen;
	string title, server, port, channel, password;
	short int errCode;
	bool isAcceptable;
	regex templateRg;
public:
	GenDefault();
	~GenDefault();
	void choose_errCode();
	int ret_errCode() const;
	string rnd_str() const;
	void rnd_title();
	void rnd_server();
	void rnd_port();
	void rnd_channel();
	void rnd_password();
	void combineStr();
	bool checkResult() const;
	void clearCash();
	string getGenStr() const;
	friend std::ostream& operator << (std::ostream& os, const GenDefault& GenStr);
	friend std::ofstream& operator << (std::ofstream& os, const GenDefault& GenStr);
};

