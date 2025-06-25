

#pragma once

#include <string>
#include <ctime>
#include <unordered_map>

enum Position
{
    Junior = 0,
    Senior = 1,
    Manager = 2

};

struct Bonus
{
    double positionBonus;
    int extraBonus;
};

class Employee
{
public:
    Employee(int baseSalary, Position p, std::string fullName, std::tm tm) : s(p, tm, baseSalary) {}
    void upDateCalc() {};
    double getAnnual()
    {
        return s.calcAnnual();
    }

private:
    int salary;
    Salary s;
};

class Salary
{
public:
    Salary(Position p, std::tm tm, int baseSalary) : baseSalary(baseSalary), p(p), start(start)
    {
    }

    double calcAnnual()
    {
        time_t now = time(nullptr);
        tm *local_tm = localtime(&now);
        double annual = baseSalary * 12;
        annual = annual * calc[p].positionBonus;
        if (start.tm_year - local_tm->tm_year >= 1)
        {
            annual += baseSalary;
        }

        return annual;
    }

private:
    int baseSalary;
    Position p;
    std::tm start;
    static std::unordered_map<Position, Bonus> calc;
};

std::unordered_map<Position, Bonus> Salary::calc =
    {
        {Junior, {1.0, 0}},
        {Senior, {1.1, 0}},
        {Manager, {1.15, 15000}}};