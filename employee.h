#pragma once

#include <string>
#include <vector>

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

class Employee {
    static const int smallStrSize = 16;
    static const int bigStrSize = 32;
public:
    std::string m_surname;
    std::string m_name;
    std::string m_patronymic;
    std::string m_dayOfBirth;
    std::string m_monthOfBirth;
    std::string m_yearOfBirth;
    std::string m_speciality;
    std::string m_position;

    void getEmployee();
    int getCountOfEmployees();
    void readEmployees(std::vector <Employee>& masEmployees);
    void writeEmployee(std::vector <Employee>& masEmployees);
    void printEmployee();
    //void rewriteEmployee(std::vector <Employee>& masEmployees);
    void sortEmployees(std::vector<Employee>& Employee);
};

