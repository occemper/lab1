#pragma once

#include <string>
#include <vector>

using namespace std;

enum class SortingDirection {
    ASC = 1,
    DESC = 2
};

enum class SortingProperty {
    FULL_NAME = 1,
    DATE_OF_BIRTH = 2,
    SPECIALITY = 3,
    POSITION = 4
};

enum class SearchingProperty {
    NAME = 1,
    SURNAME = 2,
    PATRONYMIC = 3,
    DAY_OF_BIRTH = 4,
    MONTH_OF_BIRTH = 5,
    YEAR_OF_BIRTH = 6,
    SPECIALITY = 7,
    POSITION = 8
};

class Employee 
{
public:
    string m_surname;
    string m_name;
    string m_patronymic;
    string m_dayOfBirth;
    string m_monthOfBirth;
    string m_yearOfBirth;
    string m_speciality;
    string m_position;

    void getEmployee();
    int getCountOfEmployees();
    void readEmployees(vector <Employee>& arrEmployees);
    void writeEmployee(vector <Employee>& arrEmployees);
    void printEmployee();
    void printAllEmployees(vector <Employee>& arrEmployees);
    void sortEmployees(vector<Employee>& Employee);
    void findEmployees(vector<Employee>& Employee);
};

