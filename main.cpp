#include <iostream>
#include <fstream>
#include <windows.h>
#include "employee.h"
#include <algorithm>
#include <vector>

using namespace std;

char getOperation()
{
    wchar_t op{};
    do
    {
        wcout << "1 – вывести список сотрудников, 2 – добавить сотрудника, 3 - сортировка, 4 - поиск, 5 выход: ";
        wcin >> op;

    } while (op != '1' && op != '2' && op != '3' && op != '4' && op != '5');

    return op;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Employee employee{};
    vector<Employee> arrEmployees(employee.getCountOfEmployees());
    employee.readEmployees(arrEmployees);

    wchar_t op{};
    while (op != '5') {
        op = getOperation();

        switch (op)
        {
        default:
        case '1':
            employee.printAllEmployees(arrEmployees);
            break;

        case '2':
        {
            employee.getEmployee();
            employee.writeEmployee(arrEmployees);
            employee.readEmployees(arrEmployees);
        }
        break;

        case '3':
            employee.sortEmployees(arrEmployees);
            employee.readEmployees(arrEmployees);
            break;

        case '4':
            employee.findEmployees(arrEmployees);
            break;

        case '5':
            system("exit");
            break;
        }

        wcout << endl;
    }

}
