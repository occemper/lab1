#include "employee.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include <locale>

using namespace std;

void Employee::getEmployee()
{
    wcout << "Введите фамилию: "; wcin >> m_surname;
    wcout << "Введите имя: "; wcin >> m_name;
    wcout << "Введите отчество: "; wcin >> m_patronymic;
    wcout << "Введите день рождения: "; wcin >> m_dayOfBirth;
    wcout << "Введите месяц рождения: "; wcin >> m_monthOfBirth;
    wcout << "Введите год рождения: "; wcin >> m_yearOfBirth;
    wcout << "Введите специальность по образованию: "; wcin >> m_speciality;
    wcout << "Введите должность: "; wcin >> m_position;
    m_surname[0] = toupper(m_surname[0], locale(""));
    m_name[0] = toupper(m_name[0], locale(""));
    m_patronymic[0] = toupper(m_patronymic[0], locale(""));
    m_speciality[0] = toupper(m_speciality[0], locale(""));
    m_position[0] = toupper(m_position[0], locale(""));
}

int Employee::getCountOfEmployees()
{
    wifstream fin("employees.dat", ofstream::binary);
    static Employee emp{};
    wstring p;
    int countOfEmployees{ 0 };

    if (!fin.is_open()) {
        wcout << "failed to open employees.dat" << endl;
    }
    else
    {
        while (getline(fin, p)) {
            ++countOfEmployees;
        }
    }

    fin.close();

    return countOfEmployees;
}

void Employee::readEmployees(vector <Employee>& arrEmployees)
{
    wifstream fin("employees.dat", ofstream::binary);
    Employee emp{};

    if (!fin.is_open()) {
        wcout << "failed to open employees.dat" << endl;
    }
    else
    {
        for (size_t i = 0; i < arrEmployees.size(); i++) {
            fin >> arrEmployees[i].m_surname;
            fin >> arrEmployees[i].m_name;
            fin >> arrEmployees[i].m_patronymic;
            fin >> arrEmployees[i].m_dayOfBirth;
            fin >> arrEmployees[i].m_monthOfBirth;
            fin >> arrEmployees[i].m_yearOfBirth;
            fin >> arrEmployees[i].m_speciality;
            fin >> arrEmployees[i].m_position;
        }
    }

    fin.close();
}

void Employee::writeEmployee(vector <Employee>& arrEmployees)
{
    wofstream fout("employees.dat", ios::app, ofstream::binary);
    arrEmployees.push_back(*this);
    fout << m_surname << " ";
    fout << m_name << " ";
    fout << m_patronymic << " ";
    fout << m_dayOfBirth << " ";
    fout << m_monthOfBirth << " ";
    fout << m_yearOfBirth << " ";
    fout << m_speciality << " ";
    fout << m_position << endl;

    fout.close();
}

void Employee::printEmployee()
{
    const int LENGTH_OF_OUT{ 9 };
    wcout << setw(LENGTH_OF_OUT) << m_surname << "\t";
    wcout << setw(LENGTH_OF_OUT) << m_name << "\t";
    wcout << setw(LENGTH_OF_OUT) << m_patronymic << "\t";
    wcout << m_dayOfBirth << ".";
    wcout << m_monthOfBirth << ".";
    wcout << m_yearOfBirth << "\t";
    wcout << setw(LENGTH_OF_OUT) << m_speciality << "\t";
    wcout << setw(LENGTH_OF_OUT) << m_position << endl;
}

void Employee::printAllEmployees(vector <Employee>& arrEmployees)
{
    for (Employee emp : arrEmployees) {
        emp.printEmployee();
    }
}

void rewriteEmployee(vector <Employee>& arrEmployees)
{
    wofstream fout("employees.dat", ios::out);

    for (size_t i = 0; i < arrEmployees.size(); i++)
    {
        fout << arrEmployees[i].m_surname << " ";
        fout << arrEmployees[i].m_name << " ";
        fout << arrEmployees[i].m_patronymic << " ";
        fout << arrEmployees[i].m_dayOfBirth << " ";
        fout << arrEmployees[i].m_monthOfBirth << " ";
        fout << arrEmployees[i].m_yearOfBirth << " ";
        fout << arrEmployees[i].m_speciality << " ";
        fout << arrEmployees[i].m_position << endl;
    }

    fout.close();
}

void Employee::sortEmployees(vector<Employee>& arrEmployees)
{

    SortingDirection sortDirection{};
    SortingProperty sortProperty{};
    short t;

    wcout << "Выберите свойство сортировки: 1 – ФИО, 2 – дата рождения, 3 – специальность, 4 – должность: " << endl;
    wcin >> t;
    sortProperty = static_cast<SortingProperty>(t);

    wcout << "Выберите направление сортировки: 1 – по возрастанию, 2 – по убыванию: " << endl;
    wcin >> t;
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

    wcout << "Свойство поиска: 1 – имя, 2 – фамилия, 3 – очество, 4,5,6 – день/месяц/год рождения, 7 – специальность, 8 – должность." << endl;
    wcin >> t;
    searchProperty = static_cast<SearchingProperty>(t);

    wstring strSearch;
    wcin >> strSearch;

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


