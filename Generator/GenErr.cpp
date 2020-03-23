#include "GenErr.h"

GenErr::GenErr() : GenDefault() {
	exprRg = "[a-zA-Z0-9]";
}

GenErr::~GenErr() {}

string GenErr::rnd_str_err() const {
	string tmp;
	short int length = 1 + rand() % 22;
	do {
		for (int i = 0; i < length; i++)
			tmp.append(1, char(33 + rand() % 94));
	} while (regex_match(tmp, exprRg));
	return tmp;
}

void GenErr::rnd_title_err() {
	regex rg_tmp;
	rg_tmp = "irc://";
	string tmp = "";
	do {
		if (!(rand() % 2)) {
			for (int i = 0; i < 3; i++)
				tmp.append(1, char(33 + rand() % 94));
			tmp += "://";
		}
		else {
			tmp = "irc:";
		}
	} while (regex_match(tmp, rg_tmp));
	title = tmp;
}

void GenErr::rnd_server_err() {
	server = rnd_str_err();
}

void GenErr::rnd_port_err_symbol() {
	port = ":" + rnd_str_err();
}

void GenErr::rnd_channel_err() {
	channel = "/" + rnd_str_err();
}

void GenErr::rnd_password_err() {
	password = "?" + rnd_str_err();
}

void GenErr::rnd_port_err_number() {
	int tmp = rand() + 65536;
	stringstream io;
	io << tmp;
	io >> port;
	port = ":" + port;
}

void GenErr::rnd_too_long() {
	int length = rand() + 80;
	for (int i = 0; i < length; i++) {
		if (!(rand() % 2))
			server.append(1, char('a' + rand() % ('z' - 'a')));
		else
			server.append(1, char('A' + rand() % ('Z' - 'A')));
	}
}

void GenErr::combineStr() {
	clearCash();
	choose_errCode();
	switch (errCode) {
	case 11:
		rnd_title_err();
		break;
	case 12:
		rnd_server_err();
		break;
	case 13:
		rnd_port_err_symbol();
		break;
	case 14:
		rnd_channel_err();
		break;
	case 15:
		rnd_password_err();
		break;
	case 3:
		rnd_port_err_number();
	case 5:
		rnd_too_long();
		break;
	}
	if (errCode != 11)
		rnd_title();
	if (errCode != 12 && errCode != 5)
		rnd_server();
	tmp_gen = title + server;
	if (errCode != 4) {
		if (!port.length() && rand() % 2) {
			rnd_port();
			tmp_gen += port;
		}
		if (!channel.length() && rand() % 2) {
			rnd_channel();
			tmp_gen += channel;
		}
		if (!password.length() && rand() % 2) {
			rnd_password();
			tmp_gen += password;
		}
	}
	else {
		rnd_port();
		rnd_channel();
		rnd_password();
		int tmp_choose = 1 + rand() % 4;
		switch (tmp_choose) {
		case 1:
			tmp_gen += channel + port + password;
			break;
		case 2:
			tmp_gen += channel + password + port;
			break;
		case 3:
			tmp_gen += password + port + channel;
			break;
		case 4:
			tmp_gen += password + channel + port;
			break;
		}
	}
}

std::ostream& operator << (std::ostream& os, const GenErr& GenStr) {
	os << GenStr.tmp_gen << endl;
	return os;
}

std::ofstream& operator << (std::ofstream& os, const GenErr& GenStr) {
	os << GenStr.tmp_gen << endl;
	return os;
}