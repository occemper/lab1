#include "employee.h"
#include <iostream>
#include <algorithm>
#include <fstream>


void Employee::getEmployee() {
    std::cin >> m_surname;
    std::cin >> m_name;
    std::cin >> m_patronymic;
    std::cin >> m_dayOfBirth;
    std::cin >> m_monthOfBirth;
    std::cin >> m_yearOfBirth;
    std::cin >> m_speciality;
    std::cin.ignore();
    std::getline(std::cin, m_position);
}

void Employee::readEmployees(Employee employees[]) {
    std::ifstream fin;
    fin.open("employees.txt");

    int i = 0;



    if (!fin.is_open()) {
        std::cout << "failed to open employees.txt" << std::endl;
    }
    else
    {
        Employee emp{};
        while (fin.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
            emp.printEmployee();
        }
    }

    fin.close();
}

void Employee::writeEmployee() {

    Employee emp{};

    std::ofstream fout("employees.txt", std::ios::app);
    emp.getEmployee();

    fout.write((char*)&emp, sizeof(emp));
    fout.close();


}

void Employee::printEmployee() {
    std::cout << m_surname << "\t";
    std::cout << m_name << "\t";
    std::cout << m_patronymic << "\t";
    std::cout << m_dayOfBirth << ".";
    std::cout << m_monthOfBirth << ".";
    std::cout << m_yearOfBirth << "\t";
    std::cout << m_speciality << "\t";
    std::cout << m_position << std::endl;
}

void Employee::sortEmployees(Employee employees[], int countOfEmployees) {

    SortingDirection sortDirection{};
    SortingProperty sortProperty{};
    short t;

    std::cout << "Выберите свойство сортировки: 1 – ФИО, 2 – дата рождения, 3 – специальность, 4 – должность: " << std::endl;
    std::cin >> t;
    sortProperty = static_cast<SortingProperty>(t);

    std::cout << "Выберите направление сортировки: 1 – по возрастанию, 2 – по убыванию: " << std::endl;
    std::cin >> t;
    sortDirection = static_cast<SortingDirection>(t);

    if (sortDirection == SortingDirection::ASC) {
        switch (sortProperty)
        {
        case SortingProperty::FULL_NAME:
            std::sort(employees, employees + countOfEmployees, [](Employee const& a, Employee const& b) {
                if (a.m_surname == b.m_surname) {
                    if (a.m_name == b.m_name)
                        return a.m_patronymic < b.m_patronymic;
                    else return a.m_name < b.m_name;
                }
                else
                    return a.m_surname < b.m_surname; });
            break;

        case SortingProperty::DATE_OF_BIRTH:
            std::sort(employees, employees + countOfEmployees, [](Employee const& a, Employee const& b) {
                if (a.m_yearOfBirth == b.m_yearOfBirth) {
                    if (a.m_monthOfBirth == b.m_monthOfBirth)
                        return a.m_dayOfBirth < b.m_dayOfBirth;
                    else return a.m_monthOfBirth < b.m_monthOfBirth;
                }
                else
                    return a.m_yearOfBirth < b.m_yearOfBirth; });
            break;

        case SortingProperty::SPECIALITY:
            std::sort(employees, employees + countOfEmployees, [](Employee const& a, Employee const& b) {
                return a.m_speciality < b.m_speciality; });
            break;

        case SortingProperty::POSITION:
            std::sort(employees, employees + countOfEmployees, [](Employee const& a, Employee const& b) {
                return a.m_position < b.m_position; });
            break;

        default:
            break;
        }
    }
    else if (sortDirection == SortingDirection::DESC) {
        switch (sortProperty)
        {
        case SortingProperty::FULL_NAME:
            std::sort(employees, employees + countOfEmployees, [](Employee const& a, Employee const& b) {
                if (a.m_surname == b.m_surname) {
                    if (a.m_name == b.m_name)
                        return a.m_patronymic > b.m_patronymic;
                    else return a.m_name > b.m_name;
                }
                else
                    return a.m_surname > b.m_surname; });
            break;

        case SortingProperty::DATE_OF_BIRTH:
            std::sort(employees, employees + countOfEmployees, [](Employee const& a, Employee const& b) {
                if (a.m_yearOfBirth == b.m_yearOfBirth) {
                    if (a.m_monthOfBirth == b.m_monthOfBirth)
                        return a.m_dayOfBirth > b.m_dayOfBirth;
                    else return a.m_monthOfBirth > b.m_monthOfBirth;
                }
                else
                    return a.m_yearOfBirth > b.m_yearOfBirth; });
            break;

        case SortingProperty::SPECIALITY:
            std::sort(employees, employees + countOfEmployees, [](Employee const& a, Employee const& b) {
                return a.m_speciality > b.m_speciality; });
            break;

        case SortingProperty::POSITION:
            std::sort(employees, employees + countOfEmployees, [](Employee const& a, Employee const& b) {
                return a.m_position > b.m_position; });
            break;

        default:
            break;
        }
    }

}



