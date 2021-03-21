#include "employee.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

void Employee::getEmployee()
{
    cout << "Введите фамилию: "; cin >> m_surname;
    cout << "Введите имя: "; cin >> m_name;
    cout << "Введите отчество: "; cin >> m_patronymic;
    cout << "Введите день рождения: "; cin >> m_dayOfBirth;
    cout << "Введите месяц рождения: "; cin >> m_monthOfBirth;
    cout << "Введите год рождения: "; cin >> m_yearOfBirth;
    cout << "Введите специальность по образованию: "; cin >> m_speciality;
    cout << "Введите должность: "; cin >> m_position;
}

int Employee::getCountOfEmployees()
{
    ifstream fin("employees.dat", ofstream::binary);
    static Employee emp{};
    int countOfEmployees{ 0 };

    if (!fin.is_open()) {
        cout << "failed to open employees.dat" << endl;
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

void Employee::readEmployees(vector <Employee>& masEmployees)
{
    ifstream fin("employees.dat", ofstream::binary);
    Employee emp{};

    if (!fin.is_open()) {
        cout << "failed to open employees.dat" << endl;
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

void Employee::writeEmployee(vector <Employee>& masEmployees)
{
    ofstream fout("employees.dat", ios::app, ofstream::binary);
    masEmployees.push_back(*this);
    fout.write((char*)this, sizeof(Employee));

    fout.close();
}

void Employee::printEmployee()
{
    cout << m_surname << "\t";
    cout << m_name << "\t";
    cout << m_patronymic << "\t";
    cout << m_dayOfBirth << ".";
    cout << m_monthOfBirth << ".";
    cout << m_yearOfBirth << "\t";
    cout << m_speciality << "\t";
    cout << m_position << endl;
}

void rewriteEmployee(vector <Employee>& masEmployees)
{
    ofstream fout("employees.dat", ios::out);

    for (size_t i = 0; i < masEmployees.size(); i++)
    {
        fout.write((char*)&masEmployees[i], sizeof(Employee));
    }

    fout.close();
}

void Employee::sortEmployees(vector<Employee>& masEmployees)
{

    SortingDirection sortDirection{};
    SortingProperty sortProperty{};
    short t;

    cout << "Выберите свойство сортировки: 1 – ФИО, 2 – дата рождения, 3 – специальность, 4 – должность: " << endl;
    cin >> t;
    sortProperty = static_cast<SortingProperty>(t);

    cout << "Выберите направление сортировки: 1 – по возрастанию, 2 – по убыванию: " << endl;
    cin >> t;
    sortDirection = static_cast<SortingDirection>(t);

    if (sortDirection == SortingDirection::ASC) {
        switch (sortProperty)
        {
        case SortingProperty::FULL_NAME:
            sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_surname == b.m_surname) {
                    if (a.m_name == b.m_name)
                        return a.m_patronymic < b.m_patronymic;
                    else return a.m_name < b.m_name;
                }
                else
                    return a.m_surname < b.m_surname; });
            break;

        case SortingProperty::DATE_OF_BIRTH:
            sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_yearOfBirth == b.m_yearOfBirth) {
                    if (a.m_monthOfBirth == b.m_monthOfBirth)
                        return a.m_dayOfBirth < b.m_dayOfBirth;
                    else return a.m_monthOfBirth < b.m_monthOfBirth;
                }
                else
                    return a.m_yearOfBirth < b.m_yearOfBirth; });
            break;

        case SortingProperty::SPECIALITY:
            sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_speciality < b.m_speciality; });
            break;

        case SortingProperty::POSITION:
            sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
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
            sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_surname == b.m_surname) {
                    if (a.m_name == b.m_name)
                        return a.m_patronymic > b.m_patronymic;
                    else return a.m_name > b.m_name;
                }
                else
                    return a.m_surname > b.m_surname; });
            break;

        case SortingProperty::DATE_OF_BIRTH:
            sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_yearOfBirth == b.m_yearOfBirth) {
                    if (a.m_monthOfBirth == b.m_monthOfBirth)
                        return a.m_dayOfBirth > b.m_dayOfBirth;
                    else return a.m_monthOfBirth > b.m_monthOfBirth;
                }
                else
                    return a.m_yearOfBirth > b.m_yearOfBirth; });
            break;

        case SortingProperty::SPECIALITY:
            sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_speciality > b.m_speciality; });
            break;

        case SortingProperty::POSITION:
            sort(masEmployees.begin(), masEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_position > b.m_position; });
            break;

        default:
            break;
        }
    }
    rewriteEmployee(masEmployees);
}

void Employee::findEmployees(vector<Employee>& masEmployees)
{

    SearchingProperty searchProperty{};
    short t;

    cout << "Выберите свойство поиска: 1 – имя, 2 – фамилия, 3 – очество, 4 – день рождения, 5 – месяц рождения" << endl;
    cout << "6 – год рождения, 5 – специальность, 6 – должность : " << endl;
    cin >> t;
    searchProperty = static_cast<SearchingProperty>(t);

    string strSearch;
    cin >> strSearch;

    switch (searchProperty)
    {
    case SearchingProperty::NAME:
        for (Employee emp : masEmployees) {
            if (emp.m_name.find(strSearch) != -1) {
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


