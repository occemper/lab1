#include <iostream>
#include <fstream>
#include <windows.h>
#include "employee.h"
#include <algorithm>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    
    //employee.getEmployee();

    Employee employees[5]{
        {"Иванов", "Иван", "Иванович", "22", "02", "1991", "Аряляр", "Главный архитектор"},
        {"Иванов", "Иван", "Андреевич", "16", "03", "2001", "Маляр", "Главный архитектор"},
        {"Сидоров", "Иван", "Иванович", "24", "02", "2002", "Архитектор", "Главный архитектор" },
        {"Кулибин", "Иван", "Иванович", "17", "02", "1991", "Архитектор", "Главный архитектор"},
        {"Седов", "Иван", "Иванович", "11", "02", "1989", "Архитектор", "Главный архитектор"}
    };

    std::fstream f("employees.txt");
    
    int countOfEmployees = 5;
    SortingDirection sortDirection = static_cast<SortingDirection>(2);
    SortingProperty sortProperty = static_cast<SortingProperty>(2);
    employees->sortEmployees(employees,countOfEmployees);
    

    for (size_t i = 0; i < 5; i++)
    {
        employees[i].printEmployee();
    }
}
