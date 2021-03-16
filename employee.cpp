#include "employee.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>


void Employee::getEmployee() 
{
    std::cout << "Введите фамилию: "; std::cin >> m_surname;
    std::cout << "Введите имя: "; std::cin >> m_name;
    std::cout << "Введите отчество: "; std::cin >> m_patronymic;
    std::cout << "Введите день рождения: "; std::cin >> m_dayOfBirth;
    std::cout << "Введите месяц рождения: "; std::cin >> m_monthOfBirth;
    std::cout << "Введите год рождения: "; std::cin >> m_yearOfBirth;
    std::cout << "Введите специальность по образованию: "; std::cin >> m_speciality;
    std::cout << "Введите должность: "; std::cin >> m_position;
}

int Employee::getCountOfEmployees() 
{
    std::ifstream fin("employees.dat", std::ofstream::binary);
    static Employee emp{};
    int countOfEmployees{ 0 };

    if (!fin.is_open()) {
        std::cout << "failed to open employees.dat" << std::endl;
    }
    else
    {
        while (fin.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
            ++countOfEmployees;
        }
    }

    fin.close();

    return countOfEmployees;
}

void Employee::readEmployees(std::vector <Employee>& masEmployees) 
{
    std::ifstream fin("employees.dat", std::ofstream::binary);
    Employee emp;

    if (!fin.is_open()) {
        std::cout << "failed to open employees.dat" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < masEmployees.size(); i++) {
            fin.read(reinterpret_cast<char*>(&masEmployees[i]), sizeof(Employee));
            masEmployees[i].printEmployee();
        }
    }

    fin.close();
}

void Employee::writeEmployee(std::vector <Employee>& masEmployees)
{
    std::ofstream fout("employees.dat", std::ios::app, std::ofstream::binary);
    masEmployees.push_back(*this);
    fout.write((char*)this, sizeof(Employee));

    fout.close();
}

void Employee::printEmployee()
{
    std::cout << m_surname << "\t";
    std::cout << m_name << "\t";
    std::cout << m_patronymic << "\t";
    std::cout << m_dayOfBirth << ".";
    std::cout << m_monthOfBirth << ".";
    std::cout << m_yearOfBirth << "\t";
    std::cout << m_speciality << "\t";
    std::cout << m_position << std::endl;
}

void rewriteEmployee(std::vector <Employee>& masEmployees)
{
    std::ofstream fout("employees.dat", std::ios::out);

    for (size_t i = 0; i < masEmployees.size(); i++)
    {
        fout.write((char*)&masEmployees[i], sizeof(Employee));
    }

    fout.close();
}

void Employee::sortEmployees(std::vector<Employee>& masEmployees)
{

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
            std::sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_surname == b.m_surname) {
                    if (a.m_name == b.m_name)
                        return a.m_patronymic < b.m_patronymic;
                    else return a.m_name < b.m_name;
                }
                else
                    return a.m_surname < b.m_surname; });
            break;

        case SortingProperty::DATE_OF_BIRTH:
            std::sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_yearOfBirth == b.m_yearOfBirth) {
                    if (a.m_monthOfBirth == b.m_monthOfBirth)
                        return a.m_dayOfBirth < b.m_dayOfBirth;
                    else return a.m_monthOfBirth < b.m_monthOfBirth;
                }
                else
                    return a.m_yearOfBirth < b.m_yearOfBirth; });
            break;

        case SortingProperty::SPECIALITY:
            std::sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_speciality < b.m_speciality; });
            break;

        case SortingProperty::POSITION:
            std::sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
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
            std::sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_surname == b.m_surname) {
                    if (a.m_name == b.m_name)
                        return a.m_patronymic > b.m_patronymic;
                    else return a.m_name > b.m_name;
                }
                else
                    return a.m_surname > b.m_surname; });
            break;

        case SortingProperty::DATE_OF_BIRTH:
            std::sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_yearOfBirth == b.m_yearOfBirth) {
                    if (a.m_monthOfBirth == b.m_monthOfBirth)
                        return a.m_dayOfBirth > b.m_dayOfBirth;
                    else return a.m_monthOfBirth > b.m_monthOfBirth;
                }
                else
                    return a.m_yearOfBirth > b.m_yearOfBirth; });
            break;

        case SortingProperty::SPECIALITY:
            std::sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_speciality > b.m_speciality; });
            break;

        case SortingProperty::POSITION:
            std::sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_position > b.m_position; });
            break;

        default:
            break;
        }
    }
    rewriteEmployee(masEmployees);
}

void Employee::findEmployees(std::vector<Employee>& masEmployees)
{

    SearchingProperty searchProperty{};
    short t;

    std::cout << "Выберите свойство поиска: 1 – ФИО, 2 – дата рождения, 3 – специальность, 4 – должность: " << std::endl;
    std::cin >> t;
    searchProperty = static_cast<SearchingProperty>(t);

    std::string strSearch;
    std::cin >> strSearch;

    switch (searchProperty)
    {
    case SearchingProperty::NAME:
        for (Employee emp : masEmployees) {
            if (emp.m_name.find(strSearch)!=-1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::SURNAME:
        for (Employee emp : masEmployees) {
            if (emp.m_surname.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::PATRONYMIC:
        for (Employee emp : masEmployees) {
            if (emp.m_patronymic.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::DAY_OF_BIRTH:
        for (Employee emp : masEmployees) {
            if (emp.m_dayOfBirth.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::MONTH_OF_BIRTH:
        for (Employee emp : masEmployees) {
            if (emp.m_monthOfBirth.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::YEAR_OF_BIRTH:
        for (Employee emp : masEmployees) {
            if (emp.m_yearOfBirth.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::SPECIALITY:
        for (Employee emp : masEmployees) {
            if (emp.m_speciality.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::POSITION:
        for (Employee emp : masEmployees) {
            if (emp.m_position.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    default:
        break;
    }

}


