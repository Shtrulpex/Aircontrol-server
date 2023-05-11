#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#include <QtSql>
#include "database.h"
#include <vector>
#include <string>
#include <sstream>
#include <QString>


QSqlDatabase connect(const QString& driver, const QString& filepath);

QString get_sqlquery(const AirportQuery&);
QString get_sqlquery(const PlaneQuery&);

QSqlQuery run_sqlquery(const QString& sqlquery, const QSqlDatabase& sqd);

std::vector<Airport> get_airports(QSqlQuery qquery);
std::vector<Plane> get_planes(QSqlQuery qquery);


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

#endif // DB_CONTROLLER_H
