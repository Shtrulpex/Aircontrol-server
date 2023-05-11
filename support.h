#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <sstream>
#include <iostream>
#include <QString>


struct Point
{
    double longitude{0.0};
    double latitude{0.0};
    double height{0.0};
};


struct Name
{
    std::string eng{""};
    std::string rus{""};
};


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


#endif // SUPPORT_H
