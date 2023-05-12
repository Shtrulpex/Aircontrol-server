#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#include <QtSql>
#include "database.h"
#include <QString>


QSqlDatabase connect(const QString& driver, const QString& filepath);

QString get_sqlquery(const AirportQuery&);
QString get_sqlquery(const PlaneQuery&);

QSqlQuery run_sqlquery(const QString& sqlquery, const QSqlDatabase& sqd);

std::vector<Airport> get_airports(QSqlQuery qquery);
std::vector<Plane> get_planes(QSqlQuery qquery);


#endif // DB_CONTROLLER_H
