#include "AppClass.h"

using namespace std;

AppClass::AppClass() : _fsm(*this), isAcceptable(false), tmpStr(), nameServer(), PortNumber(), statistic() {
#ifdef FSM_DEBUG
#ifdef CRTP
	setDebugFlag(true);
#else
	_fsm.setDebugFlag(true);
#endif
#endif
}

bool  AppClass::CheckString(string& inputStr) {
	_fsm.enterStartState();
    _fsm.restart();
	for (int i = 0; i < inputStr.length() - 1; i++) {
        if ((inputStr[i] >= 'a' && inputStr[i] <= 'z') || (inputStr[i] >= 'A' && inputStr[i] <= 'Z')) {
            _fsm.letter(char(inputStr[i]));
            continue;
        }
        if (inputStr[i] >= '0' && inputStr[i] <= '9') {   
            _fsm.digit(char(inputStr[i]));
            continue;
        }
        if (inputStr[i] == ':') {
            _fsm.dots(':');
            continue;
        }
        if (inputStr[i] == '/') {
            _fsm.slash('/');
            continue;
        }
        if (inputStr[i] == '?') {
            _fsm.question('?');
            continue;
        }
        _fsm.unknown(inputStr[i]);
    }
	_fsm.EOS();
	return isAcceptable;
}

/*bool AppClass::CheckString(ifstream& input) {
    #ifdef CRTP
	    enterStartState();
	    reset();
    #else
	    _fsm.enterStartState();
	    _fsm.reset();
    #endif
    string inputStr;
    getline(input, inputStr);
    #ifdef CRTP
        for (int i = 0; i < inputStr.size()-1; i++) {
            if ((inputStr[i] >= 'a' && inputStr[i] <= 'z') || (inputStr[i] >= 'A' && inputStr[i] <= 'Z')) {
                letter(char(inputStr[i]));
                continue;
            }
            if (inputStr[i] >= '0' && inputStr[i] <= '9') {   
                digit(char(scanStr[i]));
                continue;
            }
            if (inputStr[i] == ':') {
                dots();
                continue;
            }
            if (inputStr[i] == '/') {
                slash();
                continue;
            }
            if (inputStr[i] == '?') {
                question();
                continue;
            }
            unknown();
	    }
	    EOS();
    #else
        for (int i = 0; i < inputStr.size()-1; i++) {
            if ((inputStr[i] >= 'a' && inputStr[i] <= 'z') || (inputStr[i] >= 'A' && inputStr[i] <= 'Z')) {
                _fsm.letter(char(inputStr[i]));
                continue;
            }
            if (inputStr[i] >= '0' && inputStr[i] <= '9') {   
                _fsm.digit(char(scanStr[i]));
                continue;
            }
            if (inputStr[i] == ':') {
                _fsm.dots();
                continue;
            }
            if (inputStr[i] == '/') {
                _fsm.slash();
                continue;
            }
            if (inputStr[i] == '?') {
                _fsm.question();
                continue;
            }
            _fsm.unknown();
	    }
	    _fsm.EOS();
    #endif
    return isAcceptable;
}*/

void AppClass::AppendStr(char tmp) {
    tmpStr.append(1,tmp);
}

void AppClass::AppendServer(char tmp) {
    tmpStr.append(1,tmp);
    nameServer.append(1,tmp);
}

void AppClass::AppendPort(char tmp) {
    tmpStr.append(1,tmp);
    PortNumber.append(1,tmp);
}

void AppClass::setAcceptable() {
    isAcceptable = true;
}

void AppClass::UpdateStatistic() {
    if (statistic.find(nameServer) == statistic.end())
        statistic.insert(pair<string, int>(nameServer, 1));
    else
        statistic[nameServer]++;
}

bool AppClass::NotTooLong() {
    if (tmpStr.length() > 6 && tmpStr.length() <= 80)
        return true;
    else
        return false;
}

bool AppClass::checkPort() {
    int port;
    istringstream ist(PortNumber);
    ist >> port;
    if (port > 1 && port < 65536)
        return true;
    else
        return false;
}

void AppClass::ClearCash() {
    isAcceptable = false;
    tmpStr.clear();
    nameServer.clear();
    PortNumber.clear();
}

string& AppClass::getStr() {
    return tmpStr;
}

void AppClass::printStatistic(ofstream& output) {
    auto it = statistic.begin();
    for (; it != statistic.end(); it++)
        output << "Server name: \"" << it->first << "\" encountered " << it->second << endl;
}
