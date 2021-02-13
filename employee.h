#pragma once

#include <string>

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
    void printEmployee();
    void sortEmployees(Employee employees[], SortingDirection direction, SortingProperty prorerty, int countOfEmployees);
};

