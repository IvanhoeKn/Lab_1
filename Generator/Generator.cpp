// Generator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "GenDefault.h"
#include "GenErr.h"

using namespace std;

int OpenOutput(ofstream&, const string&);

int main() {
	srand(time(NULL));
	GenDefault gen_dflt;
	GenErr gen_err;
	ofstream output;
	ofstream Statistic;
	string line;
	try {
		int retCode = OpenOutput(output, "test_10.txt");
		if (!retCode)
			for (int i = 0; i < 1000000; i++) 
				if (rand() % 2) {
					gen_dflt.combineStr();
					output << gen_dflt;
				}
				else {
					gen_err.combineStr();
					output << gen_err;
				}
		else
			return 0;
	}
	catch (const std::exception & er) {
		std::cout << er.what() << std::endl;
	}
	output.close();
	cout << "Done!" << endl;
	system("pause");
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
