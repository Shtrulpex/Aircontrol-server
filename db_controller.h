#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#include <QtSql>
#include "data_object.h"
#include "query.h"
#include <vector>
#include <string>
#include <cmath>


std::vector<Airport> run_query(const AirportQuery& query);
std::vector<Plane> run_query(const PlaneQuery& query);

QSqlDatabase connect(const QString& driver, const QString& filepath);

QString get_sqlquery(const AirportQuery&);
QString get_sqlquery(const PlaneQuery&);

QSqlQuery run_sqlquery(const QString& sqlquery, const QSqlDatabase& sqd);

std::vector<Airport> get_airports(QSqlQuery qquery);
std::vector<Plane> get_planes(QSqlQuery qquery);

#endif // DB_CONTROLLER_H
