#pragma once
#include <iostream>
#include <string>
#define GetLine(in, st) getline(in>>std::ws, st); cout << st << endl;
#define LoadLine(in, st) getline(in>>std::ws, st); 
template <typename T>
T check_cond(T max, T min = 1)
{
    T x;
    while ((std::cin >> x).fail() || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Please, try again: ";
    }
    std::cerr << x << std::endl;
    return x;
}
template <typename T>
T check_bool(T min, T max)
{
    T x;
    while ((std::cin >> x).fail() || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Please, try again: ";
    }
    std::cerr << x << std::endl;
    return x;
}
class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
    redirect_output_wrapper(std::ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};
int check_diameter();
int check_id();
string FName();