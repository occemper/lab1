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

void Employee::readEmployees(vector <Employee>& arrEmployees)
{
    ifstream fin("employees.dat", ofstream::binary);
    Employee emp{};

    if (!fin.is_open()) {
        cout << "failed to open employees.dat" << endl;
    }
    else
    {
        for (size_t i = 0; i < arrEmployees.size(); i++) {
            fin.read(reinterpret_cast<char*>(&arrEmployees[i]), sizeof(Employee));
        }
    }

    fin.close();
}

void Employee::writeEmployee(vector <Employee>& arrEmployees)
{
    ofstream fout("employees.dat", ios::app, ofstream::binary);
    arrEmployees.push_back(*this);
    fout.write((char*)this, sizeof(Employee));

    fout.close();
}

void Employee::printEmployee()
{
    const int LENGTH_OF_OUT{ 9 };
    cout << setw(LENGTH_OF_OUT) << m_surname << "\t";
    cout << setw(LENGTH_OF_OUT) << m_name << "\t";
    cout << setw(LENGTH_OF_OUT) << m_patronymic << "\t";
    cout << m_dayOfBirth << ".";
    cout << m_monthOfBirth << ".";
    cout << m_yearOfBirth << "\t";
    cout << setw(LENGTH_OF_OUT) << m_speciality << "\t";
    cout << setw(LENGTH_OF_OUT) << m_position << endl;
}

void Employee::printAllEmployees(vector <Employee>& arrEmployees)
{
    for (Employee emp : arrEmployees) {
        emp.printEmployee();
    }
}

void rewriteEmployee(vector <Employee>& arrEmployees)
{
    ofstream fout("employees.dat", ios::out);

    for (size_t i = 0; i < arrEmployees.size(); i++)
    {
        fout.write((char*)&arrEmployees[i], sizeof(Employee));
    }

    fout.close();
}

void Employee::sortEmployees(vector<Employee>& arrEmployees)
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
            sort(arrEmployees.begin(), arrEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_surname == b.m_surname) {
                    if (a.m_name == b.m_name)
                        return a.m_patronymic < b.m_patronymic;
                    else return a.m_name < b.m_name;
                }
                else
                    return a.m_surname < b.m_surname; });
            break;

        case SortingProperty::DATE_OF_BIRTH:
            sort(arrEmployees.begin(), arrEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_yearOfBirth == b.m_yearOfBirth) {
                    if (a.m_monthOfBirth == b.m_monthOfBirth)
                        return a.m_dayOfBirth < b.m_dayOfBirth;
                    else return a.m_monthOfBirth < b.m_monthOfBirth;
                }
                else
                    return a.m_yearOfBirth < b.m_yearOfBirth; });
            break;

        case SortingProperty::SPECIALITY:
            sort(arrEmployees.begin(), arrEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_speciality < b.m_speciality; });
            break;

        case SortingProperty::POSITION:
            sort(arrEmployees.begin(), arrEmployees.end(), [](Employee const& a, Employee const& b) {
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
            sort(arrEmployees.begin(), arrEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_surname == b.m_surname) {
                    if (a.m_name == b.m_name)
                        return a.m_patronymic > b.m_patronymic;
                    else return a.m_name > b.m_name;
                }
                else
                    return a.m_surname > b.m_surname; });
            break;

        case SortingProperty::DATE_OF_BIRTH:
            sort(arrEmployees.begin(), arrEmployees.end(), [](Employee const& a, Employee const& b) {
                if (a.m_yearOfBirth == b.m_yearOfBirth) {
                    if (a.m_monthOfBirth == b.m_monthOfBirth)
                        return a.m_dayOfBirth > b.m_dayOfBirth;
                    else return a.m_monthOfBirth > b.m_monthOfBirth;
                }
                else
                    return a.m_yearOfBirth > b.m_yearOfBirth; });
            break;

        case SortingProperty::SPECIALITY:
            sort(arrEmployees.begin(), arrEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_speciality > b.m_speciality; });
            break;

        case SortingProperty::POSITION:
            sort(arrEmployees.begin(), arrEmployees.end(), [](Employee const& a, Employee const& b) {
                return a.m_position > b.m_position; });
            break;

        default:
            break;
        }
    }
    rewriteEmployee(arrEmployees);
}

void Employee::findEmployees(vector<Employee>& arrEmployees)
{

    SearchingProperty searchProperty{};
    short t;

    cout << "Свойство поиска: 1 – имя, 2 – фамилия, 3 – очество, 4,5,6 – день/месяц/год рождения, 7 – специальность, 8 – должность." << endl;
    cin >> t;
    searchProperty = static_cast<SearchingProperty>(t);

    string strSearch;
    cin >> strSearch;

    switch (searchProperty)
    {
    case SearchingProperty::NAME:
        for (Employee emp : arrEmployees) {
            if (emp.m_name.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::SURNAME:
        for (Employee emp : arrEmployees) {
            if (emp.m_surname.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::PATRONYMIC:
        for (Employee emp : arrEmployees) {
            if (emp.m_patronymic.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::DAY_OF_BIRTH:
        for (Employee emp : arrEmployees) {
            if (emp.m_dayOfBirth.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::MONTH_OF_BIRTH:
        for (Employee emp : arrEmployees) {
            if (emp.m_monthOfBirth.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::YEAR_OF_BIRTH:
        for (Employee emp : arrEmployees) {
            if (emp.m_yearOfBirth.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::SPECIALITY:
        for (Employee emp : arrEmployees) {
            if (emp.m_speciality.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    case SearchingProperty::POSITION:
        for (Employee emp : arrEmployees) {
            if (emp.m_position.find(strSearch) != -1) {
                emp.printEmployee();
            }
        }
        break;

    default:
        break;
    }

}


