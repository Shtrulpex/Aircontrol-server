#ifndef DB_CONTROLLER_HPP
#define DB_CONTROLLER_HPP


#include <vector>
#include <string>
#include <sstream>


template <typename Iter>
QString join(Iter begin, Iter end, const std::string& sep)
{
    std::stringstream result;
    if (begin != end)
    {
        result << (*begin).toStdString();
        begin++;
    }
    while (begin != end)
    {
        result << sep << (*begin).toStdString();
        begin++;
    }
    return QString::fromStdString(result.str());
}


#endif // DB_CONTROLLER_HPP
