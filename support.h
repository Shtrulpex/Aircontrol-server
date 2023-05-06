#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <QtSql>
#include <sstream>


struct Point
{
    double longitude;
    double latitude;
    double height;
};


struct Name
{
    std::string rus;
    std::string eng;
};


template <typename Iter>
QString join(Iter begin, Iter end, const std::string& sep);

#endif // SUPPORT_H
