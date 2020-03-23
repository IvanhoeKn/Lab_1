#pragma once
#include "GenDefault.h"
class GenErr : public GenDefault {
private:
	regex exprRg;
public:
	GenErr();
	~GenErr();
	void combineStr();
	void rnd_title_err();
	string rnd_str_err() const;
	void rnd_server_err();
	void rnd_port_err_symbol();
	void rnd_channel_err();
	void rnd_password_err();
	void rnd_port_err_number();
	void rnd_too_long();
	friend std::ostream& operator << (std::ostream& os, const GenErr& GenStr);
	friend std::ofstream& operator << (std::ofstream& os, const GenErr& GenStr);
};

