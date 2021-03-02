#include <iostream>
#include <fstream>
#include <windows.h>
#include "employee.h"
#include <algorithm>

char getOperation()
{
    char op;
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


    //employee.getEmployee();

    const int countOfEmployees = 5;

    Employee employees[countOfEmployees]{
        {"Иванов", "Иван", "Иванович", "22", "02", "1991", "Аряляр", "Главный архитектор"},
        {"Иванов", "Иван", "Андреевич", "16", "03", "2001", "Маляр", "Главный архитектор"},
        {"Сидоров", "Иван", "Иванович", "24", "02", "2002", "Архитектор", "Главный архитектор" },
        {"Кулибин", "Иван", "Иванович", "17", "02", "1991", "Архитектор", "Главный архитектор"},
        {"Седов", "Иван", "Иванович", "11", "02", "1989", "Архитектор", "Главный архитектор"}
    };

    char op{};
    while (op != '5') {
        op = getOperation();

        switch (op)
        {
        default:
        case '1':
            for (size_t i = 0; i < 5; i++)
            {
                employees[i].printEmployee();
            };
            break;

        case '2':
            ;
            break;

        case '3':
            employees->sortEmployees(employees, countOfEmployees);
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

    system("pause");
}
