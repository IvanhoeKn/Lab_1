#include "GenDefault.h"

GenDefault::GenDefault() : tmp_gen(), title(), server(), port(), channel(), password() {
	errCode = 0;
	isAcceptable = false;
	templateRg = "irc:://([a-zA-Z0-9]+)(:[0-9]+)?(/[a-zA-Z0-9]+)?(\\?[a-zA-Z0-9]+)?";
}

GenDefault::~GenDefault() {
	tmp_gen.clear();
	title.clear();
	server.clear();
	port.clear();
	channel.clear();
	password.clear();
}

void GenDefault::choose_errCode() {
	errCode = rand() % 5;
	if (!errCode)
		isAcceptable = true;
	if (errCode == 1)
		errCode = errCode * 10 + (1 + rand() % 5);
}

int GenDefault::ret_errCode() const {
	return errCode;
}

void GenDefault::rnd_title() {
	title = "irc://";
}

string GenDefault::rnd_str() const {
	string tmp;
	short int length = 1 + rand() % 22;
	for (int i = 0; i < length; i++) {
		if (!(rand() % 2))
			tmp.append(1, char('a' + rand() % ('z' - 'a')));
		else
			tmp.append(1, char('A' + rand() % ('Z' - 'A')));
	}
	return tmp;
}

void GenDefault::rnd_server() {
	server = rnd_str();
}

void GenDefault::rnd_port() {
	stringstream io_Str;
	int portNum = 1 + rand() % 65535;
	io_Str << portNum;
	io_Str >> port;
	port = ":" + port;
}

void GenDefault::rnd_channel() {
	channel = "/" + rnd_str();
}

void GenDefault::rnd_password() {
	password = "?" + rnd_str();
}

void GenDefault::combineStr() {
	clearCash();
	isAcceptable = true;
	rnd_title();
	rnd_server();
	tmp_gen = title + server;
	if (rand() % 2) {
		rnd_port();
		tmp_gen += port;
	}
	if (rand() % 2) {
		rnd_channel();
		tmp_gen += channel;
	}
	if (rand() % 2) {
		rnd_password();
		tmp_gen += password;
	}
}

bool GenDefault::checkResult() const {
	if (tmp_gen.length() <= 80) {
		bool result = regex_match(tmp_gen, templateRg);
		return result;
	}
	else
		return false;
}

void GenDefault::clearCash() {
	errCode = 0;
	isAcceptable = false;
	tmp_gen.clear();
	title.clear();
	server.clear();
	port.clear();
	channel.clear();
	password.clear();
}

string GenDefault::getGenStr() const {
	return tmp_gen;
}

std::ostream& operator << (std::ostream& os, const GenDefault& GenStr) {
	os << GenStr.tmp_gen << endl;
	return os;
}

std::ofstream& operator << (std::ofstream& os, const GenDefault& GenStr) {
	os << GenStr.tmp_gen << endl;
	return os;
}