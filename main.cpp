#include <iostream>
#include <fstream>
#include <windows.h>
#include "employee.h"
#include <algorithm>
#include <vector>

char getOperation()
{
    char op{};
    do
    {
        std::cout << "1 – вывести список сотрудников, 2 – добавить сотрудника, 3 - сортировка, 4 - поиск, 5 выход: ";
        std::cin >> op;

    } while (op != '1' && op != '2' && op != '3' && op != '4' && op != '5');

    return op;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Employee employee{};
    std::vector<Employee> masEmployees(employee.getCountOfEmployees());

    char op{};
    while (op != '5') {
        op = getOperation();

        switch (op)
        {
        default:
        case '1':
            employee.readEmployees(masEmployees);
            break;

        case '2':
        {
            employee.getEmployee();
            employee.writeEmployee(masEmployees);
        }
        break;

        case '3':
            employee.sortEmployees(masEmployees);
            break;

        case '4':
            ;
            break;

        case '5':
            system("exit");
            break;
        }

        std::cout << std::endl;
    }

}
