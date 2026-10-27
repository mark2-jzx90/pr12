// pr_12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;
const int max_pocs = 20;
int procsCount = 0;

struct Myprocess {
	string name;
	DWORD pid;
	HANDLE hProcess;
	bool is_running;
};

bool startProcess(string path, string args, Myprocess procs[], string displayName) {
	if (procsCount >= max_pocs) {
		cout << "Лимит запущенных процессов вась" << endl;
		return false;
	}
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	string FullCommsnd = path + " " + args;
	char* cmdLine = new char[FullCommsnd.length() + 1];
	strcpy(cmdLine, FullCommsnd.c_str());
	if (!CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		cout << "Ошибка при создании процесса, код ошибки вась:" << GetLastError() << endl;
		delete[] cmdLine;
		return false;
	}
	procs[procsCount].name = displayName;
	procs[procsCount].pid = pi.dwProcessId;
	procs[procsCount].hProcess = pi.hProcess;
	procs[procsCount].is_running = true;
	procsCount++;
	CloseHandle(pi.hThread);	
	delete[] cmdLine;
	cout << "Процесс успешно запущен вась. PID^ " << pi.dwProcessId << endl;
	return true;
}
void killProcess(Myprocess procs[], int index) {
	if (index < 0 || index >= procsCount) {
		cout << "Неверный номер процесса вась" << endl;
		return;
	}
	if (procs[index].is_running) {
		if (TerminateProcess(procs[index].hProcess, 0)) {
			cout << "Процесс" << procs[index].name << " (Pid: " << procs[index].pid << ") завршен вась\n";
			procs[index].is_running = false;
			CloseHandle(procs[index].hProcess);
		}
		else {
			cout << "Не удалось завершить процесс вась" << endl;
		}
	}
	else {
		cout << "Этот процесс уже завершён вась" << endl;
	}
}
void showProcess(Myprocess procs[], int procCount) {
	cout << "Список процессов вась: " << endl;
	if (procsCount == 0) {
		cout << "Список пуст" << endl;
		return;
	}
	int activeCount = 0;
	for (int i = 0; i < procCount; i++) {
		DWORD exitCode;
		if (procs[i].is_running && GetExitCodeProcess(procs[i].hProcess, &exitCode)) {
			if (exitCode != STILL_ACTIVE) {
				procs[i].is_running = false;
				CloseHandle(procs[i].hProcess);
			}
		}

		string status;
		if (procs[i].is_running) {
			status = "Работает";
			activeCount++;
		}
		else {
			status = "Завершён";
		}
		cout << i + 1 << ". Имч: " << procs[i].name << " PID: " << procs[i].pid << " Состояние: " << status << endl;
		cout << "Всего активынх процессов: " << activeCount << endl;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Myprocess processes[max_pocs];
	int choise;
	do {
		cout << "1. Запстить taskmgr.exe\n";
		cout << "2. Запстить ping.exe\n";
		cout << "3. Запстить числа полидром\n";
		cout << "4. Показать список процессов\n";
		cout << "5. Принудительно завершить процесс\n";
		cout << "0. Выход\n";
		cout << "Выбири вась: ";
		cin >> choise;
		if (choise == 1) {
			startProcess("taskmgr.exe", "", processes, "Диспетчер заача");
		}
		else if (choise == 2) {
			string ip, args;
			int mode;
			cout << "Введи ip вась: ";
			cin >> ip;
			cout << "Выбери режим: \nn1. Обычныйю\n2. -n N\n3. -t (бескончено)\nтвой выбор: ";
		}
	} while (choise != 0);
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
