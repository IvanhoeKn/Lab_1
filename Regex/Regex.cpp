// Regex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "LexAnalyzer.h"

using namespace std;

int Answer(const std::string alt[], int n);
int OpenInput(ifstream& input, const string& nameFile);
int OpenOutput(ofstream& output, const string& nameFile);

const string Menu[] = { "1. Work with files", "2. Working with console input / output", "0. Quit" }, 
			 Choice = "Make your choice",
				Msg = "You are wrong; repeate please";
const int    Num = sizeof(Menu) / sizeof(Menu[0]);

int main(int argc, char* argv[]) {
    ifstream input;
    ofstream output;
    ofstream Statistic;
    if (argc > 2) {
        input.open(argv[1]);
        output.open(argv[2]);  
        Statistic.open(argv[3]);
    }
    else {
        cout << "Not enough arguments!" << endl;
        return 1;
    }
    if(!(input.is_open() && output.is_open() && Statistic.is_open())){
    	cout << "Error of openning files!" << endl;
        return -1;
    }
	/*std::cout << " ***Hello***" << std::endl;
	int index;
	int retCode;
	LexAnalyzer Context;
	clock_t _clock = clock();
	time_t _time;
	ifstream input;
	ofstream output;
	ofstream Statistic;
	string line;
	try {
		while (index = Answer(Menu, Num)) {
			switch (index) {
			case 1:
				cout << " You choose working with files!" << endl;
				retCode = OpenInput(input, "input.txt");
				if (!retCode)
					retCode = OpenOutput(output, "output.txt");
				else
					return 0;
				if (!retCode)
					retCode = OpenOutput(Statistic, "Statistic.txt");
				else
					return 0;*/
                LexAnalyzer Context;
                clock_t _clock = clock();
                time_t _time;
				_time = time(0);
				while (!input.eof())
					Context.CheckString(input, output);
				Context.printStatistic(Statistic);
				Statistic << "\nElapsed time: " << time(0) - _time << " seconds (" << clock() - _clock << " clock ticks)." << endl;
				input.close();
				output.close();
				Statistic.close();
				/*cout << "Well Done!" << endl;
				break;
			case 2:
				cout << " You choose working with console!" << endl;
				cout << "Enter string for checking: ";
				getline(cin, line);
				Context.CheckString(line);
				break;
			case 3:
				cout << " You choose Quite!" << endl;
				break;
			}
		}
		std::cout << " ***That's all. Buy!***" << std::endl;
	}
	catch (const std::exception & er) {
		std::cout << er.what() << std::endl;
	} */
	return 0;
}

int Answer(const std::string alt[], int n) {
	int answer;
	std::string prompt = Choice;
	std::cout << "\nWhat do you want to do:" << std::endl;
	for (int i = 0; i < n; i++)
		std::cout << alt[i].c_str() << std::endl;
	do {
		std::cout << prompt.c_str() << ": -> ";
		prompt = Msg;
		std::cin >> answer;
		if (!std::cin.good()) {
			std::cout << "Error when number of choice was entered; \nRepeat, please." << std::endl;
			std::cin.ignore(80, '\n');
			std::cin.clear();
		}
	} while (answer < 0 || answer >= n);
	std::cin.ignore(80, '\n');
	return answer;
}

int OpenInput(ifstream& input, const string& nameFile) {
	try {
		input.open("input.txt");
	}
	catch (ios_base::failure & ErrCode) {
		cout << "Can't open \"" << nameFile << "\" - " << ErrCode.what() << endl;
		return 1;
	}
	catch (bad_alloc & ErrCode)
	{
		std::cout << "Memory error - " << ErrCode.what() << endl;
		return 1;
	}
	if (input.fail()) {
		std::cout << "Can't open \"" << nameFile << "\"" << endl;
		return 1;
	}
	return 0;
}

int OpenOutput(ofstream& output, const string& nameFile) {
	try {
		output.open(nameFile);
	}
	catch (ios_base::failure & ErrCode) {
		cout << "Can't open \"" << nameFile << "\" - " << ErrCode.what() << endl;
		return 1;
	}
	catch (bad_alloc & ErrCode) {
		std::cout << "Memory error - " << ErrCode.what() << endl;
		return 1;
	}
	if (output.fail()) {
		std::cout << "Can't open \"" << nameFile << "\"" << endl;
		return 1;
	}
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
